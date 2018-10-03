// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudLobby.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud
{
	BrainCloudLobby::BrainCloudLobby(BrainCloudClient* in_client)
		: m_client(in_client)
	{
	}
	
	void BrainCloudLobby::createLobby(const std::string& in_lobbyType, int in_rating, const std::vector<std::string>& in_otherUserCxIds, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, const std::string& in_jsonSettings, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyType.getValue()] = in_lobbyType;
		message[OperationParam::Rating.getValue()] = in_rating;
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());
		message[OperationParam::TeamCode.getValue()] = in_teamCode;
		message[OperationParam::Settings.getValue()] = JsonUtil::jsonStringToValue(in_jsonSettings.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::CreateLobby, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::findLobby(const std::string& in_lobbyType, int in_rating, int in_maxSteps, const std::string& in_jsonAlgo, const std::string& in_jsonFilter, const std::vector<std::string>& in_otherUserCxIds, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyType.getValue()] = in_lobbyType;
		message[OperationParam::Rating.getValue()] = in_rating;
		message[OperationParam::MaxSteps.getValue()] = in_maxSteps;
		message[OperationParam::Algo.getValue()] = JsonUtil::jsonStringToValue(in_jsonAlgo.c_str());
		message[OperationParam::Filter.getValue()] = JsonUtil::jsonStringToValue(in_jsonFilter.c_str());
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());
		message[OperationParam::TeamCode.getValue()] = in_teamCode;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::FindLobby, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::findOrCreateLobby(const std::string& in_lobbyType, int in_rating, int in_maxSteps, const std::string& in_jsonAlgo, const std::string& in_jsonFilter, const std::vector<std::string>& in_otherUserCxIds, const std::string& in_jsonSettings, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyType.getValue()] = in_lobbyType;
		message[OperationParam::Rating.getValue()] = in_rating;
		message[OperationParam::MaxSteps.getValue()] = in_maxSteps;
		message[OperationParam::Algo.getValue()] = JsonUtil::jsonStringToValue(in_jsonAlgo.c_str());
		message[OperationParam::Filter.getValue()] = JsonUtil::jsonStringToValue(in_jsonFilter.c_str());
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);
		message[OperationParam::Settings.getValue()] = JsonUtil::jsonStringToValue(in_jsonSettings.c_str());
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());
		message[OperationParam::TeamCode.getValue()] = in_teamCode;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::FindOrCreateLobby, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::getLobbyData(const std::string& in_lobbyId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::GetLobbyData, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::leaveLobby(const std::string& in_lobbyId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::LeaveLobby, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::removeMember(const std::string& in_lobbyId, const std::string& in_cxId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::CxId.getValue()] = in_cxId;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::RemoveMember, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::sendSignal(const std::string& in_lobbyId, const std::string& in_jsonSignalData, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::SignalData.getValue()] = JsonUtil::jsonStringToValue(in_jsonSignalData.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::SendSignal, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::switchTeam(const std::string& in_lobbyId, const std::string& in_toTeamCode, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::ToTeamCode.getValue()] = in_toTeamCode;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::SwitchTeam, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::updateReady(const std::string& in_lobbyId, bool in_isReady, const std::string& in_extraJson, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::UpdateReady, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::updateSettings(const std::string& in_lobbyId, const std::string& in_jsonSettings, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::Settings.getValue()] = JsonUtil::jsonStringToValue(in_jsonSettings.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::UpdateSettings, message, in_callback);
		m_client->sendRequest(sc);
	}
};
