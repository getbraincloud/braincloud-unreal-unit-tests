#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "BrainCloudRelay.h"
#include "BrainCloudRelayComms.h"

BrainCloudRelay::BrainCloudRelay(BrainCloudClient *in_client, BrainCloudRelayComms *in_comms) 
	: _client(in_client)
	, _relayComms(in_comms)
{
}

int64 BrainCloudRelay::ping()
{
    return _relayComms->ping();
}

uint8 BrainCloudRelay::netId()
{
    return _relayComms->netId();
}

void BrainCloudRelay::connect(BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *callback)
{
    _relayComms->connect(in_connectionType, in_connectOptionsJson, callback);
}

void BrainCloudRelay::disconnect()
{
    _relayComms->disconnect();
}

bool BrainCloudRelay::isConnected()
{
    return _relayComms->isConnected();
}

void BrainCloudRelay::registerDataCallback(IRelayCallback *callback)
{
    _relayComms->registerDataCallback(callback);
}

void BrainCloudRelay::registerDataCallback(UBCBlueprintRelayCallProxyBase *callback)
{
    _relayComms->registerDataCallback(callback);
}

void BrainCloudRelay::deregisterDataCallback()
{
    _relayComms->deregisterDataCallback();
}

void BrainCloudRelay::send(const TArray<uint8> &in_data, const uint64 in_target, bool in_reliable, bool in_ordered, int in_channel)
{
	if (in_target == BrainCloudRelayComms::TO_ALL_PLAYERS)
	{
		sendToAll(in_data, in_reliable, in_ordered, in_channel);
	}
	else
	{
		uint64 playerMask = (uint64)1 << in_target;
    	_relayComms->sendRelay(in_data, playerMask, in_reliable, in_ordered, in_channel);
	}
}

void BrainCloudRelay::sendToPlayers(const TArray<uint8> &in_data, const uint64 in_playerMask, bool in_reliable, bool in_ordered, int in_channel)
{
    _relayComms->sendRelay(in_data, in_playerMask, in_reliable, in_ordered, in_channel);
}

void BrainCloudRelay::sendToAll(const TArray<uint8> &in_data, bool in_reliable, bool in_ordered, int in_channel)
{
	const auto& myProfileId = _client->getAuthenticationService()->getProfileId();
	auto myNetId = _relayComms->getNetIdForProfileId(myProfileId);

	uint64 myBit = (uint64)1 << (uint64)myNetId;
	uint64 myInvertedBits = ~myBit;
	uint64 playerMask = BrainCloudRelayComms::TO_ALL_PLAYERS & myInvertedBits;
    _relayComms->sendRelay(in_data, playerMask, in_reliable, in_ordered, in_channel);
}

const FString &BrainCloudRelay::getOwnerProfileId() const
{
	return _relayComms->getOwnerProfileId();
}

const FString &BrainCloudRelay::getProfileIdForNetId(int in_netId) const
{
	return _relayComms->getProfileIdForNetId(in_netId);
}

int BrainCloudRelay::getNetIdForProfileId(const FString &in_profileId) const
{
	return _relayComms->getNetIdForProfileId(in_profileId);
}

void BrainCloudRelay::setPingInterval(float in_interval)
{
    _relayComms->setPingInterval(in_interval);
}

FString BrainCloudRelay::BCBytesToString(const uint8* in, int32 count)
{
	FString result2;
	result2.Empty(count);
	while (count)
	{
        result2 += ANSICHAR(*in);
		++in;
		--count;
	}
	
	return result2;
}

int32 BrainCloudRelay::BCStringToBytes( const FString& in_string, uint8* out_bytes, int32 in_maxBufferSize )
{
	int32 numBytes = 0;
	const TCHAR* charPos = *in_string;

	while( *charPos && numBytes < in_maxBufferSize)
	{
		out_bytes[ numBytes ] = (uint8)(*charPos);
		charPos++;
		++numBytes;
	}
	return numBytes;
}
