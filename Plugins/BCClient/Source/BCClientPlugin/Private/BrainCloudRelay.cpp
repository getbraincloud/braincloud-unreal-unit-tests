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

bool BrainCloudRelay::send(TArray<uint8> in_data, uint8 in_target, bool in_reliable/* = true*/, bool in_ordered/* = true*/, int in_channel/* = 0*/)
{
    return _relayComms->send(in_data, in_target, in_reliable, in_ordered, in_channel);
}

void BrainCloudRelay::setPingInterval(float in_interval)
{
    _relayComms->setPingInterval(in_interval);
}


