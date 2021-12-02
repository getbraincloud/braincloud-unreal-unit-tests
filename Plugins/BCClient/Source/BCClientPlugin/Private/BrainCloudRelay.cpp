#include "BrainCloudRelay.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "BrainCloudRelayComms.h"

BrainCloudRelay::BrainCloudRelay(BrainCloudClient *in_client, BrainCloudRelayComms *in_comms)
	: _client(in_client)
	, _relayComms(in_comms)
{
}

void BrainCloudRelay::connect(BCRelayConnectionType in_connectionType, const FString &host, int port, const FString &passcode, const FString &lobbyId, IRelayConnectCallback *in_callback)
{
    _relayComms->connect(in_connectionType, host, port, passcode, lobbyId, in_callback);
}

void BrainCloudRelay::disconnect()
{
    _relayComms->disconnect();
}

bool BrainCloudRelay::isConnected() const
{
    return _relayComms->isConnected();
}

int BrainCloudRelay::getPing() const
{
    return _relayComms->getPing();
}

const FString &BrainCloudRelay::getOwnerProfileId() const
{
	return _relayComms->getOwnerProfileId();
}

const FString &BrainCloudRelay::getOwnerCxId() const
{
	return _relayComms->getOwnerCxId();
}

const FString &BrainCloudRelay::getProfileIdForNetId(int in_netId) const
{
	return _relayComms->getProfileIdForNetId(in_netId);
}

int BrainCloudRelay::getNetIdForProfileId(const FString &in_profileId) const
{
	return _relayComms->getNetIdForProfileId(in_profileId);
}

const FString &BrainCloudRelay::getCxIdForNetId(int in_netId) const
{
	return _relayComms->getCxIdForNetId(in_netId);
}

int BrainCloudRelay::getNetIdForCxId(const FString &in_cxId) const
{
	return _relayComms->getNetIdForCxId(in_cxId);
}

void BrainCloudRelay::registerRelayCallback(IRelayCallback *callback)
{
    _relayComms->registerRelayCallback(callback);
}

void BrainCloudRelay::registerRelayCallback(UBCBlueprintRelayCallProxyBase *callback)
{
    _relayComms->registerRelayCallback(callback);
}

void BrainCloudRelay::deregisterRelayCallback()
{
    _relayComms->deregisterRelayCallback();
}

void BrainCloudRelay::registerSystemCallback(IRelaySystemCallback *callback)
{
    _relayComms->registerSystemCallback(callback);
}

void BrainCloudRelay::registerSystemCallback(UBCBlueprintRelaySystemCallProxyBase *callback)
{
    _relayComms->registerSystemCallback(callback);
}

void BrainCloudRelay::deregisterSystemCallback()
{
    _relayComms->deregisterSystemCallback();
}

void BrainCloudRelay::send(const TArray<uint8> &in_data, uint64 toNetId, bool in_reliable, bool in_ordered, BCRelayChannel in_channel)
{
	if (toNetId == BrainCloudRelay::TO_ALL_PLAYERS)
	{
		sendToAll(in_data, in_reliable, in_ordered, in_channel);
	}
	else
	{
		uint64 playerMask = (uint64)1 << toNetId;
    	_relayComms->send(in_data, playerMask, in_reliable, in_ordered, in_channel);
	}
}

void BrainCloudRelay::sendToPlayers(const TArray<uint8> &in_data, uint64 in_playerMask, bool in_reliable, bool in_ordered, BCRelayChannel in_channel)
{
    _relayComms->send(in_data, in_playerMask, in_reliable, in_ordered, in_channel);
}

void BrainCloudRelay::sendToAll(const TArray<uint8> &in_data, bool in_reliable, bool in_ordered, BCRelayChannel in_channel)
{
	const auto& myProfileId = _client->getAuthenticationService()->getProfileId();
	auto myNetId = _relayComms->getNetIdForProfileId(myProfileId);

	uint64 myBit = (uint64)1 << (uint64)myNetId;
	uint64 myInvertedBits = ~myBit;
	uint64 playerMask = BrainCloudRelay::TO_ALL_PLAYERS & myInvertedBits;
    _relayComms->send(in_data, playerMask, in_reliable, in_ordered, in_channel);
}
