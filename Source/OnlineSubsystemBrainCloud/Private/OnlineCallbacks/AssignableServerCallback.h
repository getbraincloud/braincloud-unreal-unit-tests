// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IServerCallback.h"
#include <functional>

class FOnlineLeaderboardsBrainCloud;

DECLARE_MULTICAST_DELEGATE_OneParam(OnSuccess, const FString&);
DECLARE_MULTICAST_DELEGATE_TwoParams(OnFail, int32, const FString&);

class AssignableServerCallback : public IServerCallback
{
    //typedef TFunctionRef <void(ServiceName, ServiceOperation, const TCHAR*)> OnSuccessFuncPtr;
    //typedef TFunctionRef <void(ServiceName, ServiceOperation, int, const TCHAR*)> OnFailFuncPtr;

public:
    AssignableServerCallback() = default;
    //AssignableServerCallback(OnSuccessFuncPtr successFunc, OnFailFuncPtr failureFunc);
    ~AssignableServerCallback();

    bool IsComplete() { return _isComplete; }

    OnSuccess OnSuccessDelegate;
    OnFail OnFailDelegate;

    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface

protected:
    bool _isComplete = false;

private:
    //OnSuccessFuncPtr successFunc = nullptr;
    //OnFailFuncPtr failureFunc = nullptr;
};
