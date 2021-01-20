// Copyright 2018 bitHeads, Inc. All Rights Reserved.
#include "SmartSwitchAuthenticateCallback.h"
#include "BCClientPluginPrivatePCH.h"
#include "ServerCall.h"

#include "BrainCloudWrapper.h"

SmartSwitchAuthenticateCallback::SmartSwitchAuthenticateCallback(UBrainCloudWrapper *in_wrapper, EBCAuthType in_authType, const FString &in_userId,
                                                                 const FString &in_token, bool forceCreate, IServerCallback *in_callback) : BCIdentityCallback(in_wrapper, in_callback)
{
    m_userId = in_userId;
    m_token = in_token;
    m_authType = in_authType;
    m_forceCreate = forceCreate;
}

SmartSwitchAuthenticateCallback::SmartSwitchAuthenticateCallback(UBrainCloudWrapper *in_wrapper, EBCAuthType in_authType, const FString &in_userId,
                                                                 const FString &in_token, const FString &in_extraStringDetail, bool forceCreate, IServerCallback *in_callback) : BCIdentityCallback(in_wrapper, in_callback)
{
    m_userId = in_userId;
    m_token = in_token;
    m_extraStringDetail = in_extraStringDetail;
    m_authType = in_authType;
    m_forceCreate = forceCreate;
}

SmartSwitchAuthenticateCallback::~SmartSwitchAuthenticateCallback()
{
}

void SmartSwitchAuthenticateCallback::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const &jsonData)
{
    switch (m_authType)
    {
    default:
    {
        // TODO: throw error? not supported ?
    }
    break;

    case EBCAuthType::Email:
    {
        m_wrapper->getBCClient()->getAuthenticationService()->authenticateEmailPassword(m_userId, m_token, m_forceCreate, m_callback);
    }
    break;

    case EBCAuthType::External:
    {
        m_wrapper->getBCClient()->getAuthenticationService()->authenticateExternal(m_userId, m_token, m_extraStringDetail, m_forceCreate, m_callback);
    }
    break;

    case EBCAuthType::Facebook:
    {
        m_wrapper->getBCClient()->getAuthenticationService()->authenticateFacebook(m_userId, m_token, m_forceCreate, m_callback);
    }
    break;

    case EBCAuthType::PlaystationNetwork:
    {
        m_wrapper->getBCClient()->getAuthenticationService()->authenticatePSN(m_userId, m_token, m_forceCreate, m_callback);
    }
    break;

    case EBCAuthType::GameCenter:
    {
        m_wrapper->getBCClient()->getAuthenticationService()->authenticateGameCenter(m_userId, m_forceCreate, m_callback);
    }
    break;

    case EBCAuthType::Google:
    {
        m_wrapper->getBCClient()->getAuthenticationService()->authenticateGoogle(m_userId, m_token, m_forceCreate, m_callback);
    }
    break;

    case EBCAuthType::Steam:
    {
        m_wrapper->getBCClient()->getAuthenticationService()->authenticateSteam(m_userId, m_token, m_forceCreate, m_callback);
    }
    break;

    case EBCAuthType::Twitter:
    {
        m_wrapper->getBCClient()->getAuthenticationService()->authenticateTwitter(m_userId, m_token, m_extraStringDetail, m_forceCreate, m_callback);
    }
    break;

    case EBCAuthType::Universal:
    {
        m_wrapper->getBCClient()->getAuthenticationService()->authenticateUniversal(m_userId, m_token, m_forceCreate, m_callback);
    }
    break;
    }

    delete this;
}

void SmartSwitchAuthenticateCallback::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
{
    m_callback->serverError(serviceName, serviceOperation, statusCode, reasonCode, jsonError);
    delete this;
}
