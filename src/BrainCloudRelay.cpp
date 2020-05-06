// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudRelay.h"
#include "braincloud/BrainCloudClient.h"

#include "braincloud/internal/RelayComms.h"

namespace BrainCloud
{
	BrainCloudRelay::BrainCloudRelay(RelayComms* in_commsLayer, BrainCloudClient* in_client)
		: m_commsLayer(in_commsLayer)
        , m_client(in_client)
	{
	}

    void BrainCloudRelay::connect(eRelayConnectionType in_connectionType, const std::string& host, int port, const std::string& passcode, const std::string& lobbyId, IRelayConnectCallback* in_callback)
    {
        m_commsLayer->connect(in_connectionType, host, port, passcode, lobbyId, in_callback);
    }

    void BrainCloudRelay::disconnect()
    {
        m_commsLayer->disconnect();
    }

    bool BrainCloudRelay::isConnected() const
    {
        return m_commsLayer->isConnected();
    }

    int BrainCloudRelay::getPing() const
    {
        return m_commsLayer->getPing();
    }

    void BrainCloudRelay::setPingInterval(int in_intervalMS)
    {
        m_commsLayer->setPingInterval(in_intervalMS);
    }

    const std::string& BrainCloudRelay::getOwnerProfileId() const
    {
        return m_commsLayer->getOwnerProfileId();
    }

    const std::string& BrainCloudRelay::getProfileIdForNetId(int in_netId) const
    {
        return m_commsLayer->getProfileIdForNetId(in_netId);
    }

    int BrainCloudRelay::getNetIdForProfileId(const std::string& in_profileId) const
    {
        return m_commsLayer->getNetIdForProfileId(in_profileId);
    }

    void BrainCloudRelay::registerRelayCallback(IRelayCallback* in_callback)
    {
        m_commsLayer->registerRelayCallback(in_callback);
    }

    void BrainCloudRelay::deregisterRelayCallback()
    {
        m_commsLayer->deregisterRelayCallback();
    }

    void BrainCloudRelay::registerSystemCallback(IRelaySystemCallback* in_callback)
    {
        m_commsLayer->registerSystemCallback(in_callback);
    }

    void BrainCloudRelay::deregisterSystemCallback()
    {
        m_commsLayer->deregisterSystemCallback();
    }

    void BrainCloudRelay::send(const uint8_t* in_data, int in_size, int in_toNetId, bool in_reliable, bool in_ordered, eRelayChannel in_channel)
    {
        m_commsLayer->send(in_data, in_size, in_toNetId, in_reliable, in_ordered, in_channel);
    }
};
