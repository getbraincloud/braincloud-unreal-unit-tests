// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudRedemptionCode.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudRedemptionCode::BrainCloudRedemptionCode(BrainCloudClient *client) : _client(client){};

void BrainCloudRedemptionCode::redeemCode(const FString &scanCode, const FString &codeType, const FString &customRedemptionInfo, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    message->SetStringField(OperationParam::RedemptionCodeServiceScanCode.getValue(), scanCode);
    message->SetStringField(OperationParam::RedemptionCodeServiceCodeType.getValue(), codeType);
    if (OperationParam::isOptionalParamValid(customRedemptionInfo))
        message->SetStringField(OperationParam::RedemptionCodeServiceCustomRedemptionInfo.getValue(), customRedemptionInfo);

    ServerCall *sc = new ServerCall(ServiceName::RedemptionCode, ServiceOperation::RedeemCode, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudRedemptionCode::getRedeemedCodes(const FString &codeType, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    if (OperationParam::isOptionalParamValid(codeType))
        message->SetStringField(OperationParam::RedemptionCodeServiceCodeType.getValue(), codeType);

    ServerCall *sc = new ServerCall(ServiceName::RedemptionCode, ServiceOperation::GetRedeemedCodes, message, callback);
    _client->sendRequest(sc);
}