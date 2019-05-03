// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once
#include "IServerCallback.h"

enum class eBCRSConnectionType : uint8;
class BrainCloudRSComms;

class BCCLIENTPLUGIN_API BrainCloudRoomServer
{
public:
  BrainCloudRoomServer(BrainCloudRSComms *in_comms);

  void connect(eBCRSConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *callback);
	void disconnect();
	void registerDataCallback(IRSCallback *callback);
	void registerDataCallback(UBCBlueprintRSCallProxyBase *callback);
	void deregisterDataCallback();

	bool send(const FString &in_message);
	bool send(TArray<uint8> in_message);
	void ping();

private:
  BrainCloudRSComms *_rsComms = nullptr;
};
