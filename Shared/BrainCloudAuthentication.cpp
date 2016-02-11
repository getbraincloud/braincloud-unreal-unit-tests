#include "BrainCloudAuthentication.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "GUID.h"
#include "StringUtil.h"

namespace BrainCloud {
	const char * BrainCloudAuthentication::AUTH_FACEBOOK = "Facebook";
	
	BrainCloudAuthentication::BrainCloudAuthentication()
	: _anonymousId("")
	, _profileId("")
	{
		
	}
	
	void BrainCloudAuthentication::initialize(const char * in_profileId, const char * in_anonymousId)
	{
		_profileId = in_profileId;
		_anonymousId = in_anonymousId;
	}
	
	std::string BrainCloudAuthentication::generateGUID()
	{
		return BrainCloud::GUID::generateGUID();
	}
	
	void BrainCloudAuthentication::generateNewAnonymousId()
	{
		_anonymousId = generateGUID();
	}
	
	void BrainCloudAuthentication::clearSavedProfileId()
	{
		_profileId = "";
	}
	
	void BrainCloudAuthentication::authenticateAnonymous(bool in_forceCreate, IServerCallback * in_callback)
	{
		authenticate(_anonymousId.c_str(), "", OperationParam::AuthenticateServiceAuthenticateAuthAnonymous.getValue().c_str(), NULL, in_forceCreate, in_callback);
	}
	
	void BrainCloudAuthentication::authenticateFacebook(const char * in_externalId, const char * in_authenticationToken, bool in_forceCreate, IServerCallback * in_callback)
	{
		authenticate(in_externalId, in_authenticationToken, OperationParam::AuthenticateServiceAuthenticateAuthFacebook.getValue().c_str(), NULL, in_forceCreate, in_callback);
	}
	
	void BrainCloudAuthentication::authenticateGameCenter(const char * in_gameCenterId, bool in_forceCreate, IServerCallback * in_callback)
	{
		authenticate(in_gameCenterId, "", OperationParam::AuthenticateServiceAuthenticateAuthGameCenter.getValue().c_str(), NULL, in_forceCreate, in_callback);
	}
	
	void BrainCloudAuthentication::authenticateEmailPassword(const char * in_email, const char * in_password, bool in_forceCreate, IServerCallback * in_callback)
	{
		authenticate(in_email, in_password, OperationParam::AuthenticateServiceAuthenticateAuthEmail.getValue().c_str(), NULL, in_forceCreate, in_callback);
	}
	
	void BrainCloudAuthentication::authenticateUniversal(const char * in_userid, const char * in_password, bool in_forceCreate, IServerCallback * in_callback)
	{
		authenticate(in_userid, in_password, OperationParam::AuthenticateServiceAuthenticateAuthUniversal.getValue().c_str(), NULL, in_forceCreate, in_callback);
	}
	
	void BrainCloudAuthentication::authenticateSteam(const char * in_userid, const char * in_sessionticket, bool in_forceCreate, IServerCallback * in_callback)
	{
		authenticate(in_userid, in_sessionticket, OperationParam::AuthenticateServiceAuthenticateAuthSteam.getValue().c_str(), NULL, in_forceCreate, in_callback);
	}

	void BrainCloudAuthentication::authenticateGoogle(const char * in_userid, const char * in_token, bool in_forceCreate, IServerCallback * in_callback)
	{
		authenticate(in_userid, in_token, OperationParam::AuthenticateServiceAuthenticateAuthGoogle.getValue().c_str(), NULL, in_forceCreate, in_callback);
	}
    
    void BrainCloudAuthentication::authenticateTwitter(const char * in_userid, const char * in_token, const char * in_secret, bool in_forceCreate, IServerCallback * in_callback)
    {
        std::string buffer(in_token);
        buffer+=":";
        buffer+=in_secret;
        authenticate(in_userid, buffer.c_str(), OperationParam::AuthenticateServiceAuthenticateAuthTwitter.getValue().c_str(), NULL, in_forceCreate, in_callback);
    }
    
    void BrainCloudAuthentication::authenticateExternal(const char * in_userid,
                                                        const char * in_token,
                                                        const char * in_externalAuthName,
                                                        bool in_forceCreate,
                                                        IServerCallback * in_callback)
    {
        authenticate(in_userid, in_token, OperationParam::AuthenticateServiceAuthenticateAuthExternal.getValue().c_str(), in_externalAuthName, in_forceCreate, in_callback);
    }
    
	void BrainCloudAuthentication::resetEmailPassword(const char * in_externalId, IServerCallback * in_callback)
	{
		BrainCloudClient * brainCloudClientRef = BrainCloudClient::getInstance();

		Json::Value message;
		message[OperationParam::AuthenticateServiceAuthenticateExternalId.getValue()] = in_externalId;
		message[OperationParam::AuthenticateServiceAuthenticateGameId.getValue()] = brainCloudClientRef->getGameId().c_str();

		ServerCall * sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetEmailPassword, message, in_callback);
		brainCloudClientRef->sendRequest(sc);
	}

	
	void BrainCloudAuthentication::authenticate(const char * in_externalId, const char * in_authenticationToken, const char * in_authenticationType, const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback)
	{
		BrainCloudClient * brainCloudClientRef = BrainCloudClient::getInstance();

		std::string authType( AUTH_FACEBOOK );
		if( in_authenticationType != NULL ) {
			authType.clear();
			authType.append( in_authenticationType );
		}
		
		Json::Value message;
		message[OperationParam::AuthenticateServiceAuthenticateExternalId.getValue()] = in_externalId;
		message[OperationParam::AuthenticateServiceAuthenticateAuthenticationToken.getValue()] = in_authenticationToken;
		message[OperationParam::AuthenticateServiceAuthenticateAuthenticationType.getValue()] = authType;
		message[OperationParam::AuthenticateServiceAuthenticateForceCreate.getValue()] = in_forceCreate;
		
		message[OperationParam::AuthenticateServiceAuthenticateProfileId.getValue()] = _profileId;
		message[OperationParam::AuthenticateServiceAuthenticateAnonymousId.getValue()] = _anonymousId;
		message[OperationParam::AuthenticateServiceAuthenticateGameId.getValue()] = brainCloudClientRef->getGameId().c_str();
        message[OperationParam::AuthenticateServiceAuthenticateReleasePlatform.getValue()] = brainCloudClientRef->getReleasePlatform().c_str();
        message[OperationParam::AuthenticateServiceAuthenticateGameVersion.getValue()] = brainCloudClientRef->getGameVersion().c_str();
        message[OperationParam::AuthenticateServiceAuthenticateBrainCloudVersion.getValue()] = brainCloudClientRef->getBrainCloudClientVersion().c_str();
        if (StringUtil::IsOptionalParameterValid(in_externalAuthName))
        {
            message[OperationParam::AuthenticateServiceAuthenticateExternalAuthName.getValue()] = in_externalAuthName;
        }

		message[OperationParam::AuthenticateServiceAuthenticateCountryCode.getValue()] = brainCloudClientRef->getCountryCode().c_str();
		message[OperationParam::AuthenticateServiceAuthenticateLanguageCode.getValue()] = brainCloudClientRef->getLanguageCode().c_str();
		message[OperationParam::AuthenticateServiceAuthenticateTimeZoneOffset.getValue()] = brainCloudClientRef->getTimezoneOffset();

		//message[OperationParam::AuthenticateServiceAuthenticateAppId.getValue()] = brainCloudClientRef->getAppId().c_str();
        //message[OperationParam::AuthenticateServiceAuthenticateRegion.getValue()] = brainCloudClientRef->getRegion().c_str();
		
		/*
		 TODO: where to get deviceId?
		 if (deviceId != NULL)
		 message["deviceId"] = deviceId;
		 message["forceMergeFlag"] = forceMergeFlag;
		 */
		
		ServerCall * sc = new ServerCall( ServiceName::AuthenticateV2, ServiceOperation::Authenticate, message, in_callback );
		brainCloudClientRef->sendRequest(sc);
	}
}
