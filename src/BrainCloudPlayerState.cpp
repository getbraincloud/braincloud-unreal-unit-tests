// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudPlayerState.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud
{
    BrainCloudPlayerState::BrainCloudPlayerState(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudPlayerState::readPlayerState(IServerCallback *in_callback, const char *in_entityTypeFilter)
    {
        Json::Value data = Json::nullValue;
        if (in_entityTypeFilter != NULL)
        {
            data[OperationParam::PlayerStateServiceReadEntitySubtype.getValue()] = in_entityTypeFilter;
        }

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::Read, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::readUserState(IServerCallback *in_callback, const char *in_entityTypeFilter)
    {
        Json::Value data = Json::nullValue;
        if (in_entityTypeFilter != NULL)
        {
            data[OperationParam::PlayerStateServiceReadEntitySubtype.getValue()] = in_entityTypeFilter;
        }

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::Read, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::deletePlayer(IServerCallback *in_callback)
    {
        Json::Value data = Json::nullValue;

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::FullReset, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::deleteUser(IServerCallback *in_callback)
    {
        Json::Value data = Json::nullValue;

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::FullReset, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::resetPlayerState(IServerCallback *in_callback)
    {
        Json::Value data = Json::nullValue;

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::DataReset, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::resetUserState(IServerCallback *in_callback)
    {
        Json::Value data = Json::nullValue;

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::DataReset, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::logout(IServerCallback * in_callback)
    {
        Json::Value data = Json::nullValue;

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::Logout, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::updatePlayerName(const char *in_userName, IServerCallback *in_callback)
    {
        Json::Value data = Json::nullValue;
        if (in_userName != NULL)
        {
            data[OperationParam::PlayerStateServiceUpdateNameData.getValue()] = in_userName;
        }

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateName, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::updateUserName(const char *in_userName, IServerCallback *in_callback)
    {
        Json::Value data = Json::nullValue;
        if (in_userName != NULL)
        {
            data[OperationParam::PlayerStateServiceUpdateNameData.getValue()] = in_userName;
        }

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateName, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::updateSummaryFriendData(const char * in_jsonSummaryData, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlayerStateServiceUpdateSummaryFriendData.getValue()] = JsonUtil::jsonStringToValue(in_jsonSummaryData);

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateSummary, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::getAttributes(IServerCallback * in_callback)
    {
        Json::Value data = Json::nullValue;

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::GetAttributes, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::updateAttributes(const std::string& in_jsonAttributes, bool in_wipeExisting, IServerCallback * in_callback)
    {
        Json::Value data;
        data[OperationParam::PlayerStateServiceAttributes.getValue()] = JsonUtil::jsonStringToValue(in_jsonAttributes);
        data[OperationParam::PlayerStateServiceWipeExisting.getValue()] = in_wipeExisting;

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateAttributes, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::removeAttributes(const std::vector<std::string> & in_attributeNames, IServerCallback * in_callback)
    {
        Json::Value data;
        data[OperationParam::PlayerStateServiceAttributes.getValue()] = JsonUtil::stringVectorToJson(in_attributeNames);

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::RemoveAttributes, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::updatePlayerPictureUrl(const char *in_pictureUrl, IServerCallback *in_callback)
    {
        Json::Value data;
        data[OperationParam::PlayerStateServicePictureUrl.getValue()] = in_pictureUrl;

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdatePlayerPicture, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::updateUserPictureUrl(const char *in_pictureUrl, IServerCallback *in_callback)
    {
        Json::Value data;
        data[OperationParam::PlayerStateServicePictureUrl.getValue()] = in_pictureUrl;

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdatePlayerPicture, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerState::updateContactEmail(const char * in_contactEmail, IServerCallback * in_callback)
    {
        Json::Value data;
        data[OperationParam::PlayerStateServiceContactEmail.getValue()] = in_contactEmail;

        ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateContactEmail, data, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }
}