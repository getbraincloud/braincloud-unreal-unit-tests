// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudProfanity.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"

namespace BrainCloud
{
    BrainCloudProfanity::BrainCloudProfanity(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudProfanity::profanityCheck(const char * in_text,
        const char * in_languages,
        bool in_flagEmail,
        bool in_flagPhone,
        bool in_flagUrls,
        IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProfanityText.getValue()] = in_text;
        if (in_languages != NULL)
        {
            message[OperationParam::ProfanityLanguages.getValue()] = in_languages;
        }
        message[OperationParam::ProfanityFlagEmail.getValue()] = in_flagEmail;
        message[OperationParam::ProfanityFlagPhone.getValue()] = in_flagPhone;
        message[OperationParam::ProfanityFlagUrls.getValue()] = in_flagUrls;

        ServerCall * sc = new ServerCall(ServiceName::Profanity, ServiceOperation::ProfanityCheck, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudProfanity::profanityReplaceText(const char * in_text,
        const char * in_replaceSymbol,
        const char * in_languages,
        bool in_flagEmail,
        bool in_flagPhone,
        bool in_flagUrls,
        IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProfanityText.getValue()] = in_text;
        message[OperationParam::ProfanityReplaceSymbol.getValue()] = in_replaceSymbol;
        if (in_languages != NULL)
        {
            message[OperationParam::ProfanityLanguages.getValue()] = in_languages;
        }
        message[OperationParam::ProfanityFlagEmail.getValue()] = in_flagEmail;
        message[OperationParam::ProfanityFlagPhone.getValue()] = in_flagPhone;
        message[OperationParam::ProfanityFlagUrls.getValue()] = in_flagUrls;

        ServerCall * sc = new ServerCall(ServiceName::Profanity, ServiceOperation::ProfanityReplaceText, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudProfanity::profanityIdentifyBadWords(const char * in_text,
        const char * in_languages,
        bool in_flagEmail,
        bool in_flagPhone,
        bool in_flagUrls,
        IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProfanityText.getValue()] = in_text;
        if (in_languages != NULL)
        {
            message[OperationParam::ProfanityLanguages.getValue()] = in_languages;
        }
        message[OperationParam::ProfanityFlagEmail.getValue()] = in_flagEmail;
        message[OperationParam::ProfanityFlagPhone.getValue()] = in_flagPhone;
        message[OperationParam::ProfanityFlagUrls.getValue()] = in_flagUrls;

        ServerCall * sc = new ServerCall(ServiceName::Profanity, ServiceOperation::ProfanityIdenitfyBadWords, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }
};