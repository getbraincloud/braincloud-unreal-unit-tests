// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCScriptProxy.h"

UBCScriptProxy::UBCScriptProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCScriptProxy* UBCScriptProxy::RunScript(ABrainCloud *brainCloud, FString scriptName, FString jsonScriptData)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getScriptService()->runScript(scriptName, jsonScriptData, Proxy);
	return Proxy;
}

UBCScriptProxy* UBCScriptProxy::ScheduleRunScriptUTC(ABrainCloud *brainCloud, FString scriptName, FString jsonScriptData, FDateTime startDateInUTC)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getScriptService()->scheduleRunScriptUTC(scriptName, jsonScriptData, startDateInUTC, Proxy);
	return Proxy;
}

UBCScriptProxy* UBCScriptProxy::ScheduleRunScriptMinutes(ABrainCloud *brainCloud, FString scriptName, FString jsonScriptData, int32 minutesFromNow)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getScriptService()->scheduleRunScriptMinutes(scriptName, jsonScriptData, minutesFromNow, Proxy);
	return Proxy;
}

UBCScriptProxy* UBCScriptProxy::RunParentScript(ABrainCloud *brainCloud, FString scriptName, FString jsonScriptData, FString parentLevel)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getScriptService()->runParentScript(scriptName, jsonScriptData, parentLevel, Proxy);
	return Proxy;
}

UBCScriptProxy* UBCScriptProxy::CancelScheduledScript(ABrainCloud *brainCloud, const FString& jobId)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getScriptService()->cancelScheduledScript(jobId, Proxy);
	return Proxy;
}

UBCScriptProxy * UBCScriptProxy::RunPeerScript(ABrainCloud *brainCloud, const FString & scriptName, const FString & jsonScriptData, const FString & peer)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getScriptService()->runPeerScript(scriptName, jsonScriptData, peer, Proxy);
	return Proxy;
}

UBCScriptProxy * UBCScriptProxy::RunPeerScriptAsync(ABrainCloud *brainCloud, const FString & scriptName, const FString & jsonScriptData, const FString & peer)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getScriptService()->runPeerScriptAsync(scriptName, jsonScriptData, peer, Proxy);
	return Proxy;
}

//callbacks
void UBCScriptProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCScriptProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

