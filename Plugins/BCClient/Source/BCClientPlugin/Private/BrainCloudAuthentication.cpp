// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudAuthentication.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudAuthentication::BrainCloudAuthentication(BrainCloudClient* client) : _client(client) {};

const FString & BrainCloudAuthentication::getAnonymousId() const
{
	return _anonymousId;
}

const FString & BrainCloudAuthentication::getProfileId() const
{
	return _profileId;
}

void BrainCloudAuthentication::setAnonymousId(const FString& anonymousId)
{
	_anonymousId = anonymousId;
}

void BrainCloudAuthentication::setProfileId(const FString& profileId)
{
	_profileId = profileId;
}

void BrainCloudAuthentication::initialize(const FString& profileId, const FString& anonymousId)
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

void BrainCloudAuthentication::authenticateAnonymous(bool forceCreate, IServerCallback * callback)
{
	authenticate(*_anonymousId, TEXT(""), EBCAuthType::Anonymous, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateFacebook(const FString& externalId, const FString& authenticationToken, bool forceCreate, IServerCallback * callback)
{
	authenticate(*externalId, *authenticationToken, EBCAuthType::Facebook, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateGameCenter(const FString& gameCenterId, bool forceCreate, IServerCallback * callback)
{
	authenticate(*gameCenterId, TEXT(""), EBCAuthType::GameCenter, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateEmailPassword(const FString& email, const FString& password, bool forceCreate, IServerCallback * callback)
{
	authenticate(*email, *password, EBCAuthType::Email, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateUniversal(const FString& userid, const FString& password, bool forceCreate, IServerCallback * callback)
{
	authenticate(*userid, *password, EBCAuthType::Universal, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateSteam(const FString& userid, const FString& sessionticket, bool forceCreate, IServerCallback * callback)
{
	authenticate(*userid, *sessionticket, EBCAuthType::Steam, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateGoogle(const FString& userid, const FString& token, bool forceCreate, IServerCallback * callback)
{
	authenticate(userid, token, EBCAuthType::Google, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateTwitter(const FString& userid, const FString& token, const FString& secret, bool forceCreate, IServerCallback * callback)
{
	FString buffer(token);
	buffer += ":";
	buffer += secret;
	authenticate(userid, buffer, EBCAuthType::Twitter, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateParse(const FString& userid, const FString& token, bool forceCreate, IServerCallback * callback)
{
	authenticate(userid, token, EBCAuthType::Parse, "", forceCreate, callback);
}

void BrainCloudAuthentication::authenticateExternal(const FString& userid, const FString& token, const FString& externalAuthName, bool forceCreate, IServerCallback * callback)
{
	authenticate(userid, token, EBCAuthType::External, externalAuthName, forceCreate, callback);
}

void BrainCloudAuthentication::resetEmailPassword(const FString& email, IServerCallback * callback)
{
	BrainCloudClient * brainCloudClientRef = _client;

	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateExternalId.getValue(), email);
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), brainCloudClientRef->getAppId());

	ServerCall * sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::ResetEmailPassword, message, callback);
	brainCloudClientRef->sendRequest(sc);
}

void BrainCloudAuthentication::authenticate(
	const FString& externalId,
	const FString& authenticationToken,
	EBCAuthType authenticationType,
	const FString& externalAuthName,
	bool forceCreate,
	IServerCallback * callback)
{
	BrainCloudClient * brainCloudClientRef = _client;
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

	ServerCall * sc = new ServerCall(ServiceName::AuthenticateV2, ServiceOperation::Authenticate, message, callback);
	brainCloudClientRef->sendRequest(sc);
}