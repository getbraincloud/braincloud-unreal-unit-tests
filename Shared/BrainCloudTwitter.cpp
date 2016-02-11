#include "BrainCloudTwitter.h"
#include "BrainCloudClient.h"

namespace BrainCloud {

	void BrainCloudTwitter::authorizeTwitter( IServerCallback * in_callback )
	{
		Json::Value nullMsg = Json::nullValue;
		ServerCall * sc = new ServerCall( ServiceName::Twitter, ServiceOperation::Authenticate, nullMsg, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudTwitter::verifyTwitter( const char * in_token, const char * in_verifier, IServerCallback * in_callback )
	{
		Json::Value message = Json::nullValue;
		message[OperationParam::TwitterServiceVerifyToken.getValue()] = in_token;
		message[OperationParam::TwitterServiceVerifyVerifier.getValue()] = in_verifier;
		
		ServerCall * sc = new ServerCall( ServiceName::Twitter, ServiceOperation::Verify, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudTwitter::tweet( const char * in_token, const char * in_secret, const char * in_tweet, const char * in_picture, IServerCallback * in_callback )
	{
		Json::Value message = Json::nullValue;
		message[OperationParam::TwitterServiceTweetToken.getValue()] = in_token;
		message[OperationParam::TwitterServiceTweetSecret.getValue()] = in_secret;
		message[OperationParam::TwitterServiceTweetTweet.getValue()] = in_tweet;
		if (in_picture != NULL) {
			message[OperationParam::TwitterServiceTweetPic.getValue()] = in_picture;
		}
		
		ServerCall * sc = new ServerCall( ServiceName::Twitter, ServiceOperation::Tweet, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
}