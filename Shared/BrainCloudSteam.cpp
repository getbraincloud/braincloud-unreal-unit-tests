// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudSteam.h"

#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
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
