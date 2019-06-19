// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudLobby.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudLobby::BrainCloudLobby(BrainCloudClient *client) : _client(client){};

void BrainCloudLobby::findLobby(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                                const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
                                bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds,
                                IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyRoomType.getValue(), in_roomType);
    message->SetNumberField(OperationParam::LobbyRating.getValue(), in_rating);
    message->SetNumberField(OperationParam::LobbyMaxSteps.getValue(), in_maxSteps);
    message->SetObjectField(OperationParam::LobbyAlgorithm.getValue(), JsonUtil::jsonStringToValue(in_algoJson));
    message->SetObjectField(OperationParam::LobbyFilterJson.getValue(), JsonUtil::jsonStringToValue(in_filterJson));
    message->SetNumberField(OperationParam::LobbyTimeoutSeconds.getValue(), in_timeoutSecs);
    message->SetBoolField(OperationParam::LobbyIsReady.getValue(), in_isReady);
    message->SetObjectField(OperationParam::LobbyExtraJson.getValue(), JsonUtil::jsonStringToValue(in_extraJson));
    message->SetStringField(OperationParam::LobbyTeamCode.getValue(), in_teamCode);
    message->SetArrayField(OperationParam::LobbyOtherUserCxIds.getValue(), JsonUtil::arrayToJsonArray(in_otherUserCxIds));

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::FindLobby, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::findLobbyWithPingData(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                                const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
                                bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds,
                                IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyRoomType.getValue(), in_roomType);
    message->SetNumberField(OperationParam::LobbyRating.getValue(), in_rating);
    message->SetNumberField(OperationParam::LobbyMaxSteps.getValue(), in_maxSteps);
    message->SetObjectField(OperationParam::LobbyAlgorithm.getValue(), JsonUtil::jsonStringToValue(in_algoJson));
    message->SetObjectField(OperationParam::LobbyFilterJson.getValue(), JsonUtil::jsonStringToValue(in_filterJson));
    message->SetNumberField(OperationParam::LobbyTimeoutSeconds.getValue(), in_timeoutSecs);
    message->SetBoolField(OperationParam::LobbyIsReady.getValue(), in_isReady);
    message->SetObjectField(OperationParam::LobbyExtraJson.getValue(), JsonUtil::jsonStringToValue(in_extraJson));
    message->SetStringField(OperationParam::LobbyTeamCode.getValue(), in_teamCode);
    message->SetArrayField(OperationParam::LobbyOtherUserCxIds.getValue(), JsonUtil::arrayToJsonArray(in_otherUserCxIds));

    // TODO : append ping data and send, or return right away the failure!
    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::FindLobby, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::createLobby(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                                  bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
                                  const FString &in_configJson, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyRoomType.getValue(), in_roomType);
    message->SetNumberField(OperationParam::LobbyRating.getValue(), in_rating);
    message->SetNumberField(OperationParam::LobbyMaxSteps.getValue(), in_maxSteps);
    message->SetBoolField(OperationParam::LobbyIsReady.getValue(), in_isReady);
    message->SetObjectField(OperationParam::LobbyExtraJson.getValue(), JsonUtil::jsonStringToValue(in_extraJson));
    message->SetStringField(OperationParam::LobbyTeamCode.getValue(), in_teamCode);

    message->SetObjectField(OperationParam::LobbySettings.getValue(), JsonUtil::jsonStringToValue(in_configJson));
    message->SetArrayField(OperationParam::LobbyOtherUserCxIds.getValue(), JsonUtil::arrayToJsonArray(in_otherUserCxIds));

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::CreateLobby, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::createLobbyWithPingData(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                                  bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
                                  const FString &in_configJson, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyRoomType.getValue(), in_roomType);
    message->SetNumberField(OperationParam::LobbyRating.getValue(), in_rating);
    message->SetNumberField(OperationParam::LobbyMaxSteps.getValue(), in_maxSteps);
    message->SetBoolField(OperationParam::LobbyIsReady.getValue(), in_isReady);
    message->SetObjectField(OperationParam::LobbyExtraJson.getValue(), JsonUtil::jsonStringToValue(in_extraJson));
    message->SetStringField(OperationParam::LobbyTeamCode.getValue(), in_teamCode);

    message->SetObjectField(OperationParam::LobbySettings.getValue(), JsonUtil::jsonStringToValue(in_configJson));
    message->SetArrayField(OperationParam::LobbyOtherUserCxIds.getValue(), JsonUtil::arrayToJsonArray(in_otherUserCxIds));

    // TODO : append ping data and send, or return right away the failure!
    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::CreateLobby, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::findOrCreateLobby(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                                        const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
                                        bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
                                        const FString &in_configJson, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyRoomType.getValue(), in_roomType);
    message->SetNumberField(OperationParam::LobbyRating.getValue(), in_rating);
    message->SetNumberField(OperationParam::LobbyMaxSteps.getValue(), in_maxSteps);
    message->SetObjectField(OperationParam::LobbyAlgorithm.getValue(), JsonUtil::jsonStringToValue(in_algoJson));
    message->SetObjectField(OperationParam::LobbyFilterJson.getValue(), JsonUtil::jsonStringToValue(in_filterJson));
    message->SetNumberField(OperationParam::LobbyTimeoutSeconds.getValue(), in_timeoutSecs);
    message->SetBoolField(OperationParam::LobbyIsReady.getValue(), in_isReady);
    message->SetObjectField(OperationParam::LobbyExtraJson.getValue(), JsonUtil::jsonStringToValue(in_extraJson));
    message->SetStringField(OperationParam::LobbyTeamCode.getValue(), in_teamCode);
    message->SetObjectField(OperationParam::LobbySettings.getValue(), JsonUtil::jsonStringToValue(in_configJson));
    message->SetArrayField(OperationParam::LobbyOtherUserCxIds.getValue(), JsonUtil::arrayToJsonArray(in_otherUserCxIds));

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::FindOrCreateLobby, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::findOrCreateLobbyWithPingData(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                                        const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
                                        bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
                                        const FString &in_configJson, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyRoomType.getValue(), in_roomType);
    message->SetNumberField(OperationParam::LobbyRating.getValue(), in_rating);
    message->SetNumberField(OperationParam::LobbyMaxSteps.getValue(), in_maxSteps);
    message->SetObjectField(OperationParam::LobbyAlgorithm.getValue(), JsonUtil::jsonStringToValue(in_algoJson));
    message->SetObjectField(OperationParam::LobbyFilterJson.getValue(), JsonUtil::jsonStringToValue(in_filterJson));
    message->SetNumberField(OperationParam::LobbyTimeoutSeconds.getValue(), in_timeoutSecs);
    message->SetBoolField(OperationParam::LobbyIsReady.getValue(), in_isReady);
    message->SetObjectField(OperationParam::LobbyExtraJson.getValue(), JsonUtil::jsonStringToValue(in_extraJson));
    message->SetStringField(OperationParam::LobbyTeamCode.getValue(), in_teamCode);
    message->SetObjectField(OperationParam::LobbySettings.getValue(), JsonUtil::jsonStringToValue(in_configJson));
    message->SetArrayField(OperationParam::LobbyOtherUserCxIds.getValue(), JsonUtil::arrayToJsonArray(in_otherUserCxIds));

// TODO : append ping data and send, or return right away the failure!
    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::FindOrCreateLobby, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::getLobbyData(const FString &in_lobbyID, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyIdentifier.getValue(), in_lobbyID);

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::GetLobbyData, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::updateReady(const FString &in_lobbyID, bool in_isReady, const FString &in_extraJson, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyIdentifier.getValue(), in_lobbyID);
    message->SetBoolField(OperationParam::LobbyIsReady.getValue(), in_isReady);
    message->SetObjectField(OperationParam::LobbyExtraJson.getValue(), JsonUtil::jsonStringToValue(in_extraJson));

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::UpdateReady, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::updateSettings(const FString &in_lobbyID, const FString &in_configJson, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyIdentifier.getValue(), in_lobbyID);
    message->SetObjectField(OperationParam::LobbySettings.getValue(), JsonUtil::jsonStringToValue(in_configJson));

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::UpdateSettings, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::switchTeam(const FString &in_lobbyID, const FString &in_teamCode, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyIdentifier.getValue(), in_lobbyID);
    message->SetStringField(OperationParam::LobbyTeamCode.getValue(), in_teamCode);

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::SwitchTeam, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::sendSignal(const FString &in_lobbyID, const FString &in_signalJson, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyIdentifier.getValue(), in_lobbyID);
    message->SetObjectField(OperationParam::LobbySignalData.getValue(), JsonUtil::jsonStringToValue(in_signalJson));

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::SendSignal, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::joinLobby(const FString &in_lobbyID, bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyIdentifier.getValue(), in_lobbyID);
    message->SetBoolField(OperationParam::LobbyIsReady.getValue(), in_isReady);
    message->SetObjectField(OperationParam::LobbyExtraJson.getValue(), JsonUtil::jsonStringToValue(in_extraJson));
    message->SetStringField(OperationParam::LobbyTeamCode.getValue(), in_teamCode);
    message->SetArrayField(OperationParam::LobbyOtherUserCxIds.getValue(), JsonUtil::arrayToJsonArray(in_otherUserCxIds));

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::JoinLobby, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::joinLobbyWithPingData(const FString &in_lobbyID, bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyIdentifier.getValue(), in_lobbyID);
    message->SetBoolField(OperationParam::LobbyIsReady.getValue(), in_isReady);
    message->SetObjectField(OperationParam::LobbyExtraJson.getValue(), JsonUtil::jsonStringToValue(in_extraJson));
    message->SetStringField(OperationParam::LobbyTeamCode.getValue(), in_teamCode);
    message->SetArrayField(OperationParam::LobbyOtherUserCxIds.getValue(), JsonUtil::arrayToJsonArray(in_otherUserCxIds));

// TODO : append ping data and send, or return right away the failure!
    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::JoinLobby, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::leaveLobby(const FString &in_lobbyID, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyIdentifier.getValue(), in_lobbyID);

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::LeaveLobby, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::removeMember(const FString &in_lobbyID, const FString &in_connectionId, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyIdentifier.getValue(), in_lobbyID);
    message->SetStringField(OperationParam::LobbyConnectionId.getValue(), in_connectionId);

    ServerCall *sc = new ServerCall(ServiceName::Lobby, ServiceOperation::RemoveMember, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::cancelFindRequest(const FString& in_lobbyType, IServerCallback* in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyRoomType.getValue(), in_lobbyType);
    message->SetStringField(OperationParam::LobbyConnectionId.getValue(), _client->getRTTConnectionId());

    ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::CancelFindRequest, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::getRegionsForLobbies(const TArray<FString> &in_roomTypes, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::LobbyTypes.getValue(), JsonUtil::arrayToJsonArray(in_roomTypes));

    ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::GetRegionsForLobbies, message, in_callback);
    _client->sendRequest(sc);

}

void BrainCloudLobby::pingRegions(IServerCallback* in_callback)
{
    
}