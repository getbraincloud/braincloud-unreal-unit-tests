// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudAsyncMatch.h"

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
	BrainCloudAsyncMatch::BrainCloudAsyncMatch(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudAsyncMatch::createMatch(const char * in_jsonOpponentIds,
		const char * in_pushNotificationMessage,
		IServerCallback * in_callback)
	{
		createMatchInternal(in_jsonOpponentIds,
			NULL,
			in_pushNotificationMessage,
			NULL,
			NULL,
			NULL,
			in_callback);
	}

	void BrainCloudAsyncMatch::createMatchWithInitialTurn(const char * in_jsonOpponentIds,
		const char * in_jsonMatchState,
		const char * in_pushNotificationMessage,
		const char * in_nextPlayer,
		const char * in_jsonSummary,
		IServerCallback * in_callback)
	{
		createMatchInternal(in_jsonOpponentIds,
			StringUtil::IsOptionalParameterValid(in_jsonMatchState) ? in_jsonMatchState : "{}",
			in_pushNotificationMessage,
			NULL,
			in_nextPlayer,
			in_jsonSummary,
			in_callback);
	}

	void BrainCloudAsyncMatch::submitTurn(
		const char * in_ownerId,
		const char * in_matchId,
		uint64_t in_version,
		const char * in_jsonMatchState,
		const char * in_pushNotificationMessage,
		const char * in_nextPlayer,
		const char * in_jsonSummary,
		const char * in_jsonStatistics,
		IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId.getValue()] = in_matchId;
		message[OperationParam::AsyncMatchServiceVersion.getValue()] = (Json::UInt64) in_version;

		if (StringUtil::IsOptionalParameterValid(in_jsonMatchState)) {
			message[OperationParam::AsyncMatchServiceMatchState.getValue()] = JsonUtil::jsonStringToValue(in_jsonMatchState);
		}
		if (StringUtil::IsOptionalParameterValid(in_nextPlayer)) {
			message[OperationParam::AsyncMatchServiceMatchStatus.getValue()][OperationParam::AsyncMatchServiceCurrentPlayer.getValue()] = in_nextPlayer;
		}
		if (StringUtil::IsOptionalParameterValid(in_jsonSummary)) {
			message[OperationParam::AsyncMatchServiceMatchSummary.getValue()] = JsonUtil::jsonStringToValue(in_jsonSummary);
		}
		if (StringUtil::IsOptionalParameterValid(in_jsonStatistics)) {
			message[OperationParam::AsyncMatchServiceStatistics.getValue()] = JsonUtil::jsonStringToValue(in_jsonStatistics);
		}
		if (StringUtil::IsOptionalParameterValid(in_pushNotificationMessage)) {
			message[OperationParam::AsyncMatchServicePushMessage.getValue()] = in_pushNotificationMessage;
		}

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::SubmitTurn, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudAsyncMatch::updateMatchSummaryData(const char * in_ownerId, const char * in_matchId, uint64_t in_version, const char * in_jsonSummary, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId.getValue()] = in_matchId;
		message[OperationParam::AsyncMatchServiceVersion.getValue()] = (Json::UInt64) in_version;
		if (StringUtil::IsOptionalParameterValid(in_jsonSummary)) {
			message[OperationParam::AsyncMatchServiceMatchSummary.getValue()] = JsonUtil::jsonStringToValue(in_jsonSummary);
		}

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::UpdateMatchSummary, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudAsyncMatch::completeMatch(const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId.getValue()] = in_matchId;

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::Complete, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudAsyncMatch::readMatch(const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId.getValue()] = in_matchId;

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::ReadMatch, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudAsyncMatch::readMatchHistory(const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId.getValue()] = in_matchId;

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::ReadMatchHistory, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudAsyncMatch::findMatches(IServerCallback * in_callback)
	{
		Json::Value message;

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::FindMatches, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudAsyncMatch::findCompleteMatches(IServerCallback * in_callback)
	{
		Json::Value message;

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::FindMatchesCompleted, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudAsyncMatch::abandonMatch(const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId.getValue()] = in_matchId;

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::Abandon, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudAsyncMatch::deleteMatch(const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId.getValue()] = in_matchId;

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::DeleteMatch, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudAsyncMatch::createMatchInternal(const char * in_jsonOpponentIds,
		const char * in_jsonMatchState,
		const char * in_pushNotificationMessage,
		const char * in_matchId,
		const char * in_nextPlayer,
		const char * in_jsonSummary,
		IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServicePlayers.getValue()] = JsonUtil::jsonStringToValue(in_jsonOpponentIds);
		if (StringUtil::IsOptionalParameterValid(in_jsonMatchState)) {
			message[OperationParam::AsyncMatchServiceMatchState.getValue()] = JsonUtil::jsonStringToValue(in_jsonMatchState);
		}
		if (StringUtil::IsOptionalParameterValid(in_matchId)) {
			message[OperationParam::AsyncMatchServiceMatchId.getValue()] = in_matchId;
		}
		if (StringUtil::IsOptionalParameterValid(in_nextPlayer)) {
			message[OperationParam::AsyncMatchServiceMatchStatus.getValue()][OperationParam::AsyncMatchServiceCurrentPlayer.getValue()] = in_nextPlayer;
		}
		if (StringUtil::IsOptionalParameterValid(in_jsonSummary)) {
			message[OperationParam::AsyncMatchServiceMatchSummary.getValue()] = JsonUtil::jsonStringToValue(in_jsonSummary);
		}
		if (StringUtil::IsOptionalParameterValid(in_pushNotificationMessage)) {
			message[OperationParam::AsyncMatchServicePushMessage.getValue()] = in_pushNotificationMessage;
		}

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::Create, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

    void BrainCloudAsyncMatch::completeMatchWithSummaryData( const char * in_ownerId, const char * in_matchId, const char* in_pushContent, const std::string& in_summary, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId.getValue()] = in_matchId;
		if(in_pushContent !=NULL)
		{
		message[OperationParam::AsyncMatchServicePushMessage.getValue()] = in_pushContent;
		}
		message[OperationParam::AsyncMatchServiceMatchSummary.getValue()] = JsonUtil::jsonStringToValue(in_summary);

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::CompleteMatchWithSummaryData, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}
        
    void BrainCloudAsyncMatch::abandonMatchWithSummaryData( const char * in_ownerId, const char * in_matchId, const char* in_pushContent, const std::string& in_summary, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId.getValue()] = in_matchId;
		if(in_pushContent != NULL)
		{
		message[OperationParam::AsyncMatchServicePushMessage.getValue()] = in_pushContent;
		}
		message[OperationParam::AsyncMatchServiceMatchSummary.getValue()] = JsonUtil::jsonStringToValue(in_summary);

		ServerCall * sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::AbandonMatchWithSummaryData, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

}  // end namespace
