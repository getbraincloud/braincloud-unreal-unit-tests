// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BCMatchmakingProxy.h"
#include "BrainCloudWrapper.h"

UBCMatchmakingProxy::UBCMatchmakingProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCMatchmakingProxy* UBCMatchmakingProxy::Read(ABrainCloudActor *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->read(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::SetPlayerRating(ABrainCloudActor *brainCloud, int32 playerRating)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->setPlayerRating(playerRating, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::ResetPlayerRating(ABrainCloudActor *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->resetPlayerRating(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::IncrementPlayerRating(ABrainCloudActor *brainCloud, int32 increment)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->incrementPlayerRating(increment, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::DecrementPlayerRating(ABrainCloudActor *brainCloud, int32 decrement)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->decrementPlayerRating(decrement, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOn(ABrainCloudActor *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->turnShieldOn(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOnFor(ABrainCloudActor *brainCloud, int32 minutes)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->turnShieldOnFor(minutes, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOff(ABrainCloudActor *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->turnShieldOff(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::IncrementShieldOnFor(ABrainCloudActor *brainCloud, int32 minutes)
{
	UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->incrementShieldOnFor(minutes, Proxy);
	return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::FindPlayers(ABrainCloudActor *brainCloud, int32 rangeDelta, int32 numMatches)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->findPlayers(rangeDelta, numMatches, Proxy);
    return Proxy;
}

UBCMatchmakingProxy * UBCMatchmakingProxy::FindPlayersWithAttributes(ABrainCloudActor *brainCloud, int32 rangeDelta, int32 numMatches, const FString & jsonAttributes)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->findPlayersWithAttributes(rangeDelta, numMatches, jsonAttributes, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::FindPlayersUsingFilter(ABrainCloudActor *brainCloud, int32 rangeDelta, int32 numMatches, const FString& jsonExtraParms)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->findPlayersUsingFilter(rangeDelta, numMatches, jsonExtraParms, Proxy);
    return Proxy;
}

UBCMatchmakingProxy * UBCMatchmakingProxy::FindPlayersWithAttributesUsingFilter(ABrainCloudActor *brainCloud, int32 rangeDelta, int32 numMatches, const FString & jsonAttributes, const FString & jsonExtraParms)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->findPlayersWithAttributesUsingFilter(rangeDelta, numMatches, jsonAttributes, jsonExtraParms, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::EnableMatchMaking(ABrainCloudActor *brainCloud)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMatchmakingService()->enableMatchMaking(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::DisableMatchMaking(ABrainCloudActor *brainCloud)
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

