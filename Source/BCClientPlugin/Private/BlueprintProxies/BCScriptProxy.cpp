// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCScriptProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCScriptProxy::UBCScriptProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCScriptProxy *UBCScriptProxy::RunScript(UBrainCloudWrapper *brainCloudWrapper, FString scriptName, FString jsonScriptData)
{
	UBCScriptProxy *Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getScriptService()->runScript(scriptName, jsonScriptData, Proxy);
	return Proxy;
}

UBCScriptProxy *UBCScriptProxy::ScheduleRunScriptMillisUTC(UBrainCloudWrapper *brainCloudWrapper, FString scriptName, FString jsonScriptData, int64 startDateInUTC)
{
	UBCScriptProxy *Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getScriptService()->scheduleRunScriptMillisUTC(scriptName, jsonScriptData, startDateInUTC, Proxy);
	return Proxy;
}

UBCScriptProxy *UBCScriptProxy::ScheduleRunScriptMinutes(UBrainCloudWrapper *brainCloudWrapper, FString scriptName, FString jsonScriptData, int32 minutesFromNow)
{
	UBCScriptProxy *Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getScriptService()->scheduleRunScriptMinutes(scriptName, jsonScriptData, minutesFromNow, Proxy);
	return Proxy;
}

UBCScriptProxy *UBCScriptProxy::RunParentScript(UBrainCloudWrapper *brainCloudWrapper, FString scriptName, FString jsonScriptData, FString parentLevel)
{
	UBCScriptProxy *Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getScriptService()->runParentScript(scriptName, jsonScriptData, parentLevel, Proxy);
	return Proxy;
}

UBCScriptProxy *UBCScriptProxy::CancelScheduledScript(UBrainCloudWrapper *brainCloudWrapper, const FString &jobId)
{
	UBCScriptProxy *Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getScriptService()->cancelScheduledScript(jobId, Proxy);
	return Proxy;
}

UBCScriptProxy *UBCScriptProxy::RunPeerScript(UBrainCloudWrapper *brainCloudWrapper, const FString &scriptName, const FString &jsonScriptData, const FString &peer)
{
	UBCScriptProxy *Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getScriptService()->runPeerScript(scriptName, jsonScriptData, peer, Proxy);
	return Proxy;
}

UBCScriptProxy *UBCScriptProxy::RunPeerScriptAsync(UBrainCloudWrapper *brainCloudWrapper, const FString &scriptName, const FString &jsonScriptData, const FString &peer)
{
	UBCScriptProxy *Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getScriptService()->runPeerScriptAsync(scriptName, jsonScriptData, peer, Proxy);
	return Proxy;
}

UBCScriptProxy *UBCScriptProxy::GetRunningOrQueuedCloudScripts(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCScriptProxy *Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getScriptService()->getRunningOrQueuedCloudScripts(Proxy);
	return Proxy;
}

UBCScriptProxy *UBCScriptProxy::GetScheduledCloudScripts(UBrainCloudWrapper *brainCloudWrapper, FDateTime startDateInUTC)
{
	UBCScriptProxy *Proxy = NewObject<UBCScriptProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getScriptService()->getScheduledCloudScripts(startDateInUTC, Proxy);
	return Proxy;
}
