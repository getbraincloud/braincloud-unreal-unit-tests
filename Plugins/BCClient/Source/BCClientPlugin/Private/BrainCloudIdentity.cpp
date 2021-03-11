// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudIdentity.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudIdentity::BrainCloudIdentity(BrainCloudClient *client) : _client(client){};

void BrainCloudIdentity::attachBlockchainIdentity(const FString &blockchainConfig, const FString &publicKey, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::IdentityServiceBlockchainConfig.getValue(), blockchainConfig);
	message->SetStringField(OperationParam::IdentityServicePublicKey.getValue(), publicKey);

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::AttachBlockchainIdentity, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::detachBlockchainIdentity(const FString &blockchainConfig, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::IdentityServiceBlockchainConfig.getValue(), blockchainConfig);

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::DetachBlockchainIdentity, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::attachFacebookIdentity(const FString &facebookId, const FString &authenticationToken, IServerCallback *callback)
{
	attachIdentity(facebookId, authenticationToken, EBCAuthType::Facebook, callback);
}

void BrainCloudIdentity::mergeFacebookIdentity(const FString &facebookId, const FString &authenticationToken, IServerCallback *callback)
{
	mergeIdentity(facebookId, authenticationToken, EBCAuthType::Facebook, callback);
}

void BrainCloudIdentity::detachFacebookIdentity(const FString &facebookId, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(facebookId, EBCAuthType::Facebook, continueAnon, callback);
}

void BrainCloudIdentity::attachOculusIdentity(const FString &oculusId, const FString &oculusNonce, IServerCallback *callback)
{
	attachIdentity(oculusId, oculusNonce, EBCAuthType::Oculus, callback);
}

void BrainCloudIdentity::mergeOculusIdentity(const FString &oculusId, const FString &oculusNonce, IServerCallback *callback)
{
	mergeIdentity(oculusId, oculusNonce, EBCAuthType::Oculus, callback);
}

void BrainCloudIdentity::detachOculusIdentity(const FString &oculusId, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(oculusId, EBCAuthType::Oculus, continueAnon, callback);
}

void BrainCloudIdentity::attachPlaystationNetworkIdentity(const FString &accountId, const FString &authenticationToken, IServerCallback *callback)
{
	attachIdentity(accountId, authenticationToken, EBCAuthType::Facebook, callback);
}

void BrainCloudIdentity::mergePlaystationNetworkIdentity(const FString &accountId, const FString &authenticationToken, IServerCallback *callback)
{
	mergeIdentity(accountId, authenticationToken, EBCAuthType::Facebook, callback);
}

void BrainCloudIdentity::detachPlaystationNetworkIdentity(const FString &accountId, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(accountId, EBCAuthType::PlaystationNetwork, continueAnon, callback);
}

void BrainCloudIdentity::attachEmailIdentity(const FString &email, const FString &password, IServerCallback *callback)
{
	attachIdentity(email, password, EBCAuthType::Email, callback);
}

void BrainCloudIdentity::mergeEmailIdentity(const FString &email, const FString &password, IServerCallback *callback)
{
	mergeIdentity(email, password, EBCAuthType::Email, callback);
}

void BrainCloudIdentity::detachEmailIdentity(const FString &email, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(email, EBCAuthType::Email, continueAnon, callback);
}

void BrainCloudIdentity::attachUniversalIdentity(const FString &userId, const FString &password, IServerCallback *callback)
{
	attachIdentity(userId, password, EBCAuthType::Universal, callback);
}

void BrainCloudIdentity::mergeUniversalIdentity(const FString &userId, const FString &password, IServerCallback *callback)
{
	mergeIdentity(userId, password, EBCAuthType::Universal, callback);
}

void BrainCloudIdentity::detachUniversalIdentity(const FString &userId, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(userId, EBCAuthType::Universal, continueAnon, callback);
}

void BrainCloudIdentity::attachGameCenterIdentity(const FString &gameCenterId, IServerCallback *callback)
{
	attachIdentity(gameCenterId, TEXT(""), EBCAuthType::GameCenter, callback);
}

void BrainCloudIdentity::mergeGameCenterIdentity(const FString &gameCenterId, IServerCallback *callback)
{
	mergeIdentity(gameCenterId, TEXT(""), EBCAuthType::GameCenter, callback);
}

void BrainCloudIdentity::detachGameCenterIdentity(const FString &gameCenterId, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(gameCenterId, EBCAuthType::GameCenter, continueAnon, callback);
}

void BrainCloudIdentity::attachSteamIdentity(const FString &steamId, const FString &sessionTicket, IServerCallback *callback)
{
	attachIdentity(steamId, sessionTicket, EBCAuthType::Steam, callback);
}

void BrainCloudIdentity::mergeSteamIdentity(const FString &steamId, const FString &sessionTicket, IServerCallback *callback)
{
	mergeIdentity(steamId, sessionTicket, EBCAuthType::Steam, callback);
}

void BrainCloudIdentity::detachSteamIdentity(const FString &steamId, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(steamId, EBCAuthType::Steam, continueAnon, callback);
}

void BrainCloudIdentity::attachGoogleIdentity(const FString &googleUserId, const FString &serverAuthCode, IServerCallback *callback)
{
	attachIdentity(googleUserId, serverAuthCode, EBCAuthType::Google, callback);
}

void BrainCloudIdentity::mergeGoogleIdentity(const FString &googleUserId, const FString &serverAuthCode, IServerCallback *callback)
{
	mergeIdentity(googleUserId, serverAuthCode, EBCAuthType::Google, callback);
}

void BrainCloudIdentity::detachGoogleIdentity(const FString &googleUserId, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(googleUserId, EBCAuthType::Google, continueAnon, callback);
}

void BrainCloudIdentity::attachGoogleOpenIdIdentity(const FString &googleUserAccountEmail, const FString &IdToken, IServerCallback *callback)
{
	attachIdentity(googleUserAccountEmail, IdToken, EBCAuthType::GoogleOpenId, callback);
}

void BrainCloudIdentity::mergeGoogleOpenIdIdentity(const FString &googleUserAccountEmail, const FString &IdToken, IServerCallback *callback)
{
	mergeIdentity(googleUserAccountEmail, IdToken, EBCAuthType::GoogleOpenId, callback);
}

void BrainCloudIdentity::detachGoogleOpenIdIdentity(const FString &googleUserAccountEmail, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(googleUserAccountEmail, EBCAuthType::GoogleOpenId, continueAnon, callback);
}

void BrainCloudIdentity::attachAppleIdentity(const FString &appleUserId, const FString &identityToken, IServerCallback *callback)
{
	attachIdentity(appleUserId, identityToken, EBCAuthType::Apple, callback);
}

void BrainCloudIdentity::mergeAppleIdentity(const FString &appleUserId, const FString &identityToken, IServerCallback *callback)
{
	mergeIdentity(appleUserId, identityToken, EBCAuthType::Apple, callback);
}

void BrainCloudIdentity::detachAppleIdentity(const FString &appleUserId, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(appleUserId, EBCAuthType::Apple, continueAnon, callback);
}

void BrainCloudIdentity::attachTwitterIdentity(const FString &twitterId, const FString &authenticationToken, const FString &secret, IServerCallback *callback)
{
	FString buffer = authenticationToken;
	buffer += ":" + secret;
	attachIdentity(twitterId, buffer, EBCAuthType::Twitter, callback);
}

void BrainCloudIdentity::mergeTwitterIdentity(const FString &twitterId, const FString &authenticationToken, const FString &secret, IServerCallback *callback)
{
	FString buffer = authenticationToken;
	buffer += ":" + secret;
	mergeIdentity(twitterId, buffer, EBCAuthType::Twitter, callback);
}

void BrainCloudIdentity::detachTwitterIdentity(const FString &twitterId, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(twitterId, EBCAuthType::Twitter, continueAnon, callback);
}

void BrainCloudIdentity::attachParseIdentity(const FString &parseId, const FString &authenticationToken, IServerCallback *callback)
{
	attachIdentity(parseId, authenticationToken, EBCAuthType::Parse, callback);
}

void BrainCloudIdentity::mergeParseIdentity(const FString &parseId, const FString &authenticationToken, IServerCallback *callback)
{
	mergeIdentity(parseId, authenticationToken, EBCAuthType::Parse, callback);
}

void BrainCloudIdentity::detachParseIdentity(const FString &parseId, bool continueAnon, IServerCallback *callback)
{
	detachIdentity(parseId, EBCAuthType::Parse, continueAnon, callback);
}

void BrainCloudIdentity::switchToChildProfile(const FString &childProfileId, const FString &childGameId, bool forceCreate, IServerCallback *callback)
{
	switchToChildProfile(childProfileId, childGameId, forceCreate, false, callback);
}

void BrainCloudIdentity::switchToSingletonChildProfile(const FString &childGameId, bool forceCreate, IServerCallback *callback)
{
	switchToChildProfile("", childGameId, forceCreate, true, callback);
}

void BrainCloudIdentity::switchToParentProfile(const FString &parentLevelName, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::AuthenticationServiceAuthenticationLevelName.getValue(), parentLevelName);

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::SwitchToParentProfile, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::getChildProfiles(bool includeSummaryData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetBoolField(OperationParam::PlayerStateServiceIncludeSummaryData.getValue(), includeSummaryData);

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::GetChildProfiles, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::getIdentities(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::GetIdentities, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::getExpiredIdentities(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::GetExpiredIdentities, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::refreshIdentity(const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::IdentityServiceExternalId.getValue(), externalId);
	message->SetStringField(OperationParam::IdentityServiceAuthenticationType.getValue(), BCAuthType::EnumToString(authenticationType));
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateAuthenticationToken.getValue(), authenticationToken);

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::RefreshIdentity, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::changeEmailIdentity(const FString &oldEmailAddress, const FString &password, const FString &newEmailAddress,
											 bool updateContactEmail, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::IdentityServiceOldEmailAddress.getValue(), oldEmailAddress);
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateAuthenticationToken.getValue(), password);
	message->SetStringField(OperationParam::IdentityServiceNewEmailAddress.getValue(), newEmailAddress);
	message->SetBoolField(OperationParam::IdentityServiceUpdateContactEmail.getValue(), updateContactEmail);

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::ChangeEmailIdentity, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::attachParentWithIdentity(const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType,
												  const FString &externalAuthName, bool forceCreate, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::IdentityServiceExternalId.getValue(), externalId);
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateAuthenticationToken.getValue(), authenticationToken);
	message->SetStringField(OperationParam::IdentityServiceAuthenticationType.getValue(), BCAuthType::EnumToString(authenticationType));
	message->SetBoolField(OperationParam::AuthenticateServiceAuthenticateForceCreate.getValue(), forceCreate);

	if (OperationParam::isOptionalParamValid(externalAuthName))
	{
		message->SetStringField(OperationParam::AuthenticateServiceAuthenticateExternalAuthName.getValue(), externalAuthName);
	}

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::AttachParentWithIdentity, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::detachParent(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::DetachParent, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::attachPeerProfile(const FString &peer, const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType,
										   const FString &externalAuthName, bool forceCreate, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::Peer.getValue(), peer);
	message->SetStringField(OperationParam::IdentityServiceExternalId.getValue(), externalId);
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateAuthenticationToken.getValue(), authenticationToken);
	message->SetStringField(OperationParam::IdentityServiceAuthenticationType.getValue(), BCAuthType::EnumToString(authenticationType));
	message->SetBoolField(OperationParam::AuthenticateServiceAuthenticateForceCreate.getValue(), forceCreate);

	if (OperationParam::isOptionalParamValid(externalAuthName))
	{
		message->SetStringField(OperationParam::AuthenticateServiceAuthenticateExternalAuthName.getValue(), externalAuthName);
	}

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::AttachPeerProfile, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::detachPeer(const FString &peer, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::Peer.getValue(), peer);

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::DetachPeer, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::getPeerProfiles(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::GetPeerProfiles, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::attachNonLoginUniversalId(const FString &externalId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::IdentityServiceExternalId.getValue(), externalId);
	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::AttachNonLoginUniversalId, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::updateUniversalIDLogin(const FString &externalId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::IdentityServiceExternalId.getValue(), externalId);
	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::UpdateUniversalIdLogin, message, callback);
	_client->sendRequest(sc);
}

//Private
void BrainCloudIdentity::attachIdentity(const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::IdentityServiceExternalId.getValue(), externalId);
	message->SetStringField(OperationParam::IdentityServiceAuthenticationType.getValue(), BCAuthType::EnumToString(authenticationType));
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateAuthenticationToken.getValue(), authenticationToken);

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::Attach, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::mergeIdentity(const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::IdentityServiceExternalId.getValue(), externalId);
	message->SetStringField(OperationParam::IdentityServiceAuthenticationType.getValue(), BCAuthType::EnumToString(authenticationType));
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateAuthenticationToken.getValue(), authenticationToken);

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::Merge, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::detachIdentity(const FString &externalId, EBCAuthType authenticationType, bool continueAnon, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::IdentityServiceExternalId.getValue(), externalId);
	message->SetStringField(OperationParam::IdentityServiceAuthenticationType.getValue(), BCAuthType::EnumToString(authenticationType));
	message->SetBoolField(OperationParam::IdentityServiceConfirmAnonymous.getValue(), continueAnon);

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::Detach, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudIdentity::switchToChildProfile(const FString &childProfileId, const FString &childGameId, bool forceCreate, bool forceSingleton, IServerCallback *callback)
{
	BrainCloudClient *brainCloudClientRef = _client;
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	if (OperationParam::isOptionalParamValid(childProfileId))
	{
		message->SetStringField(OperationParam::AuthenticateServiceAuthenticateProfileId.getValue(), childProfileId);
	}

	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateGameId.getValue(), childGameId);
	message->SetBoolField(OperationParam::AuthenticateServiceAuthenticateForceCreate.getValue(), forceCreate);
	message->SetBoolField(OperationParam::IdentityServiceForceSingleton.getValue(), forceSingleton);

	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateReleasePlatform.getValue(), brainCloudClientRef->getReleasePlatform());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateCountryCode.getValue(), "");		//brainCloudClientRef->getCountryCode());
	message->SetStringField(OperationParam::AuthenticateServiceAuthenticateLanguageCode.getValue(), "");	//brainCloudClientRef->getLanguageCode());
	message->SetNumberField(OperationParam::AuthenticateServiceAuthenticateTimeZoneOffset.getValue(), 0.0); // brainCloudClientRef->getTimezoneOffset());

	ServerCall *sc = new ServerCall(ServiceName::Identity, ServiceOperation::SwitchToChildProfile, message, callback);
	_client->sendRequest(sc);
}
