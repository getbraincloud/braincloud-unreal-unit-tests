#include "BrainCloudOneWayMatch.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"

namespace BrainCloud {

	void BrainCloudOneWayMatch::startMatch(const char * in_otherPlayerId, int32_t in_rangeDelta, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::OneWayMatchServicePlayerId.getValue()] = in_otherPlayerId;
		message[OperationParam::OneWayMatchServiceRangeDelta.getValue()] = in_rangeDelta;
		
		ServerCall * sc = new ServerCall( ServiceName::OneWayMatch, ServiceOperation::StartMatch, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudOneWayMatch::cancelMatch(const char * in_playbackStreamId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::OneWayMatchServicePlaybackStreamId.getValue()] = in_playbackStreamId;
		
		ServerCall * sc = new ServerCall( ServiceName::OneWayMatch, ServiceOperation::CancelMatch, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudOneWayMatch::completeMatch(const char * in_playbackStreamId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::OneWayMatchServicePlaybackStreamId.getValue()] = in_playbackStreamId;
		
		ServerCall * sc = new ServerCall( ServiceName::OneWayMatch, ServiceOperation::CompleteMatch, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
}