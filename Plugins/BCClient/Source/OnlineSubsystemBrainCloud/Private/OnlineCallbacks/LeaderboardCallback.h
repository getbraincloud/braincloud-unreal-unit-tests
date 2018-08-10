// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "AssignableServerCallback.h"
#include "OnlineLeaderboardInterfaceBrainCloud.h"
#include "OnlineStats.h"

class FOnlineLeaderboardsBrainCloud;

DECLARE_MULTICAST_DELEGATE_TwoParams(OnLeaderboardSuccess, const FString&, FOnlineLeaderboardReadRef);
DECLARE_MULTICAST_DELEGATE_ThreeParams(OnLeaderboardFail, int32, const FString&, FOnlineLeaderboardReadRef);

class LeaderboardCallback : public AssignableServerCallback
{
public:
    LeaderboardCallback(FOnlineLeaderboardReadRef leaderboardRead);
    virtual ~LeaderboardCallback() {};

    OnLeaderboardSuccess OnSuccessDelegate;
    OnLeaderboardFail OnFailDelegate;

    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface

private:
    FOnlineLeaderboardReadPtr _leaderboardRead;
};

