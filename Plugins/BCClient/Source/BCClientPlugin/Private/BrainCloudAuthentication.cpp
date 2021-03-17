// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudAuthentication.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudAuthentication::BrainCloudAuthentication(BrainCloudClient *client) : _client(client){};

const FString &BrainCloudAuthentication::getAnonymousId() const
{
	return _anonymousId;
}

const FString &BrainCloudAuthentication::getProfileId() const
{
	return _profileId;
}

void BrainCloudAuthentication::setAnonymousId(const FString &anonymousId)
{
	_anonymousId = anonymousId;
}

void BrainCloudAuthentication::setProfileId(const FString &profileId)
{
	_profileId = profileId;
}

void BrainCloudAuthentication::initialize(const FString &profileId, const FString &anonymousId)
{
	_profileId = profileId;
	_anonymousId = anonymousId;
}

FString BrainCloudAuthentication::generateAnonymousId()
{
	FGuid guid = FGuid::NewGuid();
	return guid.ToString(EGuidFormats::DigitsWithHyphens);
}

void BrainCloudAuthentication::clearSavedProfileId()
{
	_profileId = "";
}

void BrainCloudAuthentication::authenticateAnonymous(bool forceCreate, IServerCallback *callback)
{
	authenticate(*_anonymousId, TEXT(""), EBCAuthType::Anonymous, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateFacebook(const FString &externalId, const FString &authenticationToken, bool forceCreate, IServerCallback *callback)
{
	authenticate(*externalId, *authenticationToken, EBCAuthType::Facebook, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateFacebookLimited(const FString &externalId, const FString &authenticationToken, bool forceCreate, IServerCallback *callback)
{
	authenticate(*externalId, *authenticationToken, EBCAuthType::FacebookLimited, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateOculus(const FString &oculusId, const FString &oculusNonce, bool forceCreate, IServerCallback *callback)
{
	authenticate(*oculusId, *oculusNonce, EBCAuthType::Oculus, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticatePlaystationNetwork(const FString &accountId, const FString &authenticationToken, bool forceCreate, IServerCallback *callback)
{
	authenticate(*accountId, *authenticationToken, EBCAuthType::PlaystationNetwork, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateGameCenter(const FString &gameCenterId, bool forceCreate, IServerCallback *callback)
{
	authenticate(*gameCenterId, TEXT(""), EBCAuthType::GameCenter, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateEmailPassword(const FString &email, const FString &password, bool forceCreate, IServerCallback *callback)
{
	authenticate(*email, *password, EBCAuthType::Email, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateUniversal(const FString &userid, const FString &password, bool forceCreate, IServerCallback *callback)
{
	authenticate(*userid, *password, EBCAuthType::Universal, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateSteam(const FString &userid, const FString &sessionticket, bool forceCreate, IServerCallback *callback)
{
	authenticate(*userid, *sessionticket, EBCAuthType::Steam, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateGoogle(const FString &googleUserId, const FString &serverAuthCode, bool forceCreate, IServerCallback *callback)
{
	authenticate(googleUserId, serverAuthCode, EBCAuthType::Google, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateGoogleOpenId(const FString &googleUserAccountEmail, const FString &IdToken, bool forceCreate, IServerCallback *callback)
{
	authenticate(googleUserAccountEmail, IdToken, EBCAuthType::GoogleOpenId, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateApple(const FString &appleUserId, const FString &identityToken, bool forceCreate, IServerCallback *callback)
{
	authenticate(appleUserId, identityToken, EBCAuthType::Apple, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateTwitter(const FString &userid, const FString &token, const FString &secret, bool forceCreate, IServerCallback *callback)
{
	FString buffer(token);
	buffer += ":";
	buffer += secret;
	authenticate(userid, buffer, EBCAuthType::Twitter, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateParse(const FString &userid, const FString &token, bool forceCreate, IServerCallback *callback)
{
	authenticate(userid, token, EBCAuthType::Parse, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateHandoff(const FString &handoffId, const FString &securityToken, bool forceCreate, IServerCallback *callback)
{
	authenticate(handoffId, securityToken, EBCAuthType::Handoff, "", forceCreate, callback);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BrainCloudAuthentication::authenticateSettopHandoff(const FString &handoffCode, IServerCallback *callback)
{
	authenticate(handoffCode,"", EBCAuthType::SettopHandoff, "", false, callback);
}

void BrainCloudAuthentication::authenticateExternal(const FString &userid, const FString &token, const FString &externalAuthName, bool forceCreate, IServerCallback *callback)
{
	authenticate(userid, token, EBCAuthType::External, externalAuthName, forceCreate, callback);
}

void BrainCloudAuthentication::resetEmailPassword(const FString &in_email, IServerCallback *in_callback)
{
	BrainCloudClient *brainCloudClientRef = _client;

	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateExternalId.getValue(), in_email);
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), brainCloudClientRef->getAppId());

	ServerCall *sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetEmailPassword, message, in_callback);
	brainCloudClientRef->sendRequest(sc);
}

void BrainCloudAuthentication::resetEmailPasswordAdvanced(const FString &in_emailAddress, const FString &in_serviceParams, IServerCallback *in_callback)
{
	BrainCloudClient *brainCloudClientRef = _client;

	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), brainCloudClientRef->getAppId());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateEmailAddress.getValue(), in_emailAddress);
	message->SetObjectField(OperationParam::AuthenticateServiceAuthenticateServiceParams.getValue(), JsonUtil::jsonStringToValue(in_serviceParams));

	ServerCall *sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetEmailPasswordAdvanced, message, in_callback);
	brainCloudClientRef->sendRequest(sc);
}

void BrainCloudAuthentication::resetEmailPasswordWithExpiry(const FString &in_email, int32 in_tokenTtlInMinutes, IServerCallback *in_callback)
{
	BrainCloudClient *brainCloudClientRef = _client;

	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateExternalId.getValue(), in_email);
	message->SetNumberField(OperationParam::AuthenticateServiceAuthenticateTokenTtlInMinutes.getValue(), in_tokenTtlInMinutes);
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), brainCloudClientRef->getAppId());

	ServerCall *sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetEmailPasswordWithExpiry, message, in_callback);
	brainCloudClientRef->sendRequest(sc);
}


void BrainCloudAuthentication::resetEmailPasswordAdvancedWithExpiry(const FString &in_emailAddress, const FString &in_serviceParams, int32 in_tokenTtlInMinutes, IServerCallback *in_callback)
{
	BrainCloudClient *brainCloudClientRef = _client;

	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), brainCloudClientRef->getAppId());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateEmailAddress.getValue(), in_emailAddress);
	message->SetNumberField(OperationParam::AuthenticateServiceAuthenticateTokenTtlInMinutes.getValue(), in_tokenTtlInMinutes);
	message->SetObjectField(OperationParam::AuthenticateServiceAuthenticateServiceParams.getValue(), JsonUtil::jsonStringToValue(in_serviceParams));

	ServerCall *sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetEmailPasswordAdvancedWithExpiry, message, in_callback);
	brainCloudClientRef->sendRequest(sc);
}

void BrainCloudAuthentication::resetUniversalIdPassword(const FString &in_universalId, IServerCallback *in_callback)
{
	BrainCloudClient *brainCloudClientRef = _client;

	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), brainCloudClientRef->getAppId());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateUniversalId.getValue(), in_universalId);

	ServerCall *sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetUniversalIdPassword, message, in_callback);
	brainCloudClientRef->sendRequest(sc);
}

void BrainCloudAuthentication::resetUniversalIdPasswordAdvanced(const FString &in_universalId, const FString &in_serviceParams, IServerCallback *in_callback)
{
	BrainCloudClient *brainCloudClientRef = _client;

	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), brainCloudClientRef->getAppId());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateUniversalId.getValue(), in_universalId);
	message->SetObjectField(OperationParam::AuthenticateServiceAuthenticateServiceParams.getValue(), JsonUtil::jsonStringToValue(in_serviceParams));

	ServerCall *sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetUniversalIdPasswordAdvanced, message, in_callback);
	brainCloudClientRef->sendRequest(sc);
}

void BrainCloudAuthentication::resetUniversalIdPasswordWithExpiry(const FString &in_universalId, int32 in_tokenTtlInMinutes, IServerCallback *in_callback)
{
	BrainCloudClient *brainCloudClientRef = _client;

	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), brainCloudClientRef->getAppId());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateUniversalId.getValue(), in_universalId);
	message->SetNumberField(OperationParam::AuthenticateServiceAuthenticateTokenTtlInMinutes.getValue(), in_tokenTtlInMinutes);

	ServerCall *sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetUniversalIdPasswordWithExpiry, message, in_callback);
	brainCloudClientRef->sendRequest(sc);
}

void BrainCloudAuthentication::resetUniversalIdPasswordAdvancedWithExpiry(const FString &in_universalId, const FString &in_serviceParams, int32 in_tokenTtlInMinutes, IServerCallback *in_callback)
{
	BrainCloudClient *brainCloudClientRef = _client;

	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), brainCloudClientRef->getAppId());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateUniversalId.getValue(), in_universalId);
	message->SetNumberField(OperationParam::AuthenticateServiceAuthenticateTokenTtlInMinutes.getValue(), in_tokenTtlInMinutes);
	message->SetObjectField(OperationParam::AuthenticateServiceAuthenticateServiceParams.getValue(), JsonUtil::jsonStringToValue(in_serviceParams));


	ServerCall *sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetUniversalIdPasswordAdvancedWithExpiry, message, in_callback);
	brainCloudClientRef->sendRequest(sc);
}

