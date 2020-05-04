// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "AchievementCallback.h"
#include "OnlineSubsystemBrainCloudPrivatePCH.h"
#include "AssignableServerCallback.h"

#include "ServiceOperation.h"
#include "ServiceName.h"

#include "OnlineAchievementsInterfaceBrainCloud.h"


AchievementCallback::AchievementCallback(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate)
    : _playerId(PlayerId),
    _writeDelegate(Delegate),
    _writeObject(WriteObject)
{
}

//BC Callbacks
void AchievementCallback::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    OnWriteCompleteDelegate.Broadcast(true, jsonData, _playerId, _writeObject, _writeDelegate);
    _isComplete = true;
}

void AchievementCallback::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    OnWriteCompleteDelegate.Broadcast(false, jsonError, _playerId, _writeObject, _writeDelegate);
    _isComplete = true;
}


AchievementQueryCallback::AchievementQueryCallback(const FUniqueNetId* PlayerId, FOnQueryAchievementsCompleteDelegate& Delegate)
    : _playerId(PlayerId),
    _queryDelegate(Delegate)
{
}

//BC Callbacks
void AchievementQueryCallback::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    OnQueryCompleteDelegate.Broadcast(true, jsonData, _playerId, _queryDelegate);
    _isComplete = true;
}

void AchievementQueryCallback::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    OnQueryCompleteDelegate.Broadcast(false, jsonError, _playerId, _queryDelegate);
    _isComplete = true;
}