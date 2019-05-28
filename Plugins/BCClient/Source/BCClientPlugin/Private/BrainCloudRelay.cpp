#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudRelayComms.h"
#include "BrainCloudRelay.h"

BrainCloudRelay::BrainCloudRelay(BrainCloudRelayComms *in_comms) 
: _relayComms(in_comms)
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

bool BrainCloudRelay::send(const TArray<uint8> &in_data, const uint8 in_target, bool in_reliable/* = true*/, bool in_ordered/* = true*/, int in_channel/* = 0*/)
{
    return _relayComms->send(in_data, in_target, in_reliable, in_ordered, in_channel);
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
