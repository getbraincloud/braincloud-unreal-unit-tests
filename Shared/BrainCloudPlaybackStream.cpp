#include "BrainCloudPlaybackStream.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"

namespace BrainCloud {

	void BrainCloudPlaybackStream::startStream(const char * in_targetPlayerId, bool in_includeSharedData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlaybackStreamServiceTargetPlayerId.getValue()] = in_targetPlayerId;
		message[OperationParam::PlaybackStreamServiceIncludeSharedData.getValue()] = in_includeSharedData;

		ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::StartStream, message, in_callback);
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudPlaybackStream::readStream(const char * in_playbackStreamId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlaybackStreamServicePlaybackStreamId.getValue()] = in_playbackStreamId;

		ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::ReadStream, message, in_callback);
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudPlaybackStream::endStream(const char * in_playbackStreamId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlaybackStreamServicePlaybackStreamId.getValue()] = in_playbackStreamId;

		ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::EndStream, message, in_callback);
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudPlaybackStream::deleteStream(const char * in_playbackStreamId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlaybackStreamServicePlaybackStreamId.getValue()] = in_playbackStreamId;

		ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::DeleteStream, message, in_callback);
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudPlaybackStream::addEvent(const char * in_playbackStreamId, const char * in_jsonEventData, const char * in_jsonSummary, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlaybackStreamServicePlaybackStreamId.getValue()] = in_playbackStreamId;
		message[OperationParam::PlaybackStreamServiceEventData.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonEventData);
		message[OperationParam::PlaybackStreamServiceSummary.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonSummary);

		ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::AddEvent, message, in_callback);
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudPlaybackStream::getStreamSummariesForInitiatingPlayer(const char * in_initiatingPlayerId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlaybackStreamServiceInitiatingPlayerId.getValue()] = in_initiatingPlayerId;

		ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::GetStreamSummariesForInitiatingPlayer, message, in_callback);
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudPlaybackStream::getStreamSummariesForTargetPlayer(const char * in_targetPlayerId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlaybackStreamServiceTargetPlayerId.getValue()] = in_targetPlayerId;

		ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::GetStreamSummariesForTargetPlayer, message, in_callback);
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

}
