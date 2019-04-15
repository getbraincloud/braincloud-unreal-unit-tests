// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCRSCommsProxy.generated.h"

class BrainCloudRSComms;

UCLASS(MinimalAPI)
class UBCRSCommsProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UBCRSCommsProxy(const FObjectInitializer &ObjectInitializer);
	virtual void BeginDestroy() override;

	void SetRSComms(BrainCloudRSComms *in_comms);

	// expose web socket functions
	UFUNCTION()
	void WebSocket_OnClose();
	UFUNCTION()
	void Websocket_OnOpen();
	UFUNCTION()
	void WebSocket_OnMessage(const FString &in_data);
	UFUNCTION()
	void WebSocket_OnError(const FString &in_error);

private:
	BrainCloudRSComms *m_commsPtr;
};
