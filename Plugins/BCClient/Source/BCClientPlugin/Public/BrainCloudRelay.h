// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once
enum class BCRelayConnectionType : uint8;
class BrainCloudClient;
class BrainCloudRelayComms;
class UBCBlueprintRelayCallProxyBase;
class IRelayCallback;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudRelay
{
public:
  BrainCloudRelay(BrainCloudRelayComms *in_comms);
	int64 ping();
	uint8 netId();

  void connect(BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *callback);
	void disconnect();
	void registerDataCallback(IRelayCallback *callback);
	void registerDataCallback(UBCBlueprintRelayCallProxyBase *callback);
	void deregisterDataCallback();

	bool send(TArray<uint8> in_data, uint8 in_target, bool in_reliable = true, bool in_ordered = true, int in_channel = 0);
	void setPingInterval(float in_interval);

private:
  BrainCloudRelayComms *_relayComms = nullptr;
};
