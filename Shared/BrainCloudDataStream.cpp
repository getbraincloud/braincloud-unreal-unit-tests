// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudDataStream.h"

#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
#include "json/json.h"

#include "StringUtil.h"
#include "JsonUtil.h"

namespace BrainCloud
{
    BrainCloudDataStream::BrainCloudDataStream(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudDataStream::customPageEvent(const char * in_eventName, const char * in_jsonEventProperties, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::DataStreamEventName.getValue()] = in_eventName;

        if (StringUtil::IsOptionalParameterValid(in_jsonEventProperties)) {
            message[OperationParam::DataStreamEventProperties.getValue()] = JsonUtil::jsonStringToValue(in_jsonEventProperties);
        }

        ServerCall * sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomPageEvent, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudDataStream::customScreenEvent(const char * in_eventName, const char * in_jsonEventProperties, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::DataStreamEventName.getValue()] = in_eventName;

        if (StringUtil::IsOptionalParameterValid(in_jsonEventProperties)) {
            message[OperationParam::DataStreamEventProperties.getValue()] = JsonUtil::jsonStringToValue(in_jsonEventProperties);
        }

        ServerCall * sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomScreenEvent, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudDataStream::customTrackEvent(const char * in_eventName, const char * in_jsonEventProperties, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::DataStreamEventName.getValue()] = in_eventName;

        if (StringUtil::IsOptionalParameterValid(in_jsonEventProperties)) {
            message[OperationParam::DataStreamEventProperties.getValue()] = JsonUtil::jsonStringToValue(in_jsonEventProperties);
        }

        ServerCall * sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomTrackEvent, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }
}