// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCMatchmakingProxy.h"

UBCMatchmakingProxy::UBCMatchmakingProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCMatchmakingProxy* UBCMatchmakingProxy::Read()
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->read(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::SetPlayerRating(int32 playerRating)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->setPlayerRating(playerRating, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::ResetPlayerRating()
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->resetPlayerRating(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::IncrementPlayerRating(int32 increment)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->incrementPlayerRating(increment, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::DecrementPlayerRating(int32 decrement)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->decrementPlayerRating(decrement, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOn()
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->turnShieldOn(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOnFor(int32 minutes)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->turnShieldOnFor(minutes, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOff()
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->turnShieldOff(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::FindPlayers(int32 rangeDelta, int32 numMatches)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->findPlayers(rangeDelta, numMatches, Proxy);
    return Proxy;
}

UBCMatchmakingProxy * UBCMatchmakingProxy::FindPlayersWithAttributes(int32 rangeDelta, int32 numMatches, const FString & jsonAttributes)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->findPlayersWithAttributes(rangeDelta, numMatches, jsonAttributes, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::FindPlayersUsingFilter(int32 rangeDelta, int32 numMatches, const FString& jsonExtraParms)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->findPlayersUsingFilter(rangeDelta, numMatches, jsonExtraParms, Proxy);
    return Proxy;
}

UBCMatchmakingProxy * UBCMatchmakingProxy::FindPlayersWithAttributesUsingFilter(int32 rangeDelta, int32 numMatches, const FString & jsonAttributes, const FString & jsonExtraParms)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->findPlayersWithAttributesUsingFilter(rangeDelta, numMatches, jsonAttributes, jsonExtraParms, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::EnableMatchMaking()
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->enableMatchMaking(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::DisableMatchMaking()
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    BrainCloudClient::getInstance()->getMatchmakingService()->disableMatchMaking(Proxy);
    return Proxy;
}

//callbacks
void UBCMatchmakingProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCMatchmakingProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

