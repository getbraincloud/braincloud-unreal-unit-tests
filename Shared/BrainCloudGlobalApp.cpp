#include "BrainCloudGlobalApp.h"
#include "BrainCloudClient.h"
#include "json/json.h"
#include "ServerCall.h"


namespace BrainCloud {
	
	void BrainCloudGlobalApp::readProperties(IServerCallback * in_callback)
	{
		
		Json::Value message = Json::nullValue;
        ServerCall * sc = new ServerCall( ServiceName::GlobalApp, ServiceOperation::ReadProperties, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
		
	}
}