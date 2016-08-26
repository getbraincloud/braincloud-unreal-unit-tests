// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "OnlineSubsystemBrainCloudPrivatePCH.h"
#include "OnlineTimeInterfaceBrainCloud.h"

#include "OnlineSubsystemBrainCloud.h"
#include "BrainCloudClient.h"
#include "AssignableServerCallback.h"

FOnlineTimeBrainCloud::FOnlineTimeBrainCloud(FOnlineSubsystemBrainCloud* brainCloudSubsystem) :
    _subysystem(brainCloudSubsystem)
{
    check(_subysystem);
}

bool FOnlineTimeBrainCloud::QueryServerUtcTime()
{
    AssignableServerCallback* cb = _subysystem->GetCallbackObject<AssignableServerCallback>();
    cb->OnSuccessDelegate.AddRaw(this, &FOnlineTimeBrainCloud::OnQueryTimeComplete);
    cb->OnFailDelegate.AddRaw(this, &FOnlineTimeBrainCloud::OnQueryTimeFail);
    BrainCloudClient::getInstance()->getTimeService()->readServerTime(cb);
    return true;
}

FString FOnlineTimeBrainCloud::GetLastServerUtcTime()
{
    return _lastServerUtcTime;
}

//BC Callbacks
void FOnlineTimeBrainCloud::OnQueryTimeComplete(const FString& jsonData)
{
    uint64 time = FOnlineSubsystemBrainCloud::GetJsonData(jsonData)->GetNumberField("server_time") / 1000;

    _lastServerUtcTime = FDateTime::FromUnixTimestamp(time).ToString();

    OnQueryServerUtcTimeCompleteDelegates.Broadcast(true, _lastServerUtcTime, TEXT(""));
}

void FOnlineTimeBrainCloud::OnQueryTimeFail(int32 returnCode, const FString& jsonData)
{
    OnQueryServerUtcTimeCompleteDelegates.Broadcast(false, TEXT(""), jsonData);
}
