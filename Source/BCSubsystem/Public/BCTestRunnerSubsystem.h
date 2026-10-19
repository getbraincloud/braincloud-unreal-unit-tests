// Copyright 2026 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Containers/Ticker.h"
#include "Runtime/Launch/Resources/Version.h"
#include "BCTestRunnerSubsystem.generated.h"

class SBCTestRunnerOverlay;
class FAutomationTestBase;
class FAutomationTestExecutionInfo;
class SWidget;

/**
 * The state of one test in the runner.
 */
enum class EBCTestStatus : uint8
{
	Pending,
	Running,
	Passed,
	Failed
};

/**
 * One brainCloud call reported by a test.
 */
struct FBCTestOperation
{
	FString Name;
	bool bPassed = false;
};

/**
 * One test and its results.
 */
struct FBCTestEntry
{
	FString DisplayName;
	FString FullPath;
	FString Command;
	EBCTestStatus Status = EBCTestStatus::Pending;
	double StartTime = 0.0;
	double Duration = 0.0;
	TArray<FBCTestOperation> Operations;
	TArray<FString> Errors;
	TArray<FString> Warnings;
};

/**
 * One captured log line.
 */
struct FBCTestLogLine
{
	FString TestName;
	FString Text;
	ELogVerbosity::Type Verbosity = ELogVerbosity::Log;
};

/**
 * Runs the project's automation tests in a packaged build and shows their progress on screen.
 *
 * Enabled on Android and iOS, or on any platform with -BCTestRunner. Pass -BCRunTests=<filter> to
 * start a run as soon as the tests are found, and -BCQuitWhenDone to exit once it finishes.
 * Results are written to Saved/BCTestRunner/results.json.
 */
UCLASS()
class BCSUBSYSTEM_API UBCTestRunnerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/**
	 * Runs every test whose full name contains the filter.
	 *
	 * @param Filter Text to match, e.g. "Test_" or "Test_Identity"
	 */
	void RunTests(const FString& Filter);

	/**
	 * Returns true while tests are running.
	 */
	bool IsRunning() const { return bRunning; }

	const TArray<FBCTestEntry>& GetTests() const { return Tests; }
	const TArray<FBCTestLogLine>& GetLog() const { return LogLines; }
	const FString& GetFilter() const { return CurrentFilter; }

	/**
	 * Increments whenever tests, statuses or the log change, so the UI knows when to refresh.
	 */
	uint32 GetRevision() const { return Revision; }

	void ClearLog();

private:
	class FLogCapture;

	bool Tick(float DeltaTime);
	void DiscoverTests();
	void StartNextTest();
	void DriveCurrentTest();
	void HandleTestEnd(FAutomationTestBase* Test);
	void RecordResult(bool bSuccess, const FAutomationTestExecutionInfo& Info);
	void FinishRun();
	void WriteReport() const;
	void ShowOverlay();
	void HandlePostLoadMap(UWorld* World);
	void HandleCapturedLine(const FString& Text, ELogVerbosity::Type Verbosity, const FName& Category);

	TArray<FBCTestEntry> AllTests;
	TArray<FBCTestEntry> Tests;
	TArray<FBCTestLogLine> LogLines;
	FString CurrentFilter;
	FString AutoRunFilter;
	int32 CurrentIndex = INDEX_NONE;
	bool bDiscovered = false;
	bool bRunning = false;
	bool bLatentDone = false;
	bool bAwaitingEnd = false;
	bool bCurrentEnded = false;
	bool bQuitWhenDone = false;
	uint32 Revision = 0;
	double RunStartTime = 0.0;

	TSharedPtr<FLogCapture> LogCapture;
	TSharedPtr<SBCTestRunnerOverlay> Overlay;
	TSharedPtr<SWidget> OverlayContainer;
#if ENGINE_MAJOR_VERSION >= 5
	FTSTicker::FDelegateHandle TickHandle;
#else
	FDelegateHandle TickHandle;
#endif
	FDelegateHandle PostLoadMapHandle;
	FDelegateHandle TestEndHandle;
};
