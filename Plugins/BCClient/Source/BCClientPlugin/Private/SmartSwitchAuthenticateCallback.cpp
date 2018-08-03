// Copyright 2018 bitHeads, Inc. All Rights Reserved.
#include "BCClientPluginPrivatePCH.h"
#include "SmartSwitchAuthenticateCallback.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BrainCloudWrapper.h"

SmartSwitchAuthenticateCallback::SmartSwitchAuthenticateCallback(
    BrainCloudWrapper *in_wrapper, const FString& in_userId, const FString& in_token, bool forceCreate, IServerCallback *in_callback) : BCIdentityCallback(in_wrapper, in_callback)
{
    m_userId = in_userId;
    m_token = in_token;
    m_forceCreate = forceCreate;
}

SmartSwitchAuthenticateCallback::~SmartSwitchAuthenticateCallback()
{}

void SmartSwitchAuthenticateCallback::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const &jsonData)
{
    m_wrapper->getBCClient()->getAuthenticationService()->authenticateEmailPassword(m_userId, m_token, m_forceCreate, m_callback);
    delete this;
}

void SmartSwitchAuthenticateCallback::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
{
    m_callback->serverError(serviceName, serviceOperation, statusCode, reasonCode, jsonError);
    delete this;
}
