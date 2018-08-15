// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IFileUploadCallback.h"
#include "IEventCallback.h"
#include "IRewardCallback.h"
#include "IRTTCallback.h"
#include "IGlobalErrorCallback.h"
#include "INetworkErrorCallback.h"

#include "BrainCloudCallbackHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBCFileCallbackCompletedDelegate, const FString &, fileUploadId, const FString &, jsonResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FBCFileCallbackFailedDelegate, const FString &, fileUploadId, int32, statusCode, int32, reasonCode, const FString &, jsonResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCRewardDelegate, const FString &, jsonData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCEventDelegate, const FString &, jsonData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCRTTDelegate, const FString &, jsonData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FBCGlobalErrorDelegate, const FString &, serviceName, const FString &, serviceOperation, int32, statusCode, int32, reasonCode, const FString &, jsonResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBCNetworkErrorDelegate);

class UBrainCloudWrapper;
class ServiceName;
class ServiceOperation;

UCLASS(BlueprintType)
class UBrainCloudCallbackHandler : public UObject, public IFileUploadCallback, 
                                   public IEventCallback, public IRewardCallback, 
                                   public IGlobalErrorCallback, public INetworkErrorCallback, 
                                   public IRTTCallback
{
  GENERATED_BODY()

public:
  UBrainCloudCallbackHandler(const FObjectInitializer &ObjectInitializer);

  virtual void BeginDestroy() override;

  /**
    * Register for NON-realtime event callbacks
    * Global error, network handling etc
    */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Callback Handling")
  void RegisterCallbacks(UBrainCloudWrapper *brainCloudWrapper, bool fileCallbacks = true, bool rewardCallback = true,
                         bool eventCallback = true, bool globalErrorCallback = true, bool networkErrorCallback = true);

  /**
    * Register for Real Time Tech EVENT callbacks
    */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Callback Handling")
  void RegisterRTTEventCallback(UBrainCloudWrapper *brainCloudWrapper);

  /**
    * Deregister for Real Time Tech EVENT callbacks
    */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Callback Handling")
  void DeregisterRTTEventCallback(UBrainCloudWrapper *brainCloudWrapper);

  /**
    * Register for Real Time Tech CHAT callbacks
    */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Callback Handling")
  void RegisterRTTChatCallback(UBrainCloudWrapper *brainCloudWrapper);

  /**
    * Deregister for Real Time Tech CHAT callbacks
    */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Callback Handling")
  void DeregisterRTTChatCallback(UBrainCloudWrapper *brainCloudWrapper);

  /**
    * Register for Real Time Tech MESSAGING callbacks
    */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Callback Handling")
  void RegisterRTTMessagingCallback(UBrainCloudWrapper *brainCloudWrapper);

  /**
    * Deregister for Real Time Tech MESSAGING callbacks
    */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Callback Handling")
  void DeregisterRTTMessagingCallback(UBrainCloudWrapper *brainCloudWrapper);

  /**
    * Register for Real Time Tech LOBBY callbacks
    */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Callback Handling")
  void RegisterRTTLobbyCallback(UBrainCloudWrapper *brainCloudWrapper);

  /**
    * Deregister for Real Time Tech LOBBY callbacks
    */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Callback Handling")
  void DeregisterRTTLobbyCallback(UBrainCloudWrapper *brainCloudWrapper);

  //Response delegates
  UPROPERTY(BlueprintAssignable)
  FBCFileCallbackCompletedDelegate FileUploadComplete;

  UPROPERTY(BlueprintAssignable)
  FBCFileCallbackFailedDelegate FileUploadFailed;

  UPROPERTY(BlueprintAssignable)
  FBCEventDelegate EventCallback;

  UPROPERTY(BlueprintAssignable)
  FBCRewardDelegate RewardCallback;

  UPROPERTY(BlueprintAssignable)
  FBCGlobalErrorDelegate GlobalErrorCallback;

  UPROPERTY(BlueprintAssignable)
  FBCNetworkErrorDelegate NetworkErrorCallback;

  UPROPERTY(BlueprintAssignable)
  FBCRTTDelegate RTTEventCallback;

  UPROPERTY(BlueprintAssignable)
  FBCRTTDelegate RTTChatCallback;

  UPROPERTY(BlueprintAssignable)
  FBCRTTDelegate RTTMessagingCallback;

  UPROPERTY(BlueprintAssignable)
  FBCRTTDelegate RTTLobbyCallback;

protected:
  virtual void rttCallback(const FString &jsonData);
  virtual void fileUploadCompleted(const FString &fileUploadId, const FString &jsonResponse);
  virtual void fileUploadFailed(const FString &fileUploadId, int32 statusCode, int32 reasonCode, const FString &jsonResponse);

  virtual void rewardCallback(const FString &jsonData);
  virtual void eventCallback(const FString &jsonData);

  virtual void globalError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError);

  virtual void networkError();

  UBrainCloudWrapper *_brainCloudWrapper;
};
