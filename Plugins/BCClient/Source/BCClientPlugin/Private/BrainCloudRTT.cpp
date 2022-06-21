// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudRTT.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "BrainCloudRTTComms.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "BCRTTProxy.h"

BrainCloudRTT::BrainCloudRTT(BrainCloudRTTComms *comms, BrainCloudClient *client) : _client(client), _commsLayer(comms){};

void BrainCloudRTT::requestClientConnection(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::RTTRegistration, ServiceOperation::RequestClientConnection, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudRTT::enableRTT(BCRTTConnectionType in_type, IServerCallback *in_callback)
{
	_commsLayer->enableRTT(in_type, in_callback);
}

void BrainCloudRTT::enableRTT(BCRTTConnectionType in_type, UBCRTTProxy *in_callback)
{
	_commsLayer->enableRTT(in_type, in_callback);
}

void BrainCloudRTT::disableRTT()
{
	_commsLayer->disableRTT();
}

bool BrainCloudRTT::isRTTEnabled()
{
	return _commsLayer->isRTTEnabled();
}

void BrainCloudRTT::setRTTHeartBeatSeconds(int32 in_value)
{
	_commsLayer->setRTTHeartBeatSeconds(in_value);
}

void BrainCloudRTT::deregisterAllRTTCallbacks()
{
	_commsLayer->deregisterAllRTTCallbacks();
}

void BrainCloudRTT::registerRTTEventCallback(UBCBlueprintRTTCallProxyBase *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::Event, in_callback);
}

void BrainCloudRTT::registerRTTEventCallback(IRTTCallback *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::Event, in_callback);
}

void BrainCloudRTT::deregisterRTTEventCallback()
{
	_commsLayer->deregisterRTTCallback(ServiceName::Event);
}

void BrainCloudRTT::registerRTTChatCallback(UBCBlueprintRTTCallProxyBase *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::Chat, in_callback);
}

void BrainCloudRTT::registerRTTChatCallback(IRTTCallback *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::Chat, in_callback);
}

void BrainCloudRTT::deregisterRTTChatCallback()
{
	_commsLayer->deregisterRTTCallback(ServiceName::Chat);
}

void BrainCloudRTT::registerRTTMessagingCallback(UBCBlueprintRTTCallProxyBase *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::Messaging, in_callback);
}

void BrainCloudRTT::registerRTTMessagingCallback(IRTTCallback *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::Messaging, in_callback);
}

void BrainCloudRTT::deregisterRTTMessagingCallback()
{
	_commsLayer->deregisterRTTCallback(ServiceName::Messaging);
}

void BrainCloudRTT::registerRTTPresenceCallback(UBCBlueprintRTTCallProxyBase *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::Presence, in_callback);
}

void BrainCloudRTT::registerRTTPresenceCallback(IRTTCallback *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::Presence, in_callback);
}

void BrainCloudRTT::deregisterRTTPresenceCallback()
{
	_commsLayer->deregisterRTTCallback(ServiceName::Presence);
}

void BrainCloudRTT::registerRTTLobbyCallback(UBCBlueprintRTTCallProxyBase *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::Lobby, in_callback);
}

void BrainCloudRTT::registerRTTLobbyCallback(IRTTCallback *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::Lobby, in_callback);
}

void BrainCloudRTT::deregisterRTTLobbyCallback()
{
	_commsLayer->deregisterRTTCallback(ServiceName::Lobby);
}

void BrainCloudRTT::registerRTTBlockchainRefresh(IRTTCallback *in_callback)
{
	_commsLayer->registerRTTCallback(ServiceName::UserItems, in_callback);
}

void BrainCloudRTT::deregisterRTTBlockchainRefresh()
{
	_commsLayer->deregisterRTTCallback(ServiceName::UserItems);
}

const FString &BrainCloudRTT::getRTTConnectionId() const
{
	return _commsLayer->getConnectionId();
}

BCRTTConnectionStatus BrainCloudRTT::getConnectionStatus()
{
	return _commsLayer->getConnectionStatus();
}
