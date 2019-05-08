// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once
#include "IServerCallback.h"

enum class BCRelayConnectionType : uint8;
class BrainCloudRelayComms;

class BCCLIENTPLUGIN_API BrainCloudRelay
{
public:
  BrainCloudRelay(BrainCloudRelayComms *in_comms);

  void connect(BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *callback);
	void disconnect();
	void registerDataCallback(IRelayCallback *callback);
	void registerDataCallback(UBCBlueprintRelayCallProxyBase *callback);
	void deregisterDataCallback();

	bool send(const FString &in_message);
	bool send(TArray<uint8> in_message);
	void ping();

private:
  BrainCloudRelayComms *_relayComms = nullptr;
};
