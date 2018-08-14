// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "AssignableServerCallback.h"
#include "OnlineStats.h"

class FOnlineAchievementsBrainCloud;

class AchievementCallback : public AssignableServerCallback
{
public:
    DECLARE_MULTICAST_DELEGATE_FiveParams(OnAchievementWriteComplete, bool, const FString&, const FUniqueNetId&, FOnlineAchievementsWritePtr&, const FOnAchievementsWrittenDelegate&);

    AchievementCallback(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate);
    virtual ~AchievementCallback() {};

    OnAchievementWriteComplete OnWriteCompleteDelegate;

    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface

private:
    const FUniqueNetId& _playerId;
    FOnAchievementsWrittenDelegate _writeDelegate;
    FOnlineAchievementsWritePtr _writeObject;
};

class AchievementQueryCallback : public AssignableServerCallback
{
public:
    DECLARE_MULTICAST_DELEGATE_FourParams(OnAchievementQueryComplete, bool, const FString&, const FUniqueNetId*, FOnQueryAchievementsCompleteDelegate&);

    AchievementQueryCallback(const FUniqueNetId* PlayerId, FOnQueryAchievementsCompleteDelegate& Delegate);
    virtual ~AchievementQueryCallback() {};

    OnAchievementQueryComplete OnQueryCompleteDelegate;

    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface

private:
    const FUniqueNetId* _playerId;
    FOnQueryAchievementsCompleteDelegate _queryDelegate;
};

