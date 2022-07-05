// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "MessageCallback.h"
#include "OnlineSubsystemBrainCloudPrivatePCH.h"
#include "AssignableServerCallback.h"

#include "ServiceOperation.h"
#include "ServiceName.h"
#include "OnlineMessageInterfaceBrainCloud.h"

MessageCallback::MessageCallback(const FUniqueMessageId& messageId) 
    : _messageId(messageId)
{
}

//BC Callbacks
void MessageCallback::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    OnSuccessDelegate.Broadcast(jsonData, _messageId);
    _isComplete = true;
}

void MessageCallback::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    OnFailDelegate.Broadcast(reasonCode, jsonError, _messageId);
    _isComplete = true;
}