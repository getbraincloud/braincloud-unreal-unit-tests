// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BCMatchmakingProxy.h"
#include "BrainCloudWrapper.h"

UBCMatchmakingProxy::UBCMatchmakingProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCMatchmakingProxy* UBCMatchmakingProxy::Read(ABrainCloud *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->read(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::SetPlayerRating(ABrainCloud *brainCloud, int32 playerRating)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->setPlayerRating(playerRating, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::ResetPlayerRating(ABrainCloud *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->resetPlayerRating(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::IncrementPlayerRating(ABrainCloud *brainCloud, int32 increment)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->incrementPlayerRating(increment, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::DecrementPlayerRating(ABrainCloud *brainCloud, int32 decrement)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->decrementPlayerRating(decrement, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOn(ABrainCloud *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->turnShieldOn(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOnFor(ABrainCloud *brainCloud, int32 minutes)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->turnShieldOnFor(minutes, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOff(ABrainCloud *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->turnShieldOff(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::FindPlayers(ABrainCloud *brainCloud, int32 rangeDelta, int32 numMatches)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->findPlayers(rangeDelta, numMatches, Proxy);
    return Proxy;
}

UBCMatchmakingProxy * UBCMatchmakingProxy::FindPlayersWithAttributes(ABrainCloud *brainCloud, int32 rangeDelta, int32 numMatches, const FString & jsonAttributes)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->findPlayersWithAttributes(rangeDelta, numMatches, jsonAttributes, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::FindPlayersUsingFilter(ABrainCloud *brainCloud, int32 rangeDelta, int32 numMatches, const FString& jsonExtraParms)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->findPlayersUsingFilter(rangeDelta, numMatches, jsonExtraParms, Proxy);
    return Proxy;
}

UBCMatchmakingProxy * UBCMatchmakingProxy::FindPlayersWithAttributesUsingFilter(ABrainCloud *brainCloud, int32 rangeDelta, int32 numMatches, const FString & jsonAttributes, const FString & jsonExtraParms)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->findPlayersWithAttributesUsingFilter(rangeDelta, numMatches, jsonAttributes, jsonExtraParms, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::EnableMatchMaking(ABrainCloud *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->enableMatchMaking(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::DisableMatchMaking(ABrainCloud *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->disableMatchMaking(Proxy);
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

