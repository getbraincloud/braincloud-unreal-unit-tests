// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BCAsyncMatchProxy.h"

#include "BrainCloudClient.h"
#include "ServiceName.h"
#include "ServiceOperation.h"

UBCAsyncMatchProxy::UBCAsyncMatchProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::CreateMatch(FString jsonOpponentIds, FString pushNotificationMessage)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->createMatch(jsonOpponentIds, pushNotificationMessage, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::CreateMatchWithInitialTurn(FString jsonOpponentIds, FString jsonMatchState, FString pushNotificationMessage,
    FString nextPlayer, FString jsonSummary)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->createMatchWithInitialTurn(jsonOpponentIds, jsonMatchState, pushNotificationMessage, nextPlayer, jsonSummary, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::SubmitTurn(FString ownerId, FString matchId, int32 version, FString jsonMatchState, FString pushNotificationMessage,
    FString nextPlayer, FString jsonSummary, FString jsonStatistics)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->submitTurn(ownerId, matchId, version, jsonMatchState, pushNotificationMessage, nextPlayer, jsonSummary, jsonStatistics, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::UpdateMatchSummaryData(FString ownerId, FString matchId, int32 version, FString jsonSummary)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->updateMatchSummaryData(ownerId, matchId, version, jsonSummary, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::CompleteMatch(FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->completeMatch(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::ReadMatch(FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->readMatch(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::ReadMatchHistory(FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->readMatchHistory(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::FindMatches()
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->findMatches(Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::FindCompleteMatches()
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->findCompleteMatches(Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::AbandonMatch(FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->abandonMatch(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::DeleteMatch(FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    BrainCloudClient::getInstance()->getAsyncMatchService()->deleteMatch(ownerId, matchId, Proxy);
    return Proxy;
}

//callbacks
void UBCAsyncMatchProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCAsyncMatchProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

