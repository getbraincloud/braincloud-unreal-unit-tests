// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "LeaderboardCallback.h"
#include "OnlineSubsystemBrainCloudPrivatePCH.h"
#include "AssignableServerCallback.h"

#include "ServiceOperation.h"
#include "ServiceName.h"

#include "OnlineLeaderboardInterfaceBrainCloud.h"


LeaderboardCallback::LeaderboardCallback(FOnlineLeaderboardReadRef leaderboardRead) : _leaderboardRead(leaderboardRead)
{
}

//BC Callbacks
void LeaderboardCallback::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    OnSuccessDelegate.Broadcast(jsonData, _leaderboardRead.ToSharedRef());
    _isComplete = true;
}

void LeaderboardCallback::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    OnFailDelegate.Broadcast(reasonCode, jsonError, _leaderboardRead.ToSharedRef());
    _isComplete = true;
}