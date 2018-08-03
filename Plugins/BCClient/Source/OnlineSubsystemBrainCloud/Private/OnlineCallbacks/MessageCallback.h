// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "AssignableServerCallback.h"
#include "OnlineMessageInterfaceBrainCloud.h"
#include "OnlineStats.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(OnMessageSuccess, const FString&, const FUniqueMessageId&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(OnMessageFail, int32, const FString&, const FUniqueMessageId&);

class MessageCallback : public AssignableServerCallback
{
public:
    MessageCallback(const FUniqueMessageId& messageId);
    virtual ~MessageCallback() {};

    OnMessageSuccess OnSuccessDelegate;
    OnMessageFail OnFailDelegate;

    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface

private:
    const FUniqueMessageId& _messageId;
};

