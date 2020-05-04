// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "AssignableServerCallback.h"
#include "OnlineSubsystemBrainCloudPrivatePCH.h"

#include "ServiceOperation.h"
#include "ServiceName.h"

//AssignableServerCallback::AssignableServerCallback(OnSuccessFuncPtr successFunc, OnFailFuncPtr failureFunc)
//    : successFunc(successFunc), failureFunc(failureFunc)
//{
//}

AssignableServerCallback::~AssignableServerCallback()
{
}

//BC Callbacks
void AssignableServerCallback::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    OnSuccessDelegate.Broadcast(jsonData);
    _isComplete = true;
}

void AssignableServerCallback::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    OnFailDelegate.Broadcast(reasonCode, jsonError);
    _isComplete = true;
}