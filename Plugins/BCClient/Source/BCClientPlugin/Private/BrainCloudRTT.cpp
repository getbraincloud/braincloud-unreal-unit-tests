// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudRTT.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudRTT::BrainCloudRTT(BrainCloudClient* client) : _client(client) {};

void BrainCloudRTT::requestClientConnection(IServerCallback* callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall * sc = new ServerCall(ServiceName::RTTRegistration, ServiceOperation::RequestClientConnection, message, callback);
    _client->sendRequest(sc);
}