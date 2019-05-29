// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCRTTCommsProxy.generated.h"

class BrainCloudRTTComms;

UCLASS(MinimalAPI)
class UBCRTTCommsProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UBCRTTCommsProxy(const FObjectInitializer &ObjectInitializer);
	virtual void BeginDestroy() override;

	void SetRTTComms(BrainCloudRTTComms *in_comms);

	// expose web socket functions
	UFUNCTION()
	void WebSocket_OnClose();
	UFUNCTION()
	void Websocket_OnOpen();
	UFUNCTION()
	void WebSocket_OnMessage(TArray<uint8> in_data);
	UFUNCTION()
	void WebSocket_OnError(const FString &in_error);

private:
	BrainCloudRTTComms *m_commsPtr;
};
