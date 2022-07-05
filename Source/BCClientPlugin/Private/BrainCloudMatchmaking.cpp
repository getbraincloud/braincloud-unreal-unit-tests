// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudMatchmaking.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudMatchmaking::BrainCloudMatchmaking(BrainCloudClient *client) : _client(client){};

void BrainCloudMatchmaking::read(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::Read, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::setPlayerRating(int32 playerRating, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetNumberField(OperationParam::MatchMakingServicePlayerRating.getValue(), playerRating);

    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::SetPlayerRating, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::resetPlayerRating(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::ResetPlayerRating, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::incrementPlayerRating(int32 increment, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetNumberField(OperationParam::MatchMakingServicePlayerRating.getValue(), increment);

    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::IncrementPlayerRating, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::decrementPlayerRating(int32 decrement, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetNumberField(OperationParam::MatchMakingServicePlayerRating.getValue(), decrement);

    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::DecrementPlayerRating, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::turnShieldOn(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::ShieldOn, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::turnShieldOnFor(int32 minutes, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetNumberField(OperationParam::MatchMakingServiceMinutes.getValue(), minutes);

    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::ShieldOnFor, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::turnShieldOff(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::ShieldOff, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::incrementShieldOnFor(int32 minutes, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetNumberField(OperationParam::MatchMakingServiceMinutes.getValue(), minutes);

    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::IncrementShieldOnFor, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::findPlayers(int32 rangeDelta, int32 numMatches, IServerCallback *callback)
{
    findPlayersWithAttributes(rangeDelta, numMatches, "", callback);
}

void BrainCloudMatchmaking::findPlayersWithAttributes(int32 rangeDelta, int32 numMatches, const FString &jsonAttributes, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetNumberField(OperationParam::MatchMakingServiceRangeDelta.getValue(), rangeDelta);
    message->SetNumberField(OperationParam::MatchMakingServiceNumMatches.getValue(), numMatches);

    if (OperationParam::isOptionalParamValid(jsonAttributes))
    {
        message->SetObjectField(OperationParam::MatchMakingServiceAttributes.getValue(), JsonUtil::jsonStringToValue(jsonAttributes));
    }

    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::FindPlayers, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::findPlayersUsingFilter(int32 rangeDelta, int32 numMatches, const FString &jsonExtraParms, IServerCallback *callback)
{
    findPlayersWithAttributesUsingFilter(rangeDelta, numMatches, "", jsonExtraParms, callback);
}

void BrainCloudMatchmaking::findPlayersWithAttributesUsingFilter(
    int32 rangeDelta,
    int32 numMatches,
    const FString &jsonAttributes,
    const FString &jsonExtraParms,
    IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetNumberField(OperationParam::MatchMakingServiceRangeDelta.getValue(), rangeDelta);
    message->SetNumberField(OperationParam::MatchMakingServiceNumMatches.getValue(), numMatches);

    if (OperationParam::isOptionalParamValid(jsonExtraParms))
    {
        message->SetObjectField(OperationParam::MatchMakingServiceExtraParams.getValue(), JsonUtil::jsonStringToValue(jsonExtraParms));
    }

    if (OperationParam::isOptionalParamValid(jsonAttributes))
    {
        message->SetObjectField(OperationParam::MatchMakingServiceAttributes.getValue(), JsonUtil::jsonStringToValue(jsonAttributes));
    }

    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::FindPlayersUsingFilter, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::enableMatchMaking(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::EnableMatchMaking, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudMatchmaking::disableMatchMaking(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::DisableMatchMaking, message, callback);
    _client->sendRequest(sc);
}