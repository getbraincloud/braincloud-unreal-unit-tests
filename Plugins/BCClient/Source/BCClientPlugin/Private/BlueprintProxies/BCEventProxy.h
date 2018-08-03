// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCEventProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCEventProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCEventProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Sends an event to the designated player id with the attached json data.
    * Any events that have been sent to a player will show up in their
    * incoming event mailbox. If the in_recordLocally flag is set to true,
    * a copy of this event (with the exact same event id) will be stored
    * in the sending player's "sent" event mailbox.
    *
    * Note that the list of sent and incoming events for a player is returned
    * in the "ReadUserState" call (in the BrainCloudPlayer module).
    *
    * Service Name - Event
    * Service Operation - Send
    *
    * Param - toPlayerId The id of the player who is being sent the event
    * Param - eventType The user-defined type of the event.
    * Param - jsonEventData The user-defined data for this event encoded in JSON.
    * user's sent events mailbox.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Event")
        static UBCEventProxy* SendEvent(ABrainCloudActor *brainCloud, const FString& toPlayerId, const FString& eventType, const FString& jsonEventData);

    /**
    * Updates an event in the player's incoming event mailbox.
    *
    * Service Name - Event
    * Service Operation - UpdateEventData
    *
    * Param - evId The event id
    * Param - jsonEventData The user-defined data for this event encoded in JSON.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Event")
        static UBCEventProxy* UpdateIncomingEventData(ABrainCloudActor *brainCloud, const FString& evId, const FString& jsonEventData);

    /**
    * Delete an event out of the player's incoming mailbox.
    *
    * Service Name - Event
    * Service Operation - DeleteIncoming
    *
    * Param - evId The event id
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Event")
        static UBCEventProxy* DeleteIncomingEvent(ABrainCloudActor *brainCloud, const FString& evId);

    /**
    * Get the events currently queued for the player.
    *
    * Service Name - Event
    * Service Operation - GetEvents
    *
    * Param - includeIncomingEvents Get events sent to the player
    * Param - includeSentEvents Get events sent from the player
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Event")
        static UBCEventProxy* GetEvents(ABrainCloudActor *brainCloud);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
