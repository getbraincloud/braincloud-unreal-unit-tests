// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudTournament.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"
#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"
#include <time.h>

namespace BrainCloud
{
	BrainCloudTournament::BrainCloudTournament(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudTournament::claimTournamentReward(const char * in_leaderboardId, int32_t in_versionId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;

		if (in_versionId > 0)
			message[OperationParam::VersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::ClaimTournamentReward, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::getTournamentStatus(const char * in_leaderboardId, int32_t in_versionId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;

		if (in_versionId > 0)
			message[OperationParam::VersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::GetTournamentStatus, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::joinTournament(const char * in_leaderboardId, const char * in_tournamentCode, int32_t in_initialScore, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::TournamentCode.getValue()] = in_tournamentCode;
		message[OperationParam::InitialScore.getValue()] = in_initialScore;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::JoinTournament, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::leaveTournament(const char * in_leaderboardId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::LeaveTournament, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::postTournamentScore(const char * in_leaderboardId, int32_t in_score, const std::string & in_jsonData, const tm * in_roundStartedTime, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::Score.getValue()] = in_score;

		struct tm timeInfo = *in_roundStartedTime;
		message[OperationParam::RoundStartedEpoch.getValue()] = Json::Int64(mktime(&timeInfo) * 1000);

		if (StringUtil::IsOptionalParameterValid(in_jsonData))
			message[OperationParam::Data.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::PostTournamentScore, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::viewCurrentReward(const char * in_leaderboardId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::ViewCurrentReward, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::viewReward(const char * in_leaderboardId, int32_t in_versionId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;

		if (in_versionId > 0)
			message[OperationParam::VersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::ViewCurrentReward, message, in_callback);
		m_client->sendRequest(sc);
	}
}