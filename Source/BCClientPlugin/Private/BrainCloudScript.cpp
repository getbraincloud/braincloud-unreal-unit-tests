// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudScript.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudScript::BrainCloudScript(BrainCloudClient *client) : _client(client){};

void BrainCloudScript::runScript(const FString &scriptName, const FString &jsonScriptData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ScriptServiceRunScriptName.getValue(), scriptName);
    if (OperationParam::isOptionalParamValid(jsonScriptData))
    {
        message->SetObjectField(OperationParam::ScriptServiceRunScriptData.getValue(), JsonUtil::jsonStringToValue(jsonScriptData));
    }

    ServerCall *sc = new ServerCall(ServiceName::Script, ServiceOperation::Run, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudScript::scheduleRunScriptMillisUTC(const FString &scriptName, const FString &jsonScriptData, int64 startDateInUTC, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ScriptServiceRunScriptName.getValue(), scriptName);
    if (OperationParam::isOptionalParamValid(jsonScriptData))
    {
        message->SetObjectField(OperationParam::ScriptServiceRunScriptData.getValue(), JsonUtil::jsonStringToValue(jsonScriptData));
    }
    message->SetNumberField(OperationParam::ScriptServiceStartDateUTC.getValue(), startDateInUTC);

    ServerCall *sc = new ServerCall(ServiceName::Script, ServiceOperation::ScheduleCloudScript, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudScript::scheduleRunScriptMinutes(const FString &scriptName, const FString &jsonScriptData, int32 minutesFromNow, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ScriptServiceRunScriptName.getValue(), scriptName);
    if (OperationParam::isOptionalParamValid(jsonScriptData))
    {
        message->SetObjectField(OperationParam::ScriptServiceRunScriptData.getValue(), JsonUtil::jsonStringToValue(jsonScriptData));
    }
    message->SetNumberField(OperationParam::ScriptServiceStartMinutesFromNow.getValue(), minutesFromNow);

    ServerCall *sc = new ServerCall(ServiceName::Script, ServiceOperation::ScheduleCloudScript, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudScript::runParentScript(const FString &scriptName, const FString &jsonScriptData, const FString &parentLevel, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    message->SetStringField(OperationParam::ScriptServiceRunScriptName.getValue(), scriptName);
    if (OperationParam::isOptionalParamValid(jsonScriptData))
    {
        message->SetObjectField(OperationParam::ScriptServiceRunScriptData.getValue(), JsonUtil::jsonStringToValue(jsonScriptData));
    }

    message->SetStringField(OperationParam::ScriptServiceParentLevelName.getValue(), parentLevel);

    ServerCall *sc = new ServerCall(ServiceName::Script, ServiceOperation::RunParentScript, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudScript::cancelScheduledScript(const FString &jobId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ScriptServiceJobId.getValue(), jobId);

    ServerCall *sc = new ServerCall(ServiceName::Script, ServiceOperation::CancelScheduledScript, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudScript::runPeerScript(const FString &scriptName, const FString &jsonScriptData, const FString &peer, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ScriptServiceRunScriptName.getValue(), scriptName);
    message->SetStringField(OperationParam::Peer.getValue(), peer);
    if (OperationParam::isOptionalParamValid(jsonScriptData))
    {
        message->SetObjectField(OperationParam::ScriptServiceRunScriptData.getValue(), JsonUtil::jsonStringToValue(jsonScriptData));
    }

    ServerCall *sc = new ServerCall(ServiceName::Script, ServiceOperation::RunPeerScript, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudScript::runPeerScriptAsync(const FString &scriptName, const FString &jsonScriptData, const FString &peer, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ScriptServiceRunScriptName.getValue(), scriptName);
    message->SetStringField(OperationParam::Peer.getValue(), peer);
    if (OperationParam::isOptionalParamValid(jsonScriptData))
    {
        message->SetObjectField(OperationParam::ScriptServiceRunScriptData.getValue(), JsonUtil::jsonStringToValue(jsonScriptData));
    }

    ServerCall *sc = new ServerCall(ServiceName::Script, ServiceOperation::RunPeerScriptAsync, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudScript::getRunningOrQueuedCloudScripts(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::Script, ServiceOperation::GetRunningOrQueuedCloudScripts, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudScript::getScheduledCloudScripts(const struct FDateTime startDateInUTC, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetNumberField(OperationParam::ScriptServiceStartDateUTC.getValue(), startDateInUTC.ToUnixTimestamp() * 1000);
    ServerCall *sc = new ServerCall(ServiceName::Script, ServiceOperation::GetScheduledCloudSripts, message, callback);
    _client->sendRequest(sc);
}