void BrainCloudAuthentication::authenticate(
	const FString &externalId,
	const FString &authenticationToken,
	EBCAuthType authenticationType,
	const FString &externalAuthName,
	bool forceCreate,
	IServerCallback *callback)
{
	BrainCloudClient *brainCloudClientRef = _client;
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateExternalId.getValue(), externalId);
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateAuthenticationToken.getValue(), authenticationToken);
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateAuthenticationType.getValue(), BCAuthType::EnumToString(authenticationType));
	message->SetBoolField(OperationParam::AuthenticateServiceAuthenticateForceCreate.getValue(), forceCreate);

	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateProfileId.getValue(), _profileId);
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateAnonymousId.getValue(), _anonymousId);
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), brainCloudClientRef->getAppId());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateReleasePlatform.getValue(), brainCloudClientRef->getReleasePlatform());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameVersion.getValue(), brainCloudClientRef->getAppVersion());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateBrainCloudVersion.getValue(), brainCloudClientRef->getBrainCloudClientVersion());
	message->SetStringField(TEXT("clientLib"), TEXT("ue4"));

	if (OperationParam::isOptionalParamValid(externalAuthName))
	{
		message->SetStringField(OperationParam::AuthenticateServiceAuthenticateExternalAuthName.getValue(), externalAuthName);
	}

	ServerCall *sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::Authenticate, message, callback);
	brainCloudClientRef->sendRequest(sc);
}