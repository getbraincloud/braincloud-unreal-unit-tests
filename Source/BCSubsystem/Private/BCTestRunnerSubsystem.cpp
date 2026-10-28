// Copyright 2026 bitHeads, Inc. All Rights Reserved.

#include "BCTestRunnerSubsystem.h"
#include "SBCTestRunnerOverlay.h"

#include "AssetRegistry/IAssetRegistry.h"
#include "Dom/JsonObject.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformMisc.h"
#include "Misc/AutomationTest.h"
#include "Misc/CommandLine.h"
#include "Misc/FileHelper.h"
#include "Misc/OutputDevice.h"
#include "Misc/Paths.h"
#include "Misc/ScopeLock.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/UObjectGlobals.h"
#include "Widgets/SWeakWidget.h"

// Shipping builds have no automation framework, so the runner is compiled out there.
#if WITH_AUTOMATION_TESTS

DEFINE_LOG_CATEGORY_STATIC(LogBCTestRunner, Log, All);

namespace
{
	const int32 GMaxLogLines = 3000;
	const FName GFunctionalTestCategory(TEXT("LogFunctionalTest"));

	bool IsRunnerEnabled()
	{
#if PLATFORM_ANDROID || PLATFORM_IOS
		return true;
#else
		FString Filter;
		return FParse::Param(FCommandLine::Get(), TEXT("BCTestRunner")) ||
			FParse::Value(FCommandLine::Get(), TEXT("BCRunTests="), Filter);
#endif
	}

	const TCHAR* StatusName(EBCTestStatus Status)
	{
		switch (Status)
		{
		case EBCTestStatus::Running: return TEXT("Running");
		case EBCTestStatus::Passed: return TEXT("Passed");
		case EBCTestStatus::Failed: return TEXT("Failed");
		default: return TEXT("Pending");
		}
	}

	bool ParseOperation(const FString& Text, FBCTestOperation& Out)
	{
		static const FString Succeed(TEXT("TEST SUCCEED: "));
		static const FString Failed(TEXT("TEST FAILED: "));

		int32 Start = Text.Find(Succeed);
		bool bPassed = true;
		if (Start == INDEX_NONE)
		{
			Start = Text.Find(Failed);
			bPassed = false;
			if (Start == INDEX_NONE)
			{
				return false;
			}
		}

		FString Name = Text.Mid(Start + (bPassed ? Succeed.Len() : Failed.Len()));
		while (Name.EndsWith(TEXT("/")))
		{
			Name.LeftChopInline(1);
		}
		Out.Name = Name.TrimStartAndEnd();
		Out.bPassed = bPassed;
		return !Out.Name.IsEmpty();
	}
}

class UBCTestRunnerSubsystem::FLogCapture : public FOutputDevice
{
public:
	struct FLine
	{
		FString Text;
		ELogVerbosity::Type Verbosity;
		FName Category;
	};

	virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override
	{
		const ELogVerbosity::Type Level = (ELogVerbosity::Type)(Verbosity & ELogVerbosity::VerbosityMask);
		if (Level > ELogVerbosity::Warning && Category != GFunctionalTestCategory)
		{
			return;
		}
		FScopeLock Lock(&Mutex);
		Pending.Add({ FString(V), Level, Category });
	}

	virtual bool CanBeUsedOnAnyThread() const override { return true; }

	void Drain(TArray<FLine>& Out)
	{
		FScopeLock Lock(&Mutex);
		Out = MoveTemp(Pending);
		Pending.Reset();
	}

private:
	FCriticalSection Mutex;
	TArray<FLine> Pending;
};

bool UBCTestRunnerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return !GIsEditor && !IsRunningDedicatedServer() && IsRunnerEnabled();
}

void UBCTestRunnerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FParse::Value(FCommandLine::Get(), TEXT("BCRunTests="), AutoRunFilter);
	bQuitWhenDone = FParse::Param(FCommandLine::Get(), TEXT("BCQuitWhenDone"));
	CurrentFilter = AutoRunFilter.IsEmpty() ? FString(TEXT("Test_")) : AutoRunFilter;

	LogCapture = MakeShared<FLogCapture>();
	GLog->AddOutputDevice(LogCapture.Get());

	PostLoadMapHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UBCTestRunnerSubsystem::HandlePostLoadMap);
	TestEndHandle = FAutomationTestFramework::Get().OnTestEndEvent.AddUObject(this, &UBCTestRunnerSubsystem::HandleTestEnd);

#if ENGINE_MAJOR_VERSION >= 5
	TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UBCTestRunnerSubsystem::Tick));
#else
	TickHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UBCTestRunnerSubsystem::Tick));
#endif
}

void UBCTestRunnerSubsystem::Deinitialize()
{
#if ENGINE_MAJOR_VERSION >= 5
	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
#else
	FTicker::GetCoreTicker().RemoveTicker(TickHandle);
#endif
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(PostLoadMapHandle);
	FAutomationTestFramework::Get().OnTestEndEvent.Remove(TestEndHandle);

	if (LogCapture.IsValid())
	{
		GLog->RemoveOutputDevice(LogCapture.Get());
		LogCapture.Reset();
	}
	if (GEngine && GEngine->GameViewport && OverlayContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(OverlayContainer.ToSharedRef());
	}
	Overlay.Reset();
	OverlayContainer.Reset();

	Super::Deinitialize();
}

void UBCTestRunnerSubsystem::DiscoverTests()
{
	FAutomationTestFramework& Framework = FAutomationTestFramework::Get();
	Framework.LoadTestModules();
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5)
	Framework.SetRequestedTestFilter(EAutomationTestFlags::ClientContext | EAutomationTestFlags_FilterMask);
#else
	Framework.SetRequestedTestFilter(EAutomationTestFlags::ClientContext | EAutomationTestFlags::FilterMask);
#endif

	TArray<FAutomationTestInfo> Infos;
	Framework.GetValidTestNames(Infos);

	AllTests.Reset();
	for (const FAutomationTestInfo& Info : Infos)
	{
		FBCTestEntry Entry;
		Entry.FullPath = Info.GetFullTestPath();
		Entry.Command = Info.GetTestName();
		TArray<FString> Parts;
		Entry.FullPath.ParseIntoArray(Parts, TEXT("."));
		if (Parts.Num() >= 2 && Parts.Last() == TEXT("GlobalTestHandler"))
		{
			Entry.DisplayName = Parts[Parts.Num() - 2];
		}
		else
		{
			Entry.DisplayName = Parts.Num() > 0 ? Parts.Last() : Entry.FullPath;
		}
		AllTests.Add(MoveTemp(Entry));
	}
	AllTests.Sort([](const FBCTestEntry& A, const FBCTestEntry& B) { return A.FullPath < B.FullPath; });
	bDiscovered = true;

	if (FParse::Param(FCommandLine::Get(), TEXT("BCListTests")))
	{
		for (const FBCTestEntry& Entry : AllTests)
		{
			UE_LOG(LogBCTestRunner, Log, TEXT("[BCTestRunner] Test: %s"), *Entry.FullPath);
		}
	}

	UE_LOG(LogBCTestRunner, Log, TEXT("[BCTestRunner] %d tests available"), AllTests.Num());

	if (!bRunning)
	{
		Tests = AllTests.FilterByPredicate([this](const FBCTestEntry& Entry)
		{
			return Entry.FullPath.Contains(CurrentFilter);
		});
		++Revision;
	}
}

void UBCTestRunnerSubsystem::RunTests(const FString& Filter)
{
	if (bRunning)
	{
		return;
	}
	if (!bDiscovered)
	{
		DiscoverTests();
	}

	CurrentFilter = Filter.TrimStartAndEnd();
	Tests = AllTests.FilterByPredicate([this](const FBCTestEntry& Entry)
	{
		return CurrentFilter.IsEmpty() || Entry.FullPath.Contains(CurrentFilter);
	});
	ClearLog();

	UE_LOG(LogBCTestRunner, Log, TEXT("[BCTestRunner] Running %d tests matching '%s'"), Tests.Num(), *CurrentFilter);
	bRunning = true;
	RunStartTime = FPlatformTime::Seconds();
	CurrentIndex = INDEX_NONE;
	++Revision;
	StartNextTest();
}

void UBCTestRunnerSubsystem::StartNextTest()
{
	++CurrentIndex;
	if (!Tests.IsValidIndex(CurrentIndex))
	{
		FinishRun();
		return;
	}

	FBCTestEntry& Entry = Tests[CurrentIndex];
	Entry.Status = EBCTestStatus::Running;
	Entry.StartTime = FPlatformTime::Seconds();
	bLatentDone = false;
	bCurrentEnded = false;
	bAwaitingEnd = true;
	++Revision;

	UE_LOG(LogBCTestRunner, Log, TEXT("[BCTestRunner] Start %s"), *Entry.FullPath);
	FAutomationTestFramework::Get().StartTestByName(Entry.Command, 0);
	if (!GIsAutomationTesting && bAwaitingEnd)
	{
		FAutomationTestExecutionInfo Info;
		Info.AddError(TEXT("The test could not be started."));
		RecordResult(false, Info);
	}
}

void UBCTestRunnerSubsystem::DriveCurrentTest()
{
	if (!GIsAutomationTesting)
	{
		return;
	}
	// AutomationWorker, when loaded, already executes latent commands every frame but only stops tests it started.
	const bool bWorkerTicks = FModuleManager::Get().IsModuleLoaded(TEXT("AutomationWorker"));
	FAutomationTestFramework& Framework = FAutomationTestFramework::Get();
	if (!bLatentDone)
	{
		bLatentDone = bWorkerTicks ? Framework.IsLatentCommandQueueEmpty() : Framework.ExecuteLatentCommands();
	}
	else if (Framework.ExecuteNetworkCommands())
	{
		if (!bWorkerTicks)
		{
			Framework.ExecuteLatentCommands();
		}
		FAutomationTestExecutionInfo Info;
		Framework.StopTest(Info);
	}
	else
	{
		bLatentDone = false;
	}
}

void UBCTestRunnerSubsystem::HandleTestEnd(FAutomationTestBase* Test)
{
	if (!bAwaitingEnd || !Test)
	{
		return;
	}
	FAutomationTestExecutionInfo Info;
	Test->GetExecutionInfo(Info);
	RecordResult(Test->GetLastExecutionSuccessState(), Info);
}

void UBCTestRunnerSubsystem::RecordResult(bool bSuccess, const FAutomationTestExecutionInfo& Info)
{
	if (!Tests.IsValidIndex(CurrentIndex))
	{
		return;
	}
	bAwaitingEnd = false;
	bCurrentEnded = true;

	FBCTestEntry& Entry = Tests[CurrentIndex];
	Entry.Duration = FPlatformTime::Seconds() - Entry.StartTime;
	for (const FAutomationExecutionEntry& Item : Info.GetEntries())
	{
		if (Item.Event.Type == EAutomationEventType::Error)
		{
			Entry.Errors.Add(Item.Event.Message);
			LogLines.Add({ Entry.DisplayName, Item.Event.Message, ELogVerbosity::Error });
		}
		else if (Item.Event.Type == EAutomationEventType::Warning)
		{
			Entry.Warnings.Add(Item.Event.Message);
		}
	}
	const bool bAnyOperationFailed = Entry.Operations.ContainsByPredicate([](const FBCTestOperation& Op) { return !Op.bPassed; });
	Entry.Status = (bSuccess && !bAnyOperationFailed) ? EBCTestStatus::Passed : EBCTestStatus::Failed;
	++Revision;

	UE_LOG(LogBCTestRunner, Log, TEXT("[BCTestRunner] %s %s (%.1fs, %d calls, %d errors)"),
		StatusName(Entry.Status), *Entry.FullPath, Entry.Duration, Entry.Operations.Num(), Entry.Errors.Num());
}

void UBCTestRunnerSubsystem::FinishRun()
{
	bRunning = false;
	CurrentIndex = INDEX_NONE;
	++Revision;

	int32 Passed = 0;
	int32 Failed = 0;
	for (const FBCTestEntry& Entry : Tests)
	{
		Entry.Status == EBCTestStatus::Passed ? ++Passed : ++Failed;
	}
	WriteReport();
	UE_LOG(LogBCTestRunner, Log, TEXT("[BCTestRunner] Finished: %d passed, %d failed, %.1fs"),
		Passed, Failed, FPlatformTime::Seconds() - RunStartTime);

	if (bQuitWhenDone)
	{
		FPlatformMisc::RequestExit(false);
	}
}

void UBCTestRunnerSubsystem::WriteReport() const
{
	TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetStringField(TEXT("filter"), CurrentFilter);
	Root->SetNumberField(TEXT("totalDuration"), FPlatformTime::Seconds() - RunStartTime);

	TArray<TSharedPtr<FJsonValue>> TestValues;
	for (const FBCTestEntry& Entry : Tests)
	{
		TSharedRef<FJsonObject> Test = MakeShared<FJsonObject>();
		Test->SetStringField(TEXT("fullTestPath"), Entry.FullPath);
		Test->SetStringField(TEXT("testDisplayName"), Entry.DisplayName);
		Test->SetStringField(TEXT("state"), Entry.Status == EBCTestStatus::Passed ? TEXT("Success") : TEXT("Fail"));
		Test->SetNumberField(TEXT("duration"), Entry.Duration);

		TArray<TSharedPtr<FJsonValue>> Entries;
		auto AddEntry = [&Entries](const TCHAR* Type, const FString& Message)
		{
			TSharedRef<FJsonObject> Event = MakeShared<FJsonObject>();
			Event->SetStringField(TEXT("type"), Type);
			Event->SetStringField(TEXT("message"), Message);
			TSharedRef<FJsonObject> Item = MakeShared<FJsonObject>();
			Item->SetObjectField(TEXT("event"), Event);
			Entries.Add(MakeShared<FJsonValueObject>(Item));
		};
		for (const FString& Error : Entry.Errors) AddEntry(TEXT("Error"), Error);
		for (const FString& Warning : Entry.Warnings) AddEntry(TEXT("Warning"), Warning);
		for (const FBCTestOperation& Op : Entry.Operations)
		{
			if (!Op.bPassed) AddEntry(TEXT("Error"), FString::Printf(TEXT("TEST FAILED: %s"), *Op.Name));
		}
		Test->SetArrayField(TEXT("entries"), Entries);

		TArray<TSharedPtr<FJsonValue>> Ops;
		for (const FBCTestOperation& Op : Entry.Operations)
		{
			TSharedRef<FJsonObject> OpObj = MakeShared<FJsonObject>();
			OpObj->SetStringField(TEXT("name"), Op.Name);
			OpObj->SetBoolField(TEXT("passed"), Op.bPassed);
			Ops.Add(MakeShared<FJsonValueObject>(OpObj));
		}
		Test->SetArrayField(TEXT("operations"), Ops);
		TestValues.Add(MakeShared<FJsonValueObject>(Test));
	}
	Root->SetArrayField(TEXT("tests"), TestValues);

	FString Json;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Json);
	FJsonSerializer::Serialize(Root, Writer);

	const FString ReportPath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("BCTestRunner"), TEXT("results.json"));
	FFileHelper::SaveStringToFile(Json, *ReportPath);
	UE_LOG(LogBCTestRunner, Log, TEXT("[BCTestRunner] Report: %s"),
		*IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(*ReportPath));
}

