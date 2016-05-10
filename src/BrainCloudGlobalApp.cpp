// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudGlobalApp.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

namespace BrainCloud
{
    BrainCloudGlobalApp::BrainCloudGlobalApp(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudGlobalApp::readProperties(IServerCallback * in_callback)
    {
        Json::Value message = Json::nullValue;
        ServerCall * sc = new ServerCall(ServiceName::GlobalApp, ServiceOperation::ReadProperties, message, in_callback);
        m_client->sendRequest(sc);
    }
}