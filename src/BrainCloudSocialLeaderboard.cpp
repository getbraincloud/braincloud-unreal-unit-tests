// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudSocialLeaderboard.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/JsonUtil.h"
#include <time.h>

namespace BrainCloud
{
	BrainCloudSocialLeaderboard::BrainCloudSocialLeaderboard(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudSocialLeaderboard::getSocialLeaderboard(const char * in_leaderboardId, bool in_replaceName, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceReplaceName.getValue()] = in_replaceName;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetSocialLeaderboard, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getSocialLeaderboardByVersion(const char * in_leaderboardId, bool in_replaceName, int in_versionId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceReplaceName.getValue()] = in_replaceName;
		message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetSocialLeaderboardByVersion, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getMultiSocialLeaderboard(const std::vector<std::string> & in_leaderboardIds, int in_leaderboardResultCount, bool in_replaceName, IServerCallback * in_callback)
	{
		Json::Value message;
		if (in_leaderboardIds.size() > 0)
		{
			message[OperationParam::SocialLeaderboardServiceLeaderboardIds.getValue()] = JsonUtil::stringVectorToJson(in_leaderboardIds);
		}
		message[OperationParam::SocialLeaderboardServiceLeaderboardResultCount.getValue()] = in_leaderboardResultCount;
		message[OperationParam::SocialLeaderboardServiceReplaceName.getValue()] = in_replaceName;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetMultiSocialLeaderboard, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getGlobalLeaderboardPage(const char * in_leaderboardId, SortOrder in_sortOrder, int in_startIndex,
		int in_endIndex, IServerCallback * in_callback)
	{
		std::string sortOrder = sortOrderToString(in_sortOrder);

		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = sortOrder;
		message[OperationParam::SocialLeaderboardServiceStartIndex.getValue()] = in_startIndex;
		message[OperationParam::SocialLeaderboardServiceEndIndex.getValue()] = in_endIndex;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardPage, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getGlobalLeaderboardPageByVersion(const char * in_leaderboardId, SortOrder in_sortOrder, int in_startIndex, int in_endIndex, int in_versionId, IServerCallback * in_callback)
	{
		std::string sortOrder = sortOrderToString(in_sortOrder);

		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = sortOrder;
		message[OperationParam::SocialLeaderboardServiceStartIndex.getValue()] = in_startIndex;
		message[OperationParam::SocialLeaderboardServiceEndIndex.getValue()] = in_endIndex;
		message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardPage, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getGlobalLeaderboardView(const char * in_leaderboardId, SortOrder in_sortOrder, int in_beforeCount,
		int in_afterCount, IServerCallback * in_callback)
	{
		getGlobalLeaderboardViewByVersion(in_leaderboardId, in_sortOrder, in_beforeCount, in_afterCount, -1, in_callback);
	}

	void BrainCloudSocialLeaderboard::getGlobalLeaderboardViewByVersion(const char * in_leaderboardId, SortOrder in_sortOrder, int in_beforeCount,
		int in_afterCount, int in_versionId, IServerCallback * in_callback)
	{
		std::string sortOrder = sortOrderToString(in_sortOrder);

		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = sortOrder;
		message[OperationParam::SocialLeaderboardServiceBeforeCount.getValue()] = in_beforeCount;
		message[OperationParam::SocialLeaderboardServiceAfterCount.getValue()] = in_afterCount;
		if (in_versionId != -1) message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardView, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getGlobalLeaderboardVersions(const char * in_leaderboardId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardVersions, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::postScoreToLeaderboard(const char * in_leaderboardId, int64_t in_score, const std::string& in_jsonOtherData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceScore.getValue()] = (Json::Int64) in_score;
		message[OperationParam::SocialLeaderboardServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonOtherData);

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScore, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::postScoreToDynamicLeaderboard(
		const char * in_leaderboardId,
		int64_t in_score,
		const std::string& in_jsonData,
		SocialLeaderboardType in_leaderboardType,
		RotationType in_rotationType,
		struct tm* in_rotationResetUTC,
		int in_retainedCount,
		IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceScore.getValue()] = (Json::Int64) in_score;
		message[OperationParam::SocialLeaderboardServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		message[OperationParam::SocialLeaderboardServiceLeaderboardType.getValue()] = leaderboardTypeToString(in_leaderboardType).c_str();
		message[OperationParam::SocialLeaderboardServiceRotationType.getValue()] = leaderboardRotationTypeToString(in_rotationType).c_str();

		if (in_rotationResetUTC != NULL)
		{
			time_t timestamp = mktime(in_rotationResetUTC);
			int64_t time = (int64_t)timestamp * 1000;
			message[OperationParam::SocialLeaderboardServiceRotationResetTime.getValue()] = (Json::UInt64)time;
		}
		message[OperationParam::SocialLeaderboardServiceRetainedCount.getValue()] = in_retainedCount;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreDynamic, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}


	void BrainCloudSocialLeaderboard::postScoreToDynamicLeaderboardDays(
		const char * in_leaderboardId,
		int64_t in_score,
		const std::string& in_jsonData,
		SocialLeaderboardType in_leaderboardType,
		struct tm* in_rotationResetUTC,
		int32_t in_retainedCount,
		int32_t in_numDaysToRotate,
		IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceScore.getValue()] = (Json::Int64) in_score;
		message[OperationParam::SocialLeaderboardServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		message[OperationParam::SocialLeaderboardServiceLeaderboardType.getValue()] = leaderboardTypeToString(in_leaderboardType).c_str();
		message[OperationParam::SocialLeaderboardServiceRotationType.getValue()] = "DAYS";
		message[OperationParam::NumDaysToRotate.getValue()] = in_numDaysToRotate;

		if (in_rotationResetUTC != NULL)
		{
			time_t timestamp = mktime(in_rotationResetUTC);
			int64_t time = (int64_t)timestamp * 1000;
			message[OperationParam::SocialLeaderboardServiceRotationResetTime.getValue()] = (Json::UInt64)time;
		}
		message[OperationParam::SocialLeaderboardServiceRetainedCount.getValue()] = in_retainedCount;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreDynamic, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::removePlayerScore(const char * in_leaderboardId, int32_t in_versionId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		if (in_versionId != -1) message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::RemovePlayerScore, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::playerTournamentReward(const char * in_eventName, uint64_t in_multiplier, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceEventName.getValue()] = in_eventName;
		message[OperationParam::SocialLeaderboardServiceEventMultiplier.getValue()] = (Json::UInt64) in_multiplier;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::RewardTournament, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getGroupSocialLeaderboard(const char * in_leaderboardId, const char * in_groupId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::GroupId.getValue()] = in_groupId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGroupSocialLeaderboard, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getGroupSocialLeaderboardByVersion(const char * in_leaderboardId, const char * in_groupId, int in_versionId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGroupSocialLeaderboardByVersion, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getPlayersSocialLeaderboard(const char * in_leaderboardId, std::vector<std::string> in_profileIds, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::ProfileIds.getValue()] = JsonUtil::stringVectorToJson(in_profileIds);

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetPlayersSocialLeaderboard, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getPlayersSocialLeaderboardByVersion(const char * in_leaderboardId, std::vector<std::string> in_profileIds, int in_versionId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::ProfileIds.getValue()] = JsonUtil::stringVectorToJson(in_profileIds);
		message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetPlayersSocialLeaderboardByVersion, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::listAllLeaderboards(IServerCallback * in_callback)
	{
		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::ListAllLeaderboards, Json::nullValue, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getGlobalLeaderboardEntryCount(const char * in_leaderboardId, IServerCallback * in_callback)
	{
		getGlobalLeaderboardEntryCountByVersion(in_leaderboardId, -1, in_callback);
	}

	void BrainCloudSocialLeaderboard::getGlobalLeaderboardEntryCountByVersion(const char * in_leaderboardId, int32_t in_versionId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		if (in_versionId != -1) message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardEntryCount, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getPlayerScore(const char * in_leaderboardId, int32_t in_versionId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		if (in_versionId != -1) message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetPlayerScore, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getPlayerScoresFromLeaderboards(const std::vector<std::string> & in_leaderboardIds, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardIds.getValue()] = JsonUtil::stringVectorToJson(in_leaderboardIds);

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetPlayerScoresFromLeaderboards, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::postScoreToGroupLeaderboard(const char * in_leaderboardId, const char * in_groupId, int32_t in_score, const std::string& in_jsonData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::SocialLeaderboardServiceScore.getValue()] = in_score;
		message[OperationParam::SocialLeaderboardServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreToGroupLeaderboard, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::postScoreToDynamicGroupLeaderboard(const char * in_leaderboardId, const char * in_groupId, int32_t in_score, const std::string& in_jsonData, const char * in_leaderboardType, 
		const char * in_rotationType, struct tm* in_rotationResetUTC, int32_t in_retainedCount,  IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::SocialLeaderboardServiceScore.getValue()] = in_score;
		message[OperationParam::SocialLeaderboardServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);
		message[OperationParam::SocialLeaderboardServiceLeaderboardType.getValue()] = in_leaderboardType;
		message[OperationParam::SocialLeaderboardServiceRotationType.getValue()] = in_rotationType;
		if (in_rotationResetUTC != NULL)
		{
			time_t timestamp = mktime(in_rotationResetUTC);
			int64_t time = (int64_t)timestamp * 1000;
			message[OperationParam::SocialLeaderboardServiceRotationResetTime.getValue()] = (Json::UInt64)time;
		}
		message[OperationParam::SocialLeaderboardServiceRetainedCount.getValue()] = in_retainedCount;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreToDynamicGroupLeaderboard, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::removeGroupScore(const char * in_leaderboardId, const char * in_groupId, int32_t in_versionId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::GroupId.getValue()]= in_groupId;
		message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::RemoveGroupScore, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudSocialLeaderboard::getGroupLeaderboardView(const char * in_leaderboardId, const char * in_groupId, SortOrder in_sortOrder, int32_t in_beforeCount, int32_t in_afterCount, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		std::string sortOrder = sortOrderToString(in_sortOrder);
		message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = sortOrder;
		message[OperationParam::SocialLeaderboardServiceBeforeCount.getValue()] = in_beforeCount;
		message[OperationParam::SocialLeaderboardServiceAfterCount.getValue()] = in_afterCount;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGroupLeaderboardView, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}
		
	void BrainCloudSocialLeaderboard::getGroupLeaderboardViewByVersion(const char * in_leaderboardId, const char * in_groupId, int32_t in_versionId, SortOrder in_sortOrder, int32_t in_beforeCount, int32_t in_afterCount, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;
		std::string sortOrder = sortOrderToString(in_sortOrder);
		message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = sortOrder;
		message[OperationParam::SocialLeaderboardServiceBeforeCount.getValue()] = in_beforeCount;
		message[OperationParam::SocialLeaderboardServiceAfterCount.getValue()] = in_afterCount;

		ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGroupLeaderboardView, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	std::string BrainCloudSocialLeaderboard::leaderboardTypeToString(SocialLeaderboardType type)
	{
		std::string typeString = "HIGH_VALUE";

		if (type == CUMULATIVE)
			typeString = "CUMULATIVE";
		else if (type == LAST_VALUE)
			typeString = "LAST_VALUE";
		else if (type == LOW_VALUE)
			typeString = "LOW_VALUE";

		return typeString;
	}

	std::string BrainCloudSocialLeaderboard::leaderboardRotationTypeToString(RotationType type)
	{
		std::string typeString = "NEVER";

		switch (type)
		{
		case DAILY:
			typeString = "DAILY";
			break;
		case WEEKLY:
			typeString = "WEEKLY";
			break;
		case MONTHLY:
			typeString = "MONTHLY";
			break;
		case YEARLY:
			typeString = "YEARLY";
			break;
		default:
			break;
		}

		return typeString;
	}

	std::string BrainCloudSocialLeaderboard::sortOrderToString(SortOrder in_sortOrder)
	{
		std::string sortOrder = "HIGHEST_RANKED";

		if (in_sortOrder == HIGH_TO_LOW)
		{
			sortOrder = "HIGH_TO_LOW";
		}
		else if (in_sortOrder == LOW_TO_HIGH)
		{
			sortOrder = "LOW_TO_HIGH";
		}
		else
		{
			sortOrder = "HIGHEST_RANKED";
		}
		return sortOrder;
	}
}