bool UBCTestRunnerSubsystem::Tick(float DeltaTime)
{
	if (LogCapture.IsValid())
	{
		TArray<FLogCapture::FLine> Lines;
		LogCapture->Drain(Lines);
		for (const FLogCapture::FLine& Line : Lines)
		{
			HandleCapturedLine(Line.Text, Line.Verbosity, Line.Category);
		}
	}

	if (!Overlay.IsValid() && GEngine && GEngine->GameViewport)
	{
		ShowOverlay();
	}
	// Driven from here because Slate does not reliably tick viewport widgets on device.
	if (Overlay.IsValid())
	{
		Overlay->Refresh();
	}

	if (!bDiscovered)
	{
		if (IAssetRegistry::GetChecked().IsLoadingAssets())
		{
			return true;
		}
		DiscoverTests();
		if (!AutoRunFilter.IsEmpty())
		{
			RunTests(AutoRunFilter);
		}
		return true;
	}

	if (bRunning && Tests.IsValidIndex(CurrentIndex))
	{
		if (bCurrentEnded)
		{
			StartNextTest();
		}
		else
		{
			DriveCurrentTest();
		}
	}
	return true;
}

void UBCTestRunnerSubsystem::HandleCapturedLine(const FString& Text, ELogVerbosity::Type Verbosity, const FName& Category)
{
	const FString TestName = Tests.IsValidIndex(CurrentIndex) ? Tests[CurrentIndex].DisplayName : FString();

	if (Category == GFunctionalTestCategory)
	{
		FBCTestOperation Op;
		if (ParseOperation(Text, Op))
		{
			if (Tests.IsValidIndex(CurrentIndex))
			{
				Tests[CurrentIndex].Operations.Add(Op);
			}
			if (!Op.bPassed)
			{
				LogLines.Add({ TestName, FString::Printf(TEXT("TEST FAILED: %s"), *Op.Name), ELogVerbosity::Error });
			}
			++Revision;
			return;
		}
		if (Verbosity > ELogVerbosity::Warning)
		{
			return;
		}
	}

	LogLines.Add({ TestName, FString::Printf(TEXT("%s: %s"), *Category.ToString(), *Text), Verbosity });
	if (LogLines.Num() > GMaxLogLines)
	{
		LogLines.RemoveAt(0, LogLines.Num() - GMaxLogLines);
	}
	++Revision;
}

void UBCTestRunnerSubsystem::ClearLog()
{
	LogLines.Reset();
	++Revision;
}

void UBCTestRunnerSubsystem::ShowOverlay()
{
	if (!GEngine || !GEngine->GameViewport)
	{
		return;
	}
	if (!Overlay.IsValid())
	{
		Overlay = SNew(SBCTestRunnerOverlay).Runner(this);
		OverlayContainer = SNew(SWeakWidget).PossiblyNullContent(Overlay);
	}
	GEngine->GameViewport->RemoveViewportWidgetContent(OverlayContainer.ToSharedRef());
	GEngine->GameViewport->AddViewportWidgetContent(OverlayContainer.ToSharedRef(), 1000);
	// Test maps print to the screen over the overlay; those lines are in the Logs panel instead.
	GEngine->bEnableOnScreenDebugMessages = false;
}

void UBCTestRunnerSubsystem::HandlePostLoadMap(UWorld* World)
{
	ShowOverlay();
	if (World)
	{
		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			PC->SetShowMouseCursor(true);
		}
	}
}

#else

bool UBCTestRunnerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return false;
}

void UBCTestRunnerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBCTestRunnerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UBCTestRunnerSubsystem::RunTests(const FString& Filter)
{
}

void UBCTestRunnerSubsystem::ClearLog()
{
}

#endif
