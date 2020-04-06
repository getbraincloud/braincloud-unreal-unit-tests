// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudGlobalApp.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudGlobalApp::BrainCloudGlobalApp(BrainCloudClient *client) : _client(client){};

void BrainCloudGlobalApp::readProperties(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::GlobalApp, ServiceOperation::ReadProperties, message, callback);
    _client->sendRequest(sc);
}
