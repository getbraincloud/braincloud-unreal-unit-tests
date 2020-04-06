// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudVirtualCurrency.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudVirtualCurrency::BrainCloudVirtualCurrency(BrainCloudClient *client) : _client(client) {}

void BrainCloudVirtualCurrency::getCurrency(const FString &in_vcId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    if (OperationParam::isOptionalParamValid(in_vcId))
    {
        message->SetStringField(OperationParam::VirtualCurrencyVcId.getValue(), in_vcId);
    }

    ServerCall *sc = new ServerCall(ServiceName::VirtualCurrency, ServiceOperation::GetPlayerCurrency, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudVirtualCurrency::getParentCurrency(const FString &in_vcId, const FString &in_levelName, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    if (OperationParam::isOptionalParamValid(in_vcId))
    {
        message->SetStringField(OperationParam::VirtualCurrencyVcId.getValue(), in_vcId);
    }
    message->SetStringField(OperationParam::VirtualCurrencyLevelName.getValue(), in_levelName);

    ServerCall *sc = new ServerCall(ServiceName::VirtualCurrency, ServiceOperation::GetParentCurrency, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudVirtualCurrency::getPeerCurrency(const FString &in_vcId, const FString &in_peerCode, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    if (OperationParam::isOptionalParamValid(in_vcId))
    {
        message->SetStringField(OperationParam::VirtualCurrencyVcId.getValue(), in_vcId);
    }
    message->SetStringField(OperationParam::VirtualCurrencyPeerCode.getValue(), in_peerCode);

    ServerCall *sc = new ServerCall(ServiceName::VirtualCurrency, ServiceOperation::GetPeerCurrency, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudVirtualCurrency::awardCurrency(const FString &currencyType, int32 amount, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::VirtualCurrencyVcId.getValue(), currencyType);
    message->SetNumberField(OperationParam::VirtualCurrencyAmount.getValue(), amount);

    ServerCall *sc = new ServerCall(ServiceName::VirtualCurrency, ServiceOperation::AwardVirtualCurrency, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudVirtualCurrency::consumeCurrency(const FString &currencyType, int32 amount, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::VirtualCurrencyVcId.getValue(), currencyType);
    message->SetNumberField(OperationParam::VirtualCurrencyAmount.getValue(), amount);

    ServerCall *sc = new ServerCall(ServiceName::VirtualCurrency, ServiceOperation::ConsumeVirtualCurrency, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudVirtualCurrency::resetCurrency(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::VirtualCurrency, ServiceOperation::ResetPlayerVC, message, callback);
    _client->sendRequest(sc);
}
