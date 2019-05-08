#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudRelay.h"
#include "BrainCloudRelayComms.h"

BrainCloudRelay::BrainCloudRelay(BrainCloudRelayComms *in_comms) 
: _relayComms(in_comms)
{
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

bool BrainCloudRelay::send(const FString &in_message)
{
    return _relayComms->send(in_message);
}

bool BrainCloudRelay::send(TArray<uint8> in_message)
{
    return _relayComms->send(in_message);
}

void BrainCloudRelay::ping()
{
    _relayComms->ping();
}
