#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudRoomServer.h"
#include "BrainCloudRSComms.h"

BrainCloudRoomServer::BrainCloudRoomServer(BrainCloudRSComms *in_comms) 
: _rsComms(in_comms)
{
}

void BrainCloudRoomServer::connect(eBCRSConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *callback)
{
    _rsComms->connect(in_connectionType, in_connectOptionsJson, callback);
}

void BrainCloudRoomServer::disconnect()
{
    _rsComms->disconnect();
}

void BrainCloudRoomServer::registerDataCallback(IRSCallback *callback)
{
    _rsComms->registerDataCallback(callback);
}

void BrainCloudRoomServer::registerDataCallback(UBCBlueprintRSCallProxyBase *callback)
{
    _rsComms->registerDataCallback(callback);
}

void BrainCloudRoomServer::deregisterDataCallback()
{
    _rsComms->deregisterDataCallback();
}

bool BrainCloudRoomServer::send(const FString &in_message)
{
    return _rsComms->send(in_message);
}

bool BrainCloudRoomServer::send(TArray<uint8> in_message)
{
    return _rsComms->send(in_message);
}

void BrainCloudRoomServer::ping()
{
    _rsComms->ping();
}
