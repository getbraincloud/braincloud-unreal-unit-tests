// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudTime.h"

#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
#include "json/json.h"

namespace BrainCloud
{
    BrainCloudTime::BrainCloudTime(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudTime::readServerTime(IServerCallback * in_callback)
    {
        Json::Value nullMsg = Json::nullValue;
        ServerCall * sc = new ServerCall(ServiceName::ServerTime, ServiceOperation::Read, nullMsg, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }
}