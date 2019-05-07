// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BCLobbyProxy.h"
#include "BrainCloudWrapper.h"

UBCLobbyProxy::UBCLobbyProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCLobbyProxy *UBCLobbyProxy::FindLobby(UBrainCloudWrapper *brainCloud, const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
										const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
										bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->findLobby(in_roomType, in_rating, in_maxSteps, in_algoJson, in_filterJson, in_timeoutSecs, in_isReady, in_extraJson, in_teamCode, in_otherUserCxIds, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::CreateLobby(UBrainCloudWrapper *brainCloud, const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
										  bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
										  const FString &in_configJson, const TArray<FString> &in_otherUserCxIds)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->createLobby(in_roomType, in_rating, in_maxSteps, in_isReady, in_extraJson, in_teamCode, in_configJson, in_otherUserCxIds, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::FindOrCreateLobby(UBrainCloudWrapper *brainCloud, const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
												const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
												bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
												const FString &in_configJson, const TArray<FString> &in_otherUserCxIds)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->findOrCreateLobby(in_roomType, in_rating, in_maxSteps, in_algoJson, in_filterJson, in_timeoutSecs, in_isReady, in_extraJson, in_teamCode, in_configJson, in_otherUserCxIds, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::GetLobbyData(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->getLobbyData(in_lobbyID, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::UpdateReady(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, bool in_isReady,
										  const FString &in_extraJson)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->updateReady(in_lobbyID, in_isReady, in_extraJson, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::SwitchTeam(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, const FString &in_teamCode)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->switchTeam(in_lobbyID, in_teamCode, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::SendSignal(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, const FString &in_signalJson)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->sendSignal(in_lobbyID, in_signalJson, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::JoinLobby(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->joinLobby(in_lobbyID, in_isReady, in_extraJson, in_teamCode, in_otherUserCxIds, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::LeaveLobby(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->leaveLobby(in_lobbyID, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::RemoveMember(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, const FString &in_connectionId)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->removeMember(in_lobbyID, in_connectionId, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::UpdateLobbyConfig(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, const FString &in_configJson)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->updateLobbyConfig(in_lobbyID, in_configJson, Proxy);
	return Proxy;
}

UBCLobbyProxy *UBCLobbyProxy::CancelFindRequest(UBrainCloudWrapper *brainCloud, const FString &in_lobbyType)
{
	UBCLobbyProxy *Proxy = NewObject<UBCLobbyProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLobbyService()->cancelFindRequest(in_lobbyType, Proxy);
	return Proxy;
}
