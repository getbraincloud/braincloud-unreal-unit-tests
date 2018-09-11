#include "braincloud/BrainCloudRTTRegistration.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "json/json.h"

namespace BrainCloud
{
	BrainCloudRTTRegistration::BrainCloudRTTRegistration(BrainCloudClient* in_client)
		: m_client(in_client)
	{
	}

	void BrainCloudRTTRegistration::requestClientConnection(IServerCallback* in_callback)
	{
		Json::Value nullMsg = Json::nullValue;
		ServerCall* sc = new ServerCall(ServiceName::RTTRegistration, ServiceOperation::RequestClientConnection, nullMsg, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}
}
