// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudMail.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudMail::BrainCloudMail(BrainCloudClient *client) : _client(client){};

void BrainCloudMail::sendBasicEmail(const FString &profileId, const FString &subject, const FString &body, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::ProfileId.getValue(), profileId);
	message->SetStringField(OperationParam::Subject.getValue(), subject);
	message->SetStringField(OperationParam::Body.getValue(), body);

	ServerCall *sc = new ServerCall(ServiceName::Mail, ServiceOperation::SendBasicEmail, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudMail::sendAdvancedEmail(const FString &profileId, const FString &jsonServiceParams, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::ProfileId.getValue(), profileId);
	message->SetObjectField(OperationParam::ServiceParams.getValue(), JsonUtil::jsonStringToValue(jsonServiceParams));

	ServerCall *sc = new ServerCall(ServiceName::Mail, ServiceOperation::SendAdvancedEmail, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudMail::sendAdvancedEmailByAddress(const FString &emailAddress, const FString &jsonServiceParams, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::EmailAddress.getValue(), emailAddress);
	message->SetObjectField(OperationParam::ServiceParams.getValue(), JsonUtil::jsonStringToValue(jsonServiceParams));

	ServerCall *sc = new ServerCall(ServiceName::Mail, ServiceOperation::SendAdvancedEmailByAddress, message, callback);
	_client->sendRequest(sc);
}