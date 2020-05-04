// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudTime.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudTime::BrainCloudTime(BrainCloudClient *client) : _client(client){};

void BrainCloudTime::readServerTime(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::Time, ServiceOperation::Read, message, callback);
    _client->sendRequest(sc);
}