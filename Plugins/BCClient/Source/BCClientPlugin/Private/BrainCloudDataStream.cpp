// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudDataStream.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudDataStream::BrainCloudDataStream(BrainCloudClient *client) : _client(client){};

void BrainCloudDataStream::customPageEvent(const FString &eventName, const FString &jsonEventProperties, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::DataStreamEventName.getValue(), eventName);

    if (OperationParam::isOptionalParamValid(jsonEventProperties))
    {
        message->SetObjectField(OperationParam::DataStreamEventProperties.getValue(), JsonUtil::jsonStringToValue(jsonEventProperties));
    }

    ServerCall *sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomPageEvent, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudDataStream::customScreenEvent(const FString &eventName, const FString &jsonEventProperties, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::DataStreamEventName.getValue(), eventName);

    if (OperationParam::isOptionalParamValid(jsonEventProperties))
    {
        message->SetObjectField(OperationParam::DataStreamEventProperties.getValue(), JsonUtil::jsonStringToValue(jsonEventProperties));
    }

    ServerCall *sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomScreenEvent, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudDataStream::customTrackEvent(const FString &eventName, const FString &jsonEventProperties, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::DataStreamEventName.getValue(), eventName);

    if (OperationParam::isOptionalParamValid(jsonEventProperties))
    {
        message->SetObjectField(OperationParam::DataStreamEventProperties.getValue(), JsonUtil::jsonStringToValue(jsonEventProperties));
    }

    ServerCall *sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomTrackEvent, message, callback);
    _client->sendRequest(sc);
}

  void BrainCloudDataStream::submitCrashReport(const FString &crashType, const FString &errorMsg, const FString &crashJson, const FString &crashLog, const FString &userName, const FString &userEmail, const FString &userNotes, bool userSubmitted, IServerCallback *callback)
  {
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::DataStreamCrashType.getValue(), crashType);
    message->SetStringField(OperationParam::DataStreamErrorMsg.getValue(), errorMsg);
    message->SetObjectField(OperationParam::DataStreamCrashJson.getValue(), JsonUtil::jsonStringToValue(crashJson));
    message->SetStringField(OperationParam::DataStreamCrashLog.getValue(), crashLog);
    message->SetStringField(OperationParam::DataStreamUserName.getValue(), userName);
    message->SetStringField(OperationParam::DataStreamUserEmail.getValue(), userEmail);
    message->SetStringField(OperationParam::DataStreamUserNotes.getValue(), userNotes);
    message->SetBoolField(OperationParam::DataStreamUserSubmitted.getValue(), userSubmitted);
      
    ServerCall *sc = new ServerCall(ServiceName::DataStream, ServiceOperation::SubmitCrashReport, message, callback);
    _client->sendRequest(sc);
  }

