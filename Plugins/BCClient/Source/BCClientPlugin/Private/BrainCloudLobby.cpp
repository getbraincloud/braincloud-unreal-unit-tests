// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudLobby.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudWrapper.h"
#include "BrainCloudClient.h"
#include "ReasonCodes.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializer.h"

BrainCloudLobby::BrainCloudLobby(BrainCloudClient *client)
 : _client(client)
 , _regionsForLobbiesCallback(nullptr)
 , _pingRegionsCallback(nullptr)
 , _regionPingData(nullptr)
 , _pingData(nullptr)
 {
     _http = &FHttpModule::Get();
 }

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

    attachPingDataAndSend(message, ServiceOperation::FindLobbyWithPingData, in_callback);
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

    attachPingDataAndSend(message, ServiceOperation::CreateLobbyWithPingData, in_callback);
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

    attachPingDataAndSend(message, ServiceOperation::FindOrCreateLobbyWithPingData, in_callback);
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

    attachPingDataAndSend(message, ServiceOperation::JoinLobbyWithPingData, in_callback);
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
    message->SetStringField(OperationParam::LobbyConnectionId.getValue(), _client->getRTTService()->getRTTConnectionId());

    ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::CancelFindRequest, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::getRegionsForLobbies(const TArray<FString> &in_roomTypes, IServerCallback *in_callback)
{
    _regionsForLobbiesCallback = in_callback;
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::LobbyTypes.getValue(), JsonUtil::arrayToJsonArray(in_roomTypes));

    // pass in our own handler of this callback, 
    ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::GetRegionsForLobbies, message, this);
    _client->sendRequest(sc);
}

void BrainCloudLobby::pingRegions(IServerCallback* in_callback)
{
    _pingRegionsCallback = in_callback;
    _pingData = MakeShareable(new FJsonObject());
    _cachedPingResponses.Empty();
    FString targetStr;

    //Are there regions?
    if (_regionPingData.IsValid())
    {
        // iterate over pingable hosts, doing appropriate ping tests for each one
        FString name;
        TSharedPtr<FJsonValue> value;
        TSharedPtr<FJsonObject> valueObj;

        //iterate over the regionPingData
        for (auto currJsonValue = _regionPingData->Values.CreateConstIterator(); currJsonValue; ++currJsonValue)
        {
            // Get the key name
            name = (*currJsonValue).Key;
            // Get the value as a FJsonValue object
            value = (*currJsonValue).Value;
            valueObj = value->AsObject();

            //is the region of Ping type?
            if (valueObj->HasField("type") && valueObj->GetStringField("type") == "PING")
            {
	            TArray<double> newArray;
                _cachedPingResponses.Emplace(name, newArray);

                //update the string of the target 
                targetStr = "http://" + valueObj->GetStringField("target");

                Mutex.Lock();
                //ping that region 4 times. 
                for (int i = 0; i < MAX_PING_CALLS; i++)
                {
                    TPair<FString, FString> pair = MakeTuple(name, targetStr);
                    m_regionTargetsToProcess.Emplace(pair);
                }
                Mutex.Unlock();
            }
        }
        pingNextItemToProcess();
    }
    else 
    {
        // call the server error right away!
        if (in_callback != nullptr)
        {
            UE_LOG(LogBrainCloudComms, Log, TEXT("calling error has callback"));
            FString messageJson = UBrainCloudWrapper::buildErrorJson(400, ReasonCodes::MISSING_REQUIRED_PARAMETER, 
                "No Regions to Ping. Please call GetRegionsForLobbies and await the response before calling PingRegions.");
            in_callback->serverError(ServiceName::Lobby, ServiceOperation::GetRegionsForLobbies, 400, ReasonCodes::MISSING_REQUIRED_PARAMETER, messageJson);
        }
    }
}

void BrainCloudLobby::getLobbyInstances(const FString &in_lobbyType, const FString &in_criteriaJson, IServerCallback* in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyRoomType.getValue(),in_lobbyType);
    message->SetObjectField(OperationParam::LobbyCriteria.getValue(),JsonUtil::jsonStringToValue(in_criteriaJson));
    
    ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::GetLobbyInstances, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudLobby::getLobbyInstancesWithPingData(const FString& in_lobbyType, const FString& in_criteriaJson, IServerCallback* in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LobbyRoomType.getValue(),in_lobbyType);
    message->SetObjectField(OperationParam::LobbyCriteria.getValue(),JsonUtil::jsonStringToValue(in_criteriaJson));
    
    attachPingDataAndSend(message,ServiceOperation::GetLobbyInstancesWithPingData,in_callback);
}

void BrainCloudLobby::pingNextItemToProcess()
{
    Mutex.Lock();
    if(m_regionTargetsToProcess.Num() > 0)
    {
        FString region;
        for(int i = 0; i < NUM_PING_CALLS_IN_PARALLEL && m_regionTargetsToProcess.Num() > 0; i++)
        {
            region = m_regionTargetsToProcess[0].Key;
            pingHost(region, m_regionTargetsToProcess[0].Value,_cachedPingResponses[region].Num() );
            m_regionTargetsToProcess.RemoveAt(0);
        }
    }
    else if (_regionPingData->Values.Num() == _pingData->Values.Num() && _pingRegionsCallback != nullptr)
    {
        FString serializedPingData;
		TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&serializedPingData);
        if(FJsonSerializer::Serialize(_pingData.ToSharedRef(), writer))
        {
            _pingRegionsCallback->serverCallback(ServiceName::Lobby, ServiceOperation::PingData, serializedPingData);
        }
    }
    Mutex.Unlock();
}

void BrainCloudLobby::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const &jsonData)
{
    if (serviceName == ServiceName::Lobby && serviceOperation == ServiceOperation::GetRegionsForLobbies)
    {
        TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(jsonData);
        TSharedPtr<FJsonObject> jsonPacket = MakeShareable(new FJsonObject());
        bool res = FJsonSerializer::Deserialize(reader, jsonPacket);
    
        if (res)
        {
            TSharedPtr<FJsonObject> data = jsonPacket->GetObjectField("data");
            _regionPingData = data->GetObjectField("regionPingData");
        }
    
        if (_regionsForLobbiesCallback != nullptr)
        {
            _regionsForLobbiesCallback->serverCallback(serviceName, serviceOperation, jsonData);
        }
    }
}

void BrainCloudLobby::serverError(ServiceName serviceName, ServiceOperation serviceOperation,
                                     int32 statusCode, int32 reasonCode, const FString &message)
{
    
    if (serviceName == ServiceName::Lobby && serviceOperation == ServiceOperation::GetRegionsForLobbies)
    {
        if (_regionsForLobbiesCallback != nullptr)
        {
            _regionsForLobbiesCallback->serverError(serviceName, serviceOperation, statusCode, reasonCode, message);
        }
    }
    
}

void BrainCloudLobby::attachPingDataAndSend(TSharedRef<FJsonObject> message, ServiceOperation serviceOperation, IServerCallback *in_callback)
{
    bool hasPingData = _pingData.IsValid();
    if (hasPingData)
    {
        message->SetObjectField(OperationParam::PingData.getValue(),  _pingData);
        ServerCall* sc = new ServerCall(ServiceName::Lobby, serviceOperation, message, in_callback);
        _client->sendRequest(sc);
    }
    else 
    {
        // call the server error right away!
        if (in_callback != nullptr)
        {
            FString messageJson = UBrainCloudWrapper::buildErrorJson(400, ReasonCodes::MISSING_REQUIRED_PARAMETER, 
                "Processing exception (message): Required message parameter 'pingData' is missing.  Please ensure PingData exists by first calling GetRegionsForLobbies and PingRegions, and waiting for response before proceeding.");
            
            in_callback->serverError(ServiceName::Lobby, serviceOperation, 400, ReasonCodes::MISSING_REQUIRED_PARAMETER, messageJson);
        }
    }
}

void BrainCloudLobby::pingHost(FString in_region, FString in_target, int in_index)
{
    {
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 25) || ENGINE_MAJOR_VERSION == 5
        TSharedRef<IHttpRequest,ESPMode::ThreadSafe> Request = _http->CreateRequest();
#else
        TSharedRef<IHttpRequest> Request = _http->CreateRequest();
#endif
	    Request->OnProcessRequestComplete().BindRaw(this, &BrainCloudLobby::onPingResponseReceived);

	    //This is the url on which to process the request
	    Request->SetURL(in_target);
	    Request->SetVerb("GET");
        Request->SetHeader("region", in_region);
        Request->SetHeader("index", FString::FromInt(in_index));
        
        // set the time so that the resonse can have the proper diff
        _cachedPingResponses[in_region].Add(FPlatformTime::Seconds());

	    Request->ProcessRequest();
    }
}

void BrainCloudLobby::onPingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    FString region = Request->GetHeader("region");
    int index = FCString::Atoi(*Request->GetHeader("index"));
    double origValue = _cachedPingResponses[region][index];

    // update it to be the diff
    _cachedPingResponses[region][index] = (FPlatformTime::Seconds() - origValue) * 1000;
    
    if (index == MAX_PING_CALLS - 1)
    {
        double totalAccumulated = 0;
        double highestValue = 0;
        double pingResponse = 0;
        int32 numElements = _cachedPingResponses[region].Num();
        for (int i = 0; i < numElements; ++i)
        {
            pingResponse = _cachedPingResponses[region][i];
            totalAccumulated += pingResponse;
            if (pingResponse > highestValue)
            {
                highestValue = pingResponse;
            }
        }

        // accumulated ALL, now subtract the highest value
        totalAccumulated -= highestValue;
        _pingData->SetNumberField(region, totalAccumulated / (numElements - 1));
    }
    
    pingNextItemToProcess();
}

