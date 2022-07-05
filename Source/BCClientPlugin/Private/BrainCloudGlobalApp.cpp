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

void BrainCloudGlobalApp::readSelectedProperties(const TArray<FString>& in_propertyId, IServerCallback* callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::GlobalAppReadSelectedProperties.getValue(),JsonUtil::arrayToJsonArray(in_propertyId));
    
    ServerCall *sc = new ServerCall(ServiceName::GlobalApp, ServiceOperation::ReadSelectedProperties, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalApp::readPropertiesInCategories(const TArray<FString>& in_categories, IServerCallback* callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::GlobalAppReadPropertiesInCategories.getValue(),JsonUtil::arrayToJsonArray(in_categories));
    
    ServerCall *sc = new ServerCall(ServiceName::GlobalApp, ServiceOperation::ReadPropertiesInCategories, message, callback);
    _client->sendRequest(sc);
}

