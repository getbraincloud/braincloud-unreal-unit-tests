// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCScriptProxy.h"

UBCScriptProxy::UBCScriptProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCScriptProxy* UBCScriptProxy::RunScript(FString scriptName, FString jsonScriptData)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	BrainCloudClient::getInstance()->getScriptService()->runScript(scriptName, jsonScriptData, Proxy);
	return Proxy;
}

UBCScriptProxy* UBCScriptProxy::ScheduleRunScriptUTC(FString scriptName, FString jsonScriptData, FDateTime startDateInUTC)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	BrainCloudClient::getInstance()->getScriptService()->scheduleRunScriptUTC(scriptName, jsonScriptData, startDateInUTC, Proxy);
	return Proxy;
}

UBCScriptProxy* UBCScriptProxy::ScheduleRunScriptMinutes(FString scriptName, FString jsonScriptData, int32 minutesFromNow)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	BrainCloudClient::getInstance()->getScriptService()->scheduleRunScriptMinutes(scriptName, jsonScriptData, minutesFromNow, Proxy);
	return Proxy;
}

UBCScriptProxy* UBCScriptProxy::RunParentScript(FString scriptName, FString jsonScriptData, FString parentLevel)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	BrainCloudClient::getInstance()->getScriptService()->runParentScript(scriptName, jsonScriptData, parentLevel, Proxy);
	return Proxy;
}

UBCScriptProxy* UBCScriptProxy::CancelScheduledScript(const FString& jobId)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	BrainCloudClient::getInstance()->getScriptService()->cancelScheduledScript(jobId, Proxy);
	return Proxy;
}

UBCScriptProxy * UBCScriptProxy::RunPeerScript(const FString & scriptName, const FString & jsonScriptData, const FString & peer)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	BrainCloudClient::getInstance()->getScriptService()->runPeerScript(scriptName, jsonScriptData, peer, Proxy);
	return Proxy;
}

UBCScriptProxy * UBCScriptProxy::RunPeerScriptAsync(const FString & scriptName, const FString & jsonScriptData, const FString & peer)
{
	UBCScriptProxy* Proxy = NewObject<UBCScriptProxy>();
	BrainCloudClient::getInstance()->getScriptService()->runPeerScriptAsync(scriptName, jsonScriptData, peer, Proxy);
	return Proxy;
}

//callbacks
void UBCScriptProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
}

void UBCScriptProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
}

