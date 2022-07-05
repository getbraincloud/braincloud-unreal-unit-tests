// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudGamification.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudGamification::BrainCloudGamification(BrainCloudClient *client) : _client(client){};

void BrainCloudGamification::setAchievementAwardedDelegate(IServerCallback *callback)
{
    m_achievementsDelegate = callback;
}

void BrainCloudGamification::readAllGamification(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::Read, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readQuests(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadQuests, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readMilestones(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadMilestones, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readAchievements(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadAchievements, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readXpLevelsMetaData(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadXpLevels, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readAchievedAchievements(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadAchievedAchievements, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readCompletedQuests(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadCompletedQuests, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readInProgressQuests(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadInProgressQuests, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readNotStartedQuests(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadNotStartedQuests, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readQuestsWithStatus(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadQuestsWithStatus, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readQuestsWithBasicPercentage(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadQuestsWithBasicPercentage, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readQuestsWithComplexPercentage(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadQuestsWithComplexPercentage, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readCompletedMilestones(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadCompletedMilestones, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readInProgressMilestones(IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadInProgressMilestones, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readQuestsByCategory(const FString &category, IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GamificationServiceCategory.getValue(), category);
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadQuestsByCategory, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::readMilestonesByCategory(const FString &category, IServerCallback *callback, bool includeMetaData)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GamificationServiceCategory.getValue(), category);
    message->SetBoolField(OperationParam::GamificationServiceIncludeMetaData.getValue(), includeMetaData);

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadMilestonesByCategory, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::awardAchievements(const TArray<FString> &achievements, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::GamificationServiceAchievementsName.getValue(), JsonUtil::arrayToJsonArray(achievements));

    ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::AwardAchievements, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGamification::achievementAwardedCallback(ServiceName serviceName, ServiceOperation serviceOperation, const TCHAR *jsonData)
{
    TSharedPtr<FJsonObject> data = JsonUtil::jsonStringToValue(jsonData);

    TSharedPtr<FJsonObject> _jsonObj1;
    if (data->TryGetObjectField(OperationParam::GamificationServiceAchievementsData.getValue(), (const TSharedPtr<FJsonObject> *&)_jsonObj1))
    {
        TArray<TSharedPtr<FJsonValue>> jsonArray;
        if (_jsonObj1->TryGetArrayField(OperationParam::GamificationServiceAchievementsName.getValue(),
                                        (const TArray<TSharedPtr<FJsonValue>> *&)jsonArray))
        {
            if (m_achievementsDelegate != nullptr)
            {
                m_achievementsDelegate->serverCallback(serviceName, serviceOperation, jsonData);
            }
        }
    }
}

void BrainCloudGamification::checkForAchievementsToAward(ServiceName serviceName, ServiceOperation serviceOperation, const TCHAR *jsonData)
{
    TSharedPtr<FJsonObject> data = JsonUtil::jsonStringToValue(jsonData);

    TArray<TSharedPtr<FJsonValue>> jsonArray;
    if (data->TryGetArrayField(OperationParam::GamificationServiceAchievementsData.getValue(), (const TArray<TSharedPtr<FJsonValue>> *&)jsonArray))
    {
        if (m_achievementsDelegate != nullptr)
        {
            m_achievementsDelegate->serverCallback(serviceName, serviceOperation, *JsonUtil::jsonValueToString(data.ToSharedRef()));
        }
    }
}
