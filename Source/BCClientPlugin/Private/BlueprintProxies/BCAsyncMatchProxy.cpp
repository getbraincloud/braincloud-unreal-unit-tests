// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCAsyncMatchProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudClient.h"
#include "ServiceName.h"
#include "BrainCloudWrapper.h"
#include "ServiceOperation.h"

UBCAsyncMatchProxy::UBCAsyncMatchProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::CreateMatch(UBrainCloudWrapper *brainCloudWrapper, FString jsonOpponentIds, FString pushNotificationMessage)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->createMatch(jsonOpponentIds, pushNotificationMessage, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::CreateMatchWithInitialTurn(UBrainCloudWrapper *brainCloudWrapper, FString jsonOpponentIds, FString jsonMatchState, FString pushNotificationMessage,
                                                                   FString nextPlayer, FString jsonSummary)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->createMatchWithInitialTurn(jsonOpponentIds, jsonMatchState, pushNotificationMessage, nextPlayer, jsonSummary, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::SubmitTurn(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId, int32 version, FString jsonMatchState, FString pushNotificationMessage,
                                                   FString nextPlayer, FString jsonSummary, FString jsonStatistics)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->submitTurn(ownerId, matchId, version, jsonMatchState, pushNotificationMessage, nextPlayer, jsonSummary, jsonStatistics, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::UpdateMatchSummaryData(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId, int32 version, FString jsonSummary)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->updateMatchSummaryData(ownerId, matchId, version, jsonSummary, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::CompleteMatch(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->completeMatch(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::ReadMatch(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->readMatch(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::ReadMatchHistory(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->readMatchHistory(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::FindMatches(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->findMatches(Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::FindCompleteMatches(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->findCompleteMatches(Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::AbandonMatch(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->abandonMatch(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::DeleteMatch(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->deleteMatch(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::AbandonMatchWithSummaryData(UBrainCloudWrapper *brainCloudWrapper, const FString &ownerId, const FString &matchId, const FString &pushContent, const FString &summary)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->abandonMatchWithSummaryData(ownerId, matchId, pushContent, summary, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy *UBCAsyncMatchProxy::CompleteMatchWithSummaryData(UBrainCloudWrapper *brainCloudWrapper, const FString &ownerId, const FString &matchId, const FString &pushContent, const FString &summary)
{
    UBCAsyncMatchProxy *Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAsyncMatchService()->completeMatchWithSummaryData(ownerId, matchId, pushContent, summary, Proxy);
    return Proxy;
}
