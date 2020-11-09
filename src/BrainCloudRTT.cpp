#include "braincloud/BrainCloudRTT.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "json/json.h"

namespace BrainCloud
{
	BrainCloudRTT::BrainCloudRTT(RTTComms* in_comms, BrainCloudClient* in_client)
		: m_client(in_client), m_commsLayer(in_comms)
	{
	}

	void BrainCloudRTT::requestClientConnection(IServerCallback* in_callback)
	{
		Json::Value nullMsg = Json::nullValue;
		ServerCall* sc = new ServerCall(ServiceName::RTTRegistration, ServiceOperation::RequestClientConnection, nullMsg, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	// RTT stuff
    void BrainCloudRTT::enableRTT(IRTTConnectCallback* in_callback, bool in_useWebSocket)
    {
        m_commsLayer->enableRTT(in_callback, in_useWebSocket);
    }

    void BrainCloudRTT::disableRTT()
    {
        m_commsLayer->disableRTT();
    }

    bool BrainCloudRTT::getRTTEnabled()
    {
        return m_commsLayer->isRTTEnabled();
    }

    BrainCloudRTT::RTTConnectionStatus BrainCloudRTT::getConnectionStatus()
    {
        return m_commsLayer->getConnectionStatus();
    }

    void BrainCloudRTT::registerRTTEventCallback(IRTTCallback* in_callback)
    {
        m_commsLayer->registerRTTCallback(ServiceName::Event, in_callback);
    }

    void BrainCloudRTT::deregisterRTTEventCallback()
    {
        m_commsLayer->deregisterRTTCallback(ServiceName::Event);
    }

    void BrainCloudRTT::registerRTTChatCallback(IRTTCallback* in_callback)
    {
        m_commsLayer->registerRTTCallback(ServiceName::Chat, in_callback);
    }

    void BrainCloudRTT::deregisterRTTChatCallback()
    {
        m_commsLayer->deregisterRTTCallback(ServiceName::Chat);
    }

    void BrainCloudRTT::registerRTTMessagingCallback(IRTTCallback* in_callback)
    {
        m_commsLayer->registerRTTCallback(ServiceName::Messaging, in_callback);
    }

    void BrainCloudRTT::deregisterRTTMessagingCallback()
    {
        m_commsLayer->deregisterRTTCallback(ServiceName::Messaging);
    }

    void BrainCloudRTT::registerRTTLobbyCallback(IRTTCallback* in_callback)
    {
        m_commsLayer->registerRTTCallback(ServiceName::Lobby, in_callback);
    }

    void BrainCloudRTT::deregisterRTTLobbyCallback()
    {
        m_commsLayer->deregisterRTTCallback(ServiceName::Lobby);
    }

    void BrainCloudRTT::registerRTTPresenceCallback(IRTTCallback* in_callback)
    {
        m_commsLayer->registerRTTCallback(ServiceName::Presence, in_callback);
    }

    void BrainCloudRTT::deregisterRTTPresenceCallback()
    {
        m_commsLayer->deregisterRTTCallback(ServiceName::Presence);
    }

    void BrainCloudRTT::registerRTTBlockchainRefresh(IRTTCallback* in_callback)
    {
        m_commsLayer->registerRTTCallback(ServiceName::UserItems, in_callback);
    }
    
    void BrainCloudRTT::deregisterRTTBlockchainRefresh()
    {
        m_commsLayer->deregisterRTTCallback(ServiceName::UserItems);
    }

    void BrainCloudRTT::deregisterAllRTTCallbacks()
    {
        m_commsLayer->deregisterAllRTTCallbacks();
    }

    const std::string& BrainCloudRTT::getRTTConnectionId() const
    {
        return m_commsLayer->getConnectionId();
    }

}
