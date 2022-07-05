// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudProfanity.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudProfanity::BrainCloudProfanity(BrainCloudClient *client) : _client(client){};

void BrainCloudProfanity::profanityCheck(const FString &text, const FString &languages, bool flagEmail,
                                         bool flagPhone, bool flagUrls, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    message->SetStringField(OperationParam::ProfanityText.getValue(), text);

    if (OperationParam::isOptionalParamValid(languages))
        message->SetStringField(OperationParam::ProfanityFlagEmail.getValue(), languages);

    message->SetBoolField(OperationParam::ProfanityFlagEmail.getValue(), flagEmail);
    message->SetBoolField(OperationParam::ProfanityFlagPhone.getValue(), flagPhone);
    message->SetBoolField(OperationParam::ProfanityFlagUrls.getValue(), flagUrls);

    ServerCall *sc = new ServerCall(ServiceName::Profanity, ServiceOperation::ProfanityCheck, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudProfanity::profanityReplaceText(const FString &text, const FString &replaceSymbol, const FString &languages,
                                               bool flagEmail, bool flagPhone, bool flagUrls, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    message->SetStringField(OperationParam::ProfanityText.getValue(), text);
    message->SetStringField(OperationParam::ProfanityReplaceSymbol.getValue(), replaceSymbol);

    if (OperationParam::isOptionalParamValid(languages))
        message->SetStringField(OperationParam::ProfanityFlagEmail.getValue(), languages);

    message->SetBoolField(OperationParam::ProfanityFlagEmail.getValue(), flagEmail);
    message->SetBoolField(OperationParam::ProfanityFlagPhone.getValue(), flagPhone);
    message->SetBoolField(OperationParam::ProfanityFlagUrls.getValue(), flagUrls);

    ServerCall *sc = new ServerCall(ServiceName::Profanity, ServiceOperation::ProfanityReplaceText, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudProfanity::profanityIdentifyBadWords(const FString &text, const FString &languages, bool flagEmail,
                                                    bool flagPhone, bool flagUrls, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    message->SetStringField(OperationParam::ProfanityText.getValue(), text);

    if (OperationParam::isOptionalParamValid(languages))
        message->SetStringField(OperationParam::ProfanityFlagEmail.getValue(), languages);

    message->SetBoolField(OperationParam::ProfanityFlagEmail.getValue(), flagEmail);
    message->SetBoolField(OperationParam::ProfanityFlagPhone.getValue(), flagPhone);
    message->SetBoolField(OperationParam::ProfanityFlagUrls.getValue(), flagUrls);

    ServerCall *sc = new ServerCall(ServiceName::Profanity, ServiceOperation::ProfanityIdenitfyBadWords, message, callback);
    _client->sendRequest(sc);
}