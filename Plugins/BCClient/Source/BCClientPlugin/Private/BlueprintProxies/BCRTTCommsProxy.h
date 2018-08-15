// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCRTTCommsProxy.generated.h"

class ABrainCloud;
class BrainCloudRTTComms;

UCLASS(MinimalAPI)
class UBCRTTCommsProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UBCRTTCommsProxy(const FObjectInitializer &ObjectInitializer);

	void SetRTTComms(BrainCloudRTTComms *in_comms);

	// expose web socket functions
	void WebSocket_OnClose();
	void Websocket_OnOpen();
	void WebSocket_OnMessage(const FString &in_data);
	void WebSocket_OnError(const FString &in_error);

private:
	BrainCloudRTTComms *m_commsPtr;
};
