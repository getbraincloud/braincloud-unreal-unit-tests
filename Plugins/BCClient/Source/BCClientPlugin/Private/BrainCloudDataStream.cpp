// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudDataStream.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudDataStream::BrainCloudDataStream(BrainCloudClient* client) : _client(client) {};

void BrainCloudDataStream::customPageEvent(const FString & eventName, const FString & jsonEventProperties, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::DataStreamEventName.getValue(), eventName);

    if (OperationParam::isOptionalParamValid(jsonEventProperties)) {
        message->SetObjectField(OperationParam::DataStreamEventProperties.getValue(), JsonUtil::jsonStringToValue(jsonEventProperties));
    }

    ServerCall * sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomPageEvent, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudDataStream::customScreenEvent(const FString & eventName, const FString & jsonEventProperties, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::DataStreamEventName.getValue(), eventName);

    if (OperationParam::isOptionalParamValid(jsonEventProperties)) {
        message->SetObjectField(OperationParam::DataStreamEventProperties.getValue(), JsonUtil::jsonStringToValue(jsonEventProperties));
    }

    ServerCall * sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomScreenEvent, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudDataStream::customTrackEvent(const FString & eventName, const FString & jsonEventProperties, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::DataStreamEventName.getValue(), eventName);

    if (OperationParam::isOptionalParamValid(jsonEventProperties)) {
        message->SetObjectField(OperationParam::DataStreamEventProperties.getValue(), JsonUtil::jsonStringToValue(jsonEventProperties));
    }

    ServerCall * sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomTrackEvent, message, callback);
    _client->sendRequest(sc);
}
