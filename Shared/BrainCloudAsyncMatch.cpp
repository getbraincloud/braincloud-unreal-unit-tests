
#include "BrainCloudAsyncMatch.h"

#include "BrainCloudTypes.h"
#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "StringUtil.h"


namespace BrainCloud {

	void BrainCloudAsyncMatch::createMatch( const char * in_jsonOpponentIds,
				const char * in_pushNotificationMessage,
				const char * in_matchId,
				IServerCallback * in_callback )
	{
        createMatchInternal(in_jsonOpponentIds,
                            NULL,
                            in_pushNotificationMessage,
                            in_matchId,
                            NULL,
                            NULL,
                            in_callback);
	}
    
    void BrainCloudAsyncMatch::createMatch( const char * in_jsonOpponentIds,
                                           const char * in_pushNotificationMessage,
                                           IServerCallback * in_callback )
    {
        createMatchInternal(in_jsonOpponentIds,
                            NULL,
                            in_pushNotificationMessage,
                            NULL,
                            NULL,
                            NULL,
                            in_callback);
    }

    void BrainCloudAsyncMatch::createMatchWithInitialTurn( const char * in_jsonOpponentIds,
                                                          const char * in_jsonMatchState,
                                                          const char * in_pushNotificationMessage,
                                                          const char * in_nextPlayer,
                                                          const char * in_jsonSummary,
                                                          IServerCallback * in_callback )
    {
        createMatchInternal(in_jsonOpponentIds,
                            StringUtil::IsOptionalParameterValid(in_jsonMatchState) ? in_jsonMatchState : "{}",
                            in_pushNotificationMessage,
                            NULL,
                            in_nextPlayer,
                            in_jsonSummary,
                            in_callback);
    }
    
	void BrainCloudAsyncMatch::createMatchWithInitialTurn( const char * in_jsonOpponentIds,
				const char * in_jsonMatchState,
				const char * in_pushNotificationMessage,
				const char * in_matchId,
				const char * in_nextPlayer,
				const char * in_jsonSummary,
				IServerCallback * in_callback )
	{
		createMatchInternal(in_jsonOpponentIds,
                            StringUtil::IsOptionalParameterValid(in_jsonMatchState) ? in_jsonMatchState : "{}",
                            in_pushNotificationMessage,
                            in_matchId,
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
		BrainCloudClient* brainCloudClient = BrainCloudClient::getInstance();
		
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId .getValue()] = in_matchId;
        message[OperationParam::AsyncMatchServiceVersion.getValue()] = (Json::UInt64) in_version;
        
		if (StringUtil::IsOptionalParameterValid(in_jsonMatchState)) {
			message[OperationParam::AsyncMatchServiceMatchState.getValue()] = brainCloudClient->jsonStringToValue( in_jsonMatchState );
		}
		if (StringUtil::IsOptionalParameterValid(in_nextPlayer)) {
			message[OperationParam::AsyncMatchServiceMatchStatus.getValue()][OperationParam::AsyncMatchServiceCurrentPlayer.getValue()] = in_nextPlayer;
		}
		if (StringUtil::IsOptionalParameterValid(in_jsonSummary)) {
			message[OperationParam::AsyncMatchServiceMatchSummary.getValue()] = brainCloudClient->jsonStringToValue( in_jsonSummary );
		}
		if (StringUtil::IsOptionalParameterValid(in_jsonStatistics)) {
			message[OperationParam::AsyncMatchServiceStatistics.getValue()] = brainCloudClient->jsonStringToValue( in_jsonStatistics );
		}
		if (StringUtil::IsOptionalParameterValid(in_pushNotificationMessage)) {
			message[OperationParam::AsyncMatchServicePushMessage.getValue()] = in_pushNotificationMessage;
		}

		ServerCall * sc = new ServerCall( ServiceName::AsyncMatch, ServiceOperation::SubmitTurn, message, in_callback );
		brainCloudClient->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudAsyncMatch:: updateMatchSummaryData( const char * in_ownerId, const char * in_matchId, uint64_t in_version, const char * in_jsonSummary, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId .getValue()] = in_matchId;
		message[OperationParam::AsyncMatchServiceVersion.getValue()] = (Json::UInt64) in_version;
		if (StringUtil::IsOptionalParameterValid(in_jsonSummary)) {
			message[OperationParam::AsyncMatchServiceMatchSummary.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue( in_jsonSummary );
		}

		ServerCall * sc = new ServerCall( ServiceName::AsyncMatch, ServiceOperation::UpdateMatchSummary, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudAsyncMatch::completeMatch( const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId .getValue()] = in_matchId;

		ServerCall * sc = new ServerCall( ServiceName::AsyncMatch, ServiceOperation::Complete, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudAsyncMatch::readMatch( const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId .getValue()] = in_matchId;

		ServerCall * sc = new ServerCall( ServiceName::AsyncMatch, ServiceOperation::ReadMatch, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudAsyncMatch::readMatchHistory( const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId .getValue()] = in_matchId;

		ServerCall * sc = new ServerCall( ServiceName::AsyncMatch, ServiceOperation::ReadMatchHistory, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudAsyncMatch::findMatches( IServerCallback * in_callback )
	{
		Json::Value message;

		ServerCall * sc = new ServerCall( ServiceName::AsyncMatch, ServiceOperation::FindMatches, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudAsyncMatch::findCompleteMatches( IServerCallback * in_callback )
	{
		Json::Value message;

		ServerCall * sc = new ServerCall( ServiceName::AsyncMatch, ServiceOperation::FindMatchesCompleted, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudAsyncMatch::abandonMatch( const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId .getValue()] = in_matchId;

		ServerCall * sc = new ServerCall( ServiceName::AsyncMatch, ServiceOperation::Abandon, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudAsyncMatch::deleteMatch( const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::AsyncMatchServiceOwnerId.getValue()] = in_ownerId;
		message[OperationParam::AsyncMatchServiceMatchId .getValue()] = in_matchId;

		ServerCall * sc = new ServerCall( ServiceName::AsyncMatch, ServiceOperation::DeleteMatch, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
    
    void BrainCloudAsyncMatch::createMatchInternal(const char * in_jsonOpponentIds,
                             const char * in_jsonMatchState,
                             const char * in_pushNotificationMessage,
                             const char * in_matchId,
                             const char * in_nextPlayer,
                             const char * in_jsonSummary,
                             IServerCallback * in_callback)
    {
        BrainCloudClient* brainCloudClient = BrainCloudClient::getInstance();
        
        Json::Value message;
        message[OperationParam::AsyncMatchServicePlayers.getValue()] = brainCloudClient->jsonStringToValue( in_jsonOpponentIds );
        if (StringUtil::IsOptionalParameterValid(in_jsonMatchState)) {
            message[OperationParam::AsyncMatchServiceMatchState.getValue()] = brainCloudClient->jsonStringToValue( in_jsonMatchState );
        }
        if (StringUtil::IsOptionalParameterValid(in_matchId)) {
            message[OperationParam::AsyncMatchServiceMatchId .getValue()] = in_matchId;
        }
        if (StringUtil::IsOptionalParameterValid(in_nextPlayer)) {
            message[OperationParam::AsyncMatchServiceMatchStatus.getValue()][OperationParam::AsyncMatchServiceCurrentPlayer.getValue()] = in_nextPlayer;
        }
        if (StringUtil::IsOptionalParameterValid(in_jsonSummary)) {
            message[OperationParam::AsyncMatchServiceMatchSummary.getValue()] = brainCloudClient->jsonStringToValue( in_jsonSummary );
        }
        if (StringUtil::IsOptionalParameterValid(in_pushNotificationMessage)) {
            message[OperationParam::AsyncMatchServicePushMessage.getValue()] = in_pushNotificationMessage;
        }
        
        ServerCall * sc = new ServerCall( ServiceName::AsyncMatch, ServiceOperation::Create, message, in_callback );
        brainCloudClient->getBrainCloudComms()->addToQueue( sc );
    }

}  // end namespace
