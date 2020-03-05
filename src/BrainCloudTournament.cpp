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
#include "braincloud/internal/timegm.h"

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

	void BrainCloudTournament::getDivisionInfo(const std::string& in_divSetId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::DivSetID.getValue()] = in_divSetId;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::GetDivisionInfo, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::getMyDivisions(IServerCallback * in_callback)
	{
		Json::Value message;
		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::GetMyDivisions, message, in_callback);
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

	void BrainCloudTournament::joinDivision(const std::string& in_divSetId, const std::string& in_tournamentCode, int64_t in_initialScore, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::DivSetID.getValue()] = in_divSetId;
		message[OperationParam::TournamentCode.getValue()] = in_tournamentCode;
		message[OperationParam::InitialScore.getValue()] = (Json::Int64) in_initialScore;

		
		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::JoinDivision, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::joinTournament(const char * in_leaderboardId, const char * in_tournamentCode, int64_t in_initialScore, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::TournamentCode.getValue()] = in_tournamentCode;
		message[OperationParam::InitialScore.getValue()] = (Json::Int64) in_initialScore;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::JoinTournament, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::leaveDivisionInstance(const std::string& in_leaderboardId, IServerCallback * in_callback)
	{
		Json::Value message; 
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::LeaveDivisionInstance, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::leaveTournament(const char * in_leaderboardId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::LeaveTournament, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::postTournamentScore(const char * in_leaderboardId, int64_t in_score, const std::string & in_jsonData, const tm * in_roundStartedTimeUTC, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::Score.getValue()] = (Json::Int64) in_score;

		struct tm timeInfo = *in_roundStartedTimeUTC;
		message[OperationParam::RoundStartedEpoch.getValue()] = (Json::Int64) ((int64_t)internal_timegm(&timeInfo)) * 1000;

		if (StringUtil::IsOptionalParameterValid(in_jsonData))
			message[OperationParam::Data.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::PostTournamentScore, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::postTournamentScoreUTC(const char * in_leaderboardId, int64_t in_score, const std::string & in_jsonData, int64_t in_roundStartedTimeUTC, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::Score.getValue()] = (Json::Int64) in_score;

		message[OperationParam::RoundStartedEpoch.getValue()] = (Json::Int64) in_roundStartedTimeUTC;

		if (StringUtil::IsOptionalParameterValid(in_jsonData))
			message[OperationParam::Data.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::PostTournamentScore, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudTournament::postTournamentScoreWithResults(
		const char * in_leaderboardId,
		int64_t in_score,
		const std::string & in_jsonData,
		const tm * in_roundStartedTimeLocal,
		SortOrder in_sort,
		int32_t in_beforeCount,
		int32_t in_afterCount,
		int64_t in_initialScore,
		IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::Score.getValue()] = (Json::Int64) in_score;

		struct tm timeInfo = *in_roundStartedTimeLocal;
		message[OperationParam::RoundStartedEpoch.getValue()] = (Json::Int64) ((int64_t)internal_timegm(&timeInfo)) * 1000;

		if (StringUtil::IsOptionalParameterValid(in_jsonData))
			message[OperationParam::Data.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = BrainCloudSocialLeaderboard::sortOrderToString(in_sort);
		message[OperationParam::SocialLeaderboardServiceBeforeCount.getValue()] = in_beforeCount;
		message[OperationParam::SocialLeaderboardServiceAfterCount.getValue()] = in_afterCount;
		message[OperationParam::InitialScore.getValue()] = (Json::Int64) in_initialScore;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::PostTournamentScoreWithResults, message, in_callback);
		m_client->sendRequest(sc);
	}

		void BrainCloudTournament::postTournamentScoreWithResultsUTC(
		const char * in_leaderboardId,
		int64_t in_score,
		const std::string & in_jsonData,
		int64_t in_roundStartedTimeUTC,
		SortOrder in_sort,
		int32_t in_beforeCount,
		int32_t in_afterCount,
		int64_t in_initialScore,
		IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::LeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::Score.getValue()] = (Json::Int64) in_score;

		message[OperationParam::RoundStartedEpoch.getValue()] = (Json::Int64) in_roundStartedTimeUTC;

		if (StringUtil::IsOptionalParameterValid(in_jsonData))
			message[OperationParam::Data.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = BrainCloudSocialLeaderboard::sortOrderToString(in_sort);
		message[OperationParam::SocialLeaderboardServiceBeforeCount.getValue()] = in_beforeCount;
		message[OperationParam::SocialLeaderboardServiceAfterCount.getValue()] = in_afterCount;
		message[OperationParam::InitialScore.getValue()] = (Json::Int64) in_initialScore;

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::PostTournamentScoreWithResults, message, in_callback);
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

		ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::ViewReward, message, in_callback);
		m_client->sendRequest(sc);
	}
}