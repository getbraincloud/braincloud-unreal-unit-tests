#include "BrainCloudSteam.h"
#include "BrainCloudClient.h"

namespace BrainCloud {
	
	void BrainCloudSteam::getUserInfo( IServerCallback * in_callback )
	{
		Json::Value data = Json::nullValue;
		
		ServerCall * sc = new ServerCall( ServiceName::Steam, ServiceOperation::Logout, data, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
}
