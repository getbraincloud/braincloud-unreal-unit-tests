// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudTime.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
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