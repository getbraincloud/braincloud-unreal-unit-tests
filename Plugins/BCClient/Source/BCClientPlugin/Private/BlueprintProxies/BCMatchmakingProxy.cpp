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

UBCMatchmakingProxy* UBCMatchmakingProxy::Read(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->read(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::SetPlayerRating(UBrainCloudWrapper *brainCloudWrapper, int32 playerRating)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->setPlayerRating(playerRating, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::ResetPlayerRating(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->resetPlayerRating(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::IncrementPlayerRating(UBrainCloudWrapper *brainCloudWrapper, int32 increment)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->incrementPlayerRating(increment, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::DecrementPlayerRating(UBrainCloudWrapper *brainCloudWrapper, int32 decrement)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->decrementPlayerRating(decrement, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOn(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->turnShieldOn(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOnFor(UBrainCloudWrapper *brainCloudWrapper, int32 minutes)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->turnShieldOnFor(minutes, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::TurnShieldOff(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->turnShieldOff(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::IncrementShieldOnFor(UBrainCloudWrapper *brainCloudWrapper, int32 minutes)
{
	UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->incrementShieldOnFor(minutes, Proxy);
	return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::FindPlayers(UBrainCloudWrapper *brainCloudWrapper, int32 rangeDelta, int32 numMatches)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->findPlayers(rangeDelta, numMatches, Proxy);
    return Proxy;
}

UBCMatchmakingProxy * UBCMatchmakingProxy::FindPlayersWithAttributes(UBrainCloudWrapper *brainCloudWrapper, int32 rangeDelta, int32 numMatches, const FString & jsonAttributes)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->findPlayersWithAttributes(rangeDelta, numMatches, jsonAttributes, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::FindPlayersUsingFilter(UBrainCloudWrapper *brainCloudWrapper, int32 rangeDelta, int32 numMatches, const FString& jsonExtraParms)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->findPlayersUsingFilter(rangeDelta, numMatches, jsonExtraParms, Proxy);
    return Proxy;
}

UBCMatchmakingProxy * UBCMatchmakingProxy::FindPlayersWithAttributesUsingFilter(UBrainCloudWrapper *brainCloudWrapper, int32 rangeDelta, int32 numMatches, const FString & jsonAttributes, const FString & jsonExtraParms)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->findPlayersWithAttributesUsingFilter(rangeDelta, numMatches, jsonAttributes, jsonExtraParms, Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::EnableMatchMaking(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->enableMatchMaking(Proxy);
    return Proxy;
}

UBCMatchmakingProxy* UBCMatchmakingProxy::DisableMatchMaking(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCMatchmakingProxy* Proxy = NewObject<UBCMatchmakingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMatchmakingService()->disableMatchMaking(Proxy);
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

