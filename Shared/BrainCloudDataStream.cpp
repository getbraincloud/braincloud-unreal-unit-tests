#include <stdio.h>
#include "BrainCloudDataStream.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "StringUtil.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
#include "JsonUtil.h"

namespace BrainCloud {
    
    void BrainCloudDataStream::customPageEvent(const char * in_eventName, const char * in_jsonEventProperties, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::DataStreamEventName.getValue()] = in_eventName;
        
        if (StringUtil::IsOptionalParameterValid(in_jsonEventProperties))
        {
            message[OperationParam::DataStreamEventProperties.getValue()] = BrainCloudClient::jsonStringToValue(in_jsonEventProperties);
        }
        
        ServerCall * sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomPageEvent, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
    }
    
    
    void BrainCloudDataStream::customScreenEvent(const char * in_eventName, const char * in_jsonEventProperties, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::DataStreamEventName.getValue()] = in_eventName;
        
        if (StringUtil::IsOptionalParameterValid(in_jsonEventProperties))
        {
            message[OperationParam::DataStreamEventProperties.getValue()] = BrainCloudClient::jsonStringToValue(in_jsonEventProperties);
        }
        
        ServerCall * sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomScreenEvent, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
    }
    
    
    void BrainCloudDataStream::customTrackEvent(const char * in_eventName, const char * in_jsonEventProperties, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::DataStreamEventName.getValue()] = in_eventName;
        
        if (StringUtil::IsOptionalParameterValid(in_jsonEventProperties))
        {
            message[OperationParam::DataStreamEventProperties.getValue()] = BrainCloudClient::jsonStringToValue(in_jsonEventProperties);
        }
        
        ServerCall * sc = new ServerCall(ServiceName::DataStream, ServiceOperation::CustomTrackEvent, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
    }
    
}