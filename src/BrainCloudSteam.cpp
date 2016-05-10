// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudSteam.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

namespace BrainCloud
{
    BrainCloudSteam::BrainCloudSteam(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudSteam::getUserInfo(IServerCallback * in_callback)
    {
        ServerCall * sc = new ServerCall(ServiceName::Steam, ServiceOperation::Logout, Json::nullValue, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }
}
