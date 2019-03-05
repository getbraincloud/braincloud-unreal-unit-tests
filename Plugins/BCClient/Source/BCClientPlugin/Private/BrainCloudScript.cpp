// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudScript.h"

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

void BrainCloudScript::scheduleRunScriptUTC(const FString &scriptName, const FString &jsonScriptData, const struct FDateTime startDateInUTC, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ScriptServiceRunScriptName.getValue(), scriptName);
    if (OperationParam::isOptionalParamValid(jsonScriptData))
    {
        message->SetObjectField(OperationParam::ScriptServiceRunScriptData.getValue(), JsonUtil::jsonStringToValue(jsonScriptData));
    }
    message->SetNumberField(OperationParam::ScriptServiceStartDateUTC.getValue(), startDateInUTC.ToUnixTimestamp() * 1000);

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
