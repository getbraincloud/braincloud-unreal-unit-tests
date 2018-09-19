// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudVirtualCurrency.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudVirtualCurrency::BrainCloudVirtualCurrency(BrainCloudClient* client) : _client(client) {}

    void BrainCloudVirtualCurrency::getCurrency(const FString& in_vcId, IServerCallback * callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	    message->SetStringField(OperationParam::VcId.getValue(), in_vcId);

        ServerCall * sc = new ServerCall(ServiceName::VirtualCurrency, ServiceOperation::GetCurrency, message, callback);
	    _client->sendRequest(sc);
    }

    void BrainCloudVirtualCurrency::getParentCurrency(const FString& in_vcId, const FString& in_levelName, IServerCallback * callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	    message->SetStringField(OperationParam::VcId.getValue(), in_vcId);
        message->SetStringField(OperationParam::LevelName.getValue(), in_levelName);

        ServerCall * sc = new ServerCall(ServiceName::VirtualCurrency, ServiceOperation::GetParentCurrency, message, callback);
	    _client->sendRequest(sc);
    }

    void BrainCloudVirtualCurrency::getPeerCurrency(const FString& in_vcId,const FString& in_peerCode, IServerCallback * callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	    message->SetStringField(OperationParam::VcId.getValue(), in_vcId);
        message->SetStringField(OperationParam::PeerCode.getValue(), in_peerCode);

        ServerCall * sc = new ServerCall(ServiceName::VirtualCurrency, ServiceOperation::GetPeerCurrency, message, callback);
	    _client->sendRequest(sc);
    }
