// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudAuthentication.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "braincloud/AuthenticationType.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/GUID.h"

namespace BrainCloud {
    BrainCloudAuthentication::BrainCloudAuthentication(BrainCloudClient* in_client) :
        m_client(in_client),
        _anonymousId(""),
        _profileId("") ,
		_clientLib("cpp")
    {
    }

	void BrainCloudAuthentication::setClientLib(const char * lib)
	{
		if (_clientLib == "obj-c" || _clientLib == "cpp")
			_clientLib = lib;
	}

    void BrainCloudAuthentication::initialize(const char * in_profileId, const char * in_anonymousId)
    {
        _profileId = in_profileId;
        _anonymousId = in_anonymousId;
    }

	std::string BrainCloudAuthentication::generateAnonymousId()
	{
		return BrainCloud::GUID::generateGUID();
	}

    void BrainCloudAuthentication::clearSavedProfileId()
    {
        _profileId = "";
    }

    void BrainCloudAuthentication::authenticateAnonymous(bool in_forceCreate, IServerCallback * in_callback)
    {
        authenticate(_anonymousId.c_str(), "", AuthenticationType::Anonymous, NULL, in_forceCreate, in_callback);
    }

    void BrainCloudAuthentication::authenticateFacebook(const char * in_fbUserId, const char * in_fbAuthToken, bool in_forceCreate, IServerCallback * in_callback)
    {
        authenticate(in_fbUserId, in_fbAuthToken, AuthenticationType::Facebook, NULL, in_forceCreate, in_callback);
    }

    void BrainCloudAuthentication::authenticateGameCenter(const char * in_gameCenterId, bool in_forceCreate, IServerCallback * in_callback)
    {
        authenticate(in_gameCenterId, "", AuthenticationType::GameCenter, NULL, in_forceCreate, in_callback);
    }

    void BrainCloudAuthentication::authenticateEmailPassword(const char * in_email, const char * in_password, bool in_forceCreate, IServerCallback * in_callback)
    {
        authenticate(in_email, in_password, AuthenticationType::Email, NULL, in_forceCreate, in_callback);
    }

    void BrainCloudAuthentication::authenticateUniversal(const char * in_userid, const char * in_password, bool in_forceCreate, IServerCallback * in_callback)
    {
        authenticate(in_userid, in_password, AuthenticationType::Universal, NULL, in_forceCreate, in_callback);
    }

    void BrainCloudAuthentication::authenticateSteam(const char * in_userid, const char * in_sessionticket, bool in_forceCreate, IServerCallback * in_callback)
    {
        authenticate(in_userid, in_sessionticket, AuthenticationType::Steam, NULL, in_forceCreate, in_callback);
    }

    void BrainCloudAuthentication::authenticateGoogle(const char * in_userid, const char * in_token, bool in_forceCreate, IServerCallback * in_callback)
    {
        authenticate(in_userid, in_token, AuthenticationType::Google, NULL, in_forceCreate, in_callback);
    }

    void BrainCloudAuthentication::authenticateTwitter(const char * in_userid, const char * in_token, const char * in_secret, bool in_forceCreate, IServerCallback * in_callback)
    {
        std::string buffer(in_token);
        buffer += ":";
        buffer += in_secret;
        authenticate(in_userid, buffer.c_str(), AuthenticationType::Twitter, NULL, in_forceCreate, in_callback);
    }

    void BrainCloudAuthentication::authenticateParse(const char * in_userid, const char * in_token, bool in_forceCreate, IServerCallback * in_callback)
    {
        authenticate(in_userid, in_token, AuthenticationType::Parse, NULL, in_forceCreate, in_callback);
    }

    void BrainCloudAuthentication::authenticateHandoff(const char * in_handoffId, const char * in_securityToken, IServerCallback * in_callback)
    {
        authenticate(in_handoffId, in_securityToken, AuthenticationType::Parse, NULL, false, in_callback);
    }

    void BrainCloudAuthentication::authenticateExternal(
        const char * in_userid,
        const char * in_token,
        const char * in_externalAuthName,
        bool in_forceCreate,
        IServerCallback * in_callback)
    {
        authenticate(in_userid, in_token, AuthenticationType::External, in_externalAuthName, in_forceCreate, in_callback);
    }

    void BrainCloudAuthentication::resetEmailPassword(const char * in_externalId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::AuthenticateServiceAuthenticateExternalId.getValue()] = in_externalId;
        message[OperationParam::AuthenticateServiceAuthenticateGameId.getValue()] = m_client->getAppId().c_str();

        ServerCall * sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetEmailPassword, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudAuthentication::authenticate(
        const char * in_externalId,
        const char * in_authenticationToken,
        AuthenticationType in_authenticationType,
        const char * in_externalAuthName,
        bool in_forceCreate,
        IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::AuthenticateServiceAuthenticateExternalId.getValue()] = in_externalId;
        message[OperationParam::AuthenticateServiceAuthenticateAuthenticationToken.getValue()] = in_authenticationToken;
        message[OperationParam::AuthenticateServiceAuthenticateAuthenticationType.getValue()] = in_authenticationType.toString();
        message[OperationParam::AuthenticateServiceAuthenticateForceCreate.getValue()] = in_forceCreate;

        message[OperationParam::AuthenticateServiceAuthenticateProfileId.getValue()] = _profileId;
        message[OperationParam::AuthenticateServiceAuthenticateAnonymousId.getValue()] = _anonymousId;
        message[OperationParam::AuthenticateServiceAuthenticateGameId.getValue()] = m_client->getAppId().c_str();
        message[OperationParam::AuthenticateServiceAuthenticateReleasePlatform.getValue()] = m_client->getReleasePlatform().c_str();
        message[OperationParam::AuthenticateServiceAuthenticateGameVersion.getValue()] = m_client->getAppVersion().c_str();
        message[OperationParam::AuthenticateServiceAuthenticateBrainCloudVersion.getValue()] = m_client->getBrainCloudClientVersion().c_str();
        if (StringUtil::IsOptionalParameterValid(in_externalAuthName))
        {
            message[OperationParam::AuthenticateServiceAuthenticateExternalAuthName.getValue()] = in_externalAuthName;
        }

        message[OperationParam::AuthenticateServiceAuthenticateCountryCode.getValue()] = m_client->getCountryCode().c_str();
        message[OperationParam::AuthenticateServiceAuthenticateLanguageCode.getValue()] = m_client->getLanguageCode().c_str();
        message[OperationParam::AuthenticateServiceAuthenticateTimeZoneOffset.getValue()] = m_client->getTimezoneOffset();
		message["clientLib"] = _clientLib;

        ServerCall * sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::Authenticate, message, in_callback);
        m_client->sendRequest(sc);
    }
}
