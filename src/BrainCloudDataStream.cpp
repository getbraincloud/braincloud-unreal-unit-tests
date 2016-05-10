// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudDataStream.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"

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