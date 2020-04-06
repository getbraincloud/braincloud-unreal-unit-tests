// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "Interfaces/OnlineTimeInterface.h"
#include "OnlineSubsystemBrainCloudPackage.h"

/**
 * Info associated with an online friend on the Steam service
 */
class FOnlineTimeBrainCloud : public IOnlineTime
{
    /** Reference to the owning subsystem */
    class FOnlineSubsystemBrainCloud* _subysystem;

    FString _lastServerUtcTime = TEXT("");

    void OnQueryTimeComplete(const FString& jsonData);
    void OnQueryTimeFail(int32 returnCode, const FString& jsonData);

public:

    /**
     * Init/default constructor
     */
    FOnlineTimeBrainCloud(class FOnlineSubsystemBrainCloud* brainCloudSubsystem);

    /** Virtual destructor to keep clang happy */
    virtual ~FOnlineTimeBrainCloud() {};

    /**
     * Send request for current UTC time from the server
     *
     * @return true if the query was started
     */
    virtual bool QueryServerUtcTime() override;

    /**
     * Retrieve cached timestamp from last server time query 
     *
     * @return string representation of time (yyyy.MM.dd-HH.mm.ss)
     */
    virtual FString GetLastServerUtcTime() override;
};

typedef TSharedPtr<FOnlineTimeBrainCloud, ESPMode::ThreadSafe> FOnlineTimeBrainCloudPtr;