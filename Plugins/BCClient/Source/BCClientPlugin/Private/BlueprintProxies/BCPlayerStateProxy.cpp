// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCPlayerStateProxy.h"

UBCPlayerStateProxy::UBCPlayerStateProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStateProxy* UBCPlayerStateProxy::ReadPlayerState()
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->readPlayerState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::DeletePlayer()
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->deletePlayer(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::ResetPlayerState()
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->resetPlayerState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::Logout()
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->logout(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdatePlayerName(FString playerName)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->updatePlayerName(playerName, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateSummaryFriendData(const FString& jsonSummaryData)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->updateSummaryFriendData(jsonSummaryData, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::GetAttributes()
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->getAttributes(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateAttributes(FString jsonAttributes, bool wipeExisting)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->updateAttributes(jsonAttributes, wipeExisting, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::RemoveAttributes(const TArray<FString>& attributeNames)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->removeAttributes(attributeNames, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdatePlayerPictureUrl(const FString& pictureUrl)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->updatePlayerPictureUrl(pictureUrl, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateContactEmail(const FString& contactEmail)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    BrainCloudClient::getInstance()->getPlayerStateService()->updateContactEmail(contactEmail, Proxy);
    return Proxy;
}

//callbacks
void UBCPlayerStateProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCPlayerStateProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

