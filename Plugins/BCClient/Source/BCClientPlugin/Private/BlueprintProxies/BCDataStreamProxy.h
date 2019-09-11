// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCDataStreamProxy.generated.h"

UCLASS(MinimalAPI)
class UBCDataStreamProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCDataStreamProxy(const FObjectInitializer &ObjectInitializer);

  /**
    * Creates custom data stream page event
    *
    * Param - eventName Name of event
    * Param - eventProperties Properties of event
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|DataStream")
  static UBCDataStreamProxy *CustomPageEvent(UBrainCloudWrapper *brainCloudWrapper, const FString &eventName, const FString &jsonEventProperties);

  /**
    * Creates custom data stream screen event
    *
    * Param - eventName Name of event
    * Param - eventProperties Properties of event
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|DataStream")
  static UBCDataStreamProxy *CustomScreenEvent(UBrainCloudWrapper *brainCloudWrapper, const FString &eventName, const FString &jsonEventProperties);

  /**
    * Creates custom data stream track event
    *
    * Param - eventName Name of event
    * Param - eventProperties Properties of event
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|DataStream")
  static UBCDataStreamProxy *CustomTrackEvent(UBrainCloudWrapper *brainCloudWrapper, const FString &eventName, const FString &jsonEventProperties);

  /**
     * Send crash report
     *
     * @param crashType String the type of crash
     * @param errosMsg String the message to send
     * @param crashJson Json the fields of the crash
     * @param crashLog String log data
     * @param userName
     * @param userEmail
     * @param userNotes
     * @param userSubmitted
     * @param callback The callback object
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|DataStream")
  static UBCDataStreamProxy *SubmitCrashReport(UBrainCloudWrapper *brainCloudWrapper, const FString &crashType, const FString &errorMsg, const FString &crashJson, const FString &crashLog, const FString &userName, const FString &userEmail, const FString &userNotes, bool userSubmitted);

};
