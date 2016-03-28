// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudGlobalApp.h"

#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
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