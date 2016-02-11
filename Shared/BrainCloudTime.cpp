#include "BrainCloudTime.h"
#include "BrainCloudClient.h"


namespace BrainCloud
{
	void BrainCloudTime::readServerTime( IServerCallback * in_callback )
	{
		Json::Value nullMsg = Json::nullValue;
		ServerCall * sc = new ServerCall( ServiceName::ServerTime, ServiceOperation::Read, nullMsg, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
}