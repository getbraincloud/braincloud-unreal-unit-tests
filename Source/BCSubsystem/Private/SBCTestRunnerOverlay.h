// Copyright 2026 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UBCTestRunnerSubsystem;
enum class EBCTestStatus : uint8;
class SEditableTextBox;
class SScrollBox;
class STextBlock;

/**
 * On-screen test list, run controls and log panel for UBCTestRunnerSubsystem.
 */
class SBCTestRunnerOverlay : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBCTestRunnerOverlay) {}
		SLATE_ARGUMENT(UBCTestRunnerSubsystem*, Runner)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/** Updates the counts, test list and log. Called by the runner every frame. */
	void Refresh();

private:
	void RebuildTests();
	void RebuildLog();
	int32 GetCount(EBCTestStatus Status) const;
	FReply HandleRunClicked();
	FReply HandleLogsClicked();
	FReply HandleErrorsOnlyClicked();
	FReply HandleClearLogClicked();
	FReply HandleTestClicked(FString FullPath);

	TWeakObjectPtr<UBCTestRunnerSubsystem> Runner;
	TSharedPtr<SEditableTextBox> FilterBox;
	TSharedPtr<SScrollBox> TestList;
	TSharedPtr<SScrollBox> LogList;
	TSharedPtr<STextBlock> LogsButtonText;
	TSharedPtr<STextBlock> StateText;
	TSharedPtr<STextBlock> PassedText;
	TSharedPtr<STextBlock> FailedText;
	TSharedPtr<STextBlock> RemainingText;
	TSharedPtr<STextBlock> ErrorsOnlyText;
	TSet<FString> Expanded;
	FString ScrolledTo;
	uint32 ShownRevision = MAX_uint32;
	double LastRebuildTime = 0.0;
	bool bLogVisible = false;
	bool bErrorsOnly = true;
	bool bFilterInitialized = false;
};
