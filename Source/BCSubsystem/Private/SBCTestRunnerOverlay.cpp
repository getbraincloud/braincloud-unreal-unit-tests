// Copyright 2026 bitHeads, Inc. All Rights Reserved.

#include "SBCTestRunnerOverlay.h"
#include "BCTestRunnerSubsystem.h"

#include "Styling/CoreStyle.h"
#include "Styling/SlateTypes.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SDPIScaler.h"
#include "Widgets/Layout/SSafeZone.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Text/STextBlock.h"

namespace
{
	const FLinearColor GBackground(0.02f, 0.03f, 0.05f, 0.94f);
	const FLinearColor GPanel(0.06f, 0.07f, 0.10f, 0.98f);
	const FLinearColor GText(0.88f, 0.90f, 0.93f);
	const FLinearColor GDim(0.55f, 0.58f, 0.63f);
	const FLinearColor GPass(0.30f, 0.85f, 0.40f);
	const FLinearColor GFail(0.95f, 0.30f, 0.30f);
	const FLinearColor GRun(0.98f, 0.80f, 0.25f);
	const FLinearColor GWarningColor(0.95f, 0.65f, 0.20f);
	const double GMinRebuildInterval = 0.25;
#if PLATFORM_ANDROID || PLATFORM_IOS
	// Phone screens are dense; scale up so text and buttons stay readable and tappable.
	const float GScale = 1.5f;
#else
	const float GScale = 1.f;
#endif

	FSlateFontInfo Font(int32 Size, bool bBold = false)
	{
		return FCoreStyle::GetDefaultFontStyle(bBold ? "Bold" : "Regular", Size);
	}

	FLinearColor StatusColor(EBCTestStatus Status)
	{
		switch (Status)
		{
		case EBCTestStatus::Passed: return GPass;
		case EBCTestStatus::Failed: return GFail;
		case EBCTestStatus::Running: return GRun;
		default: return GDim;
		}
	}

	FText StatusLabel(EBCTestStatus Status)
	{
		switch (Status)
		{
		case EBCTestStatus::Passed: return FText::FromString(TEXT("PASS"));
		case EBCTestStatus::Failed: return FText::FromString(TEXT("FAIL"));
		case EBCTestStatus::Running: return FText::FromString(TEXT("RUN"));
		default: return FText::FromString(TEXT("..."));
		}
	}

	TSharedRef<SWidget> MakeButton(const FString& Label, FOnClicked OnClicked, TSharedPtr<STextBlock>* OutText = nullptr)
	{
		TSharedRef<STextBlock> Text = SNew(STextBlock).Text(FText::FromString(Label)).Font(Font(14, true));
		if (OutText)
		{
			*OutText = Text;
		}
		return SNew(SButton)
			.ButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button"))
			.ContentPadding(FMargin(16.f, 8.f))
			.OnClicked(OnClicked)
			[
				Text
			];
	}
}

void SBCTestRunnerOverlay::Construct(const FArguments& InArgs)
{
	Runner = InArgs._Runner;
	const FSlateBrush* WhiteBrush = FCoreStyle::Get().GetBrush("GenericWhiteBox");

	// The background fills the screen; the content stays inside the notch and rounded-corner safe area.
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(WhiteBrush)
		.BorderBackgroundColor(GBackground)
		.Padding(0.f)
		[
		SNew(SSafeZone)
		[
		SNew(SDPIScaler)
		.DPIScale(GScale)
		[
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SBox)
			.Padding(FMargin(16.f))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("brainCloud Unit Tests"))).Font(Font(20, true)).ColorAndOpacity(GText)
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 4.f, 0.f, 8.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 16.f, 0.f)
					[
						SAssignNew(StateText, STextBlock).Font(Font(16, true)).ColorAndOpacity(GRun)
					]
					+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 16.f, 0.f)
					[
						SAssignNew(PassedText, STextBlock).Font(Font(16, true)).ColorAndOpacity(GPass)
					]
					+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 16.f, 0.f)
					[
						SAssignNew(FailedText, STextBlock).Font(Font(16, true)).ColorAndOpacity(GFail)
					]
					+ SHorizontalBox::Slot().AutoWidth()
					[
						SAssignNew(RemainingText, STextBlock).Font(Font(16, true)).ColorAndOpacity(GText)
					]
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 8.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().FillWidth(1.f).VAlign(VAlign_Center).Padding(0.f, 0.f, 8.f, 0.f)
					[
						SAssignNew(FilterBox, SEditableTextBox)
						.Font(Font(14))
						.HintText(FText::FromString(TEXT("Test filter, e.g. Test_ or Test_Identity")))
					]
					+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 8.f, 0.f)
					[
						MakeButton(TEXT("Run"), FOnClicked::CreateSP(this, &SBCTestRunnerOverlay::HandleRunClicked))
					]
					+ SHorizontalBox::Slot().AutoWidth()
					[
						MakeButton(TEXT("Logs"), FOnClicked::CreateSP(this, &SBCTestRunnerOverlay::HandleLogsClicked), &LogsButtonText)
					]
				]
				+ SVerticalBox::Slot().FillHeight(1.f)
				[
					SAssignNew(TestList, SScrollBox)
				]
			]
		]
		+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			.Visibility_Lambda([this]() { return bLogVisible ? EVisibility::Visible : EVisibility::Collapsed; })
			+ SVerticalBox::Slot().FillHeight(0.35f)
			[
				SNew(SBox)
			]
			+ SVerticalBox::Slot().FillHeight(0.65f)
			[
				SNew(SBorder)
				.BorderImage(WhiteBrush)
				.BorderBackgroundColor(GPanel)
				.Padding(FMargin(16.f))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 8.f)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().FillWidth(1.f).VAlign(VAlign_Center)
						[
							SNew(STextBlock).Text(FText::FromString(TEXT("Logs"))).Font(Font(18, true)).ColorAndOpacity(GText)
						]
						+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 8.f, 0.f)
						[
							MakeButton(TEXT("Errors only"), FOnClicked::CreateSP(this, &SBCTestRunnerOverlay::HandleErrorsOnlyClicked), &ErrorsOnlyText)
						]
						+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 8.f, 0.f)
						[
							MakeButton(TEXT("Clear"), FOnClicked::CreateSP(this, &SBCTestRunnerOverlay::HandleClearLogClicked))
						]
						+ SHorizontalBox::Slot().AutoWidth()
						[
							MakeButton(TEXT("Close"), FOnClicked::CreateSP(this, &SBCTestRunnerOverlay::HandleLogsClicked))
						]
					]
					+ SVerticalBox::Slot().FillHeight(1.f)
					[
						SAssignNew(LogList, SScrollBox)
					]
				]
			]
		]
		]
		]
		]
	];
}

void SBCTestRunnerOverlay::Refresh()
{
	UBCTestRunnerSubsystem* RunnerPtr = Runner.Get();
	if (!RunnerPtr)
	{
		return;
	}
	const double InCurrentTime = FPlatformTime::Seconds();
	if (StateText.IsValid())
	{
		StateText->SetText(FText::FromString(RunnerPtr->IsRunning() ? TEXT("Running") : TEXT("Idle")));
		PassedText->SetText(FText::FromString(FString::Printf(TEXT("Passed %d"), GetCount(EBCTestStatus::Passed))));
		FailedText->SetText(FText::FromString(FString::Printf(TEXT("Failed %d"), GetCount(EBCTestStatus::Failed))));
		RemainingText->SetText(FText::FromString(FString::Printf(TEXT("Remaining %d"),
			GetCount(EBCTestStatus::Pending) + GetCount(EBCTestStatus::Running))));
	}
	if (!bFilterInitialized && FilterBox.IsValid())
	{
		FilterBox->SetText(FText::FromString(RunnerPtr->GetFilter()));
		bFilterInitialized = true;
	}
	if (RunnerPtr->GetRevision() == ShownRevision || InCurrentTime - LastRebuildTime < GMinRebuildInterval)
	{
		return;
	}
	ShownRevision = RunnerPtr->GetRevision();
	LastRebuildTime = InCurrentTime;
	RebuildTests();
	if (bLogVisible)
	{
		RebuildLog();
	}

	int32 Errors = 0;
	for (const FBCTestLogLine& Line : RunnerPtr->GetLog())
	{
		Errors += Line.Verbosity <= ELogVerbosity::Error ? 1 : 0;
	}
	if (LogsButtonText.IsValid())
	{
		LogsButtonText->SetText(FText::FromString(Errors > 0 ? FString::Printf(TEXT("Logs (%d)"), Errors) : FString(TEXT("Logs"))));
	}
}

int32 SBCTestRunnerOverlay::GetCount(EBCTestStatus Status) const
{
	int32 Count = 0;
	if (const UBCTestRunnerSubsystem* RunnerPtr = Runner.Get())
	{
		for (const FBCTestEntry& Entry : RunnerPtr->GetTests())
		{
			Count += Entry.Status == Status ? 1 : 0;
		}
	}
	return Count;
}

void SBCTestRunnerOverlay::RebuildTests()
{
	const UBCTestRunnerSubsystem* RunnerPtr = Runner.Get();
	if (!RunnerPtr || !TestList.IsValid())
	{
		return;
	}
	TestList->ClearChildren();

	if (RunnerPtr->GetTests().Num() == 0)
	{
		TestList->AddSlot()
		[
			SNew(STextBlock).Text(FText::FromString(TEXT("No tests match the filter."))).Font(Font(14)).ColorAndOpacity(GDim)
		];
		return;
	}

	for (const FBCTestEntry& Entry : RunnerPtr->GetTests())
	{
		int32 PassedOps = 0;
		for (const FBCTestOperation& Op : Entry.Operations)
		{
			PassedOps += Op.bPassed ? 1 : 0;
		}
		const FString Detail = Entry.Status == EBCTestStatus::Pending ? FString()
			: FString::Printf(TEXT("%d/%d calls   %.1fs"), PassedOps, Entry.Operations.Num(),
				Entry.Status == EBCTestStatus::Running ? FPlatformTime::Seconds() - Entry.StartTime : Entry.Duration);

		TSharedRef<SWidget> Row = SNew(SButton)
			.ButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("NoBorder"))
			.OnClicked(FOnClicked::CreateSP(this, &SBCTestRunnerOverlay::HandleTestClicked, Entry.FullPath))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 12.f, 0.f)
				[
					SNew(SBox).WidthOverride(56.f)
					[
						SNew(STextBlock).Text(StatusLabel(Entry.Status)).Font(Font(14, true)).ColorAndOpacity(StatusColor(Entry.Status))
					]
				]
				+ SHorizontalBox::Slot().FillWidth(1.f)
				[
					SNew(STextBlock).Text(FText::FromString(Entry.DisplayName)).Font(Font(14)).ColorAndOpacity(GText)
				]
				+ SHorizontalBox::Slot().AutoWidth()
				[
					SNew(STextBlock).Text(FText::FromString(Detail)).Font(Font(12)).ColorAndOpacity(GDim)
				]
			];
		TestList->AddSlot().Padding(0.f, 2.f)
		[
			Row
		];
		// Follow the run so the current test stays on screen.
		if (Entry.Status == EBCTestStatus::Running && Entry.FullPath != ScrolledTo)
		{
			ScrolledTo = Entry.FullPath;
			TestList->ScrollDescendantIntoView(Row, true, EDescendantScrollDestination::Center);
		}

		if (!Expanded.Contains(Entry.FullPath))
		{
			continue;
		}
		for (const FBCTestOperation& Op : Entry.Operations)
		{
			TestList->AddSlot().Padding(68.f, 0.f, 0.f, 0.f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(FString::Printf(TEXT("%s  %s"), Op.bPassed ? TEXT("ok  ") : TEXT("FAIL"), *Op.Name)))
				.Font(Font(12))
				.ColorAndOpacity(Op.bPassed ? GPass : GFail)
			];
		}
		for (const FString& Error : Entry.Errors)
		{
			TestList->AddSlot().Padding(68.f, 0.f, 0.f, 0.f)
			[
				SNew(STextBlock).Text(FText::FromString(Error)).Font(Font(12)).ColorAndOpacity(GFail).AutoWrapText(true)
			];
		}
	}
}

void SBCTestRunnerOverlay::RebuildLog()
{
	const UBCTestRunnerSubsystem* RunnerPtr = Runner.Get();
	if (!RunnerPtr || !LogList.IsValid())
	{
		return;
	}
	LogList->ClearChildren();
	for (const FBCTestLogLine& Line : RunnerPtr->GetLog())
	{
		if (bErrorsOnly && Line.Verbosity > ELogVerbosity::Error)
		{
			continue;
		}
		const FLinearColor Color = Line.Verbosity <= ELogVerbosity::Error ? GFail
			: (Line.Verbosity == ELogVerbosity::Warning ? GWarningColor : GText);
		const FString Text = Line.TestName.IsEmpty() ? Line.Text : FString::Printf(TEXT("[%s] %s"), *Line.TestName, *Line.Text);
		LogList->AddSlot().Padding(0.f, 1.f)
		[
			SNew(STextBlock).Text(FText::FromString(Text)).Font(Font(12)).ColorAndOpacity(Color).AutoWrapText(true)
		];
	}
	LogList->ScrollToEnd();
}

FReply SBCTestRunnerOverlay::HandleRunClicked()
{
	if (UBCTestRunnerSubsystem* RunnerPtr = Runner.Get())
	{
		RunnerPtr->RunTests(FilterBox.IsValid() ? FilterBox->GetText().ToString() : RunnerPtr->GetFilter());
	}
	return FReply::Handled();
}

FReply SBCTestRunnerOverlay::HandleLogsClicked()
{
	bLogVisible = !bLogVisible;
	if (bLogVisible)
	{
		RebuildLog();
	}
	return FReply::Handled();
}

FReply SBCTestRunnerOverlay::HandleErrorsOnlyClicked()
{
	bErrorsOnly = !bErrorsOnly;
	if (ErrorsOnlyText.IsValid())
	{
		ErrorsOnlyText->SetText(FText::FromString(bErrorsOnly ? TEXT("Errors only") : TEXT("All warnings")));
	}
	RebuildLog();
	return FReply::Handled();
}

FReply SBCTestRunnerOverlay::HandleClearLogClicked()
{
	if (UBCTestRunnerSubsystem* RunnerPtr = Runner.Get())
	{
		RunnerPtr->ClearLog();
	}
	RebuildLog();
	return FReply::Handled();
}

FReply SBCTestRunnerOverlay::HandleTestClicked(FString FullPath)
{
	if (Expanded.Contains(FullPath))
	{
		Expanded.Remove(FullPath);
	}
	else
	{
		Expanded.Add(FullPath);
	}
	RebuildTests();
	return FReply::Handled();
}
