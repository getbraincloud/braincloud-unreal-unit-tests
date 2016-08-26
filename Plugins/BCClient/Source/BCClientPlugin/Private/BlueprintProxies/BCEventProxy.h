// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCEventProxy.generated.h"

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
    * in the "ReadPlayerState" call (in the BrainCloudPlayer module).
    *
    * Service Name - Event
    * Service Operation - Send
    *
    * Param - toPlayerId The id of the player who is being sent the event
    * Param - eventType The user-defined type of the event.
    * Param - jsonEventData The user-defined data for this event encoded in JSON.
    * Param - recordLocally If true, a copy of this event will be saved in the
    * user's sent events mailbox.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Event")
        static UBCEventProxy* SendEvent(FString toPlayerId, FString eventType, FString jsonEventData, bool recordLocally);

    /**
    * Updates an event in the player's incoming event mailbox.
    *
    * Service Name - Event
    * Service Operation - UpdateEventData
    *
    * Param - fromPlayerId The id of the player who sent the event
    * Param - eventId The event id
    * Param - jsonEventData The user-defined data for this event encoded in JSON.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Event")
        static UBCEventProxy* UpdateIncomingEventData(FString fromPlayerId, int32 eventId, FString jsonEventData);

    /**
    * Delete an event out of the player's incoming mailbox.
    *
    * Service Name - Event
    * Service Operation - DeleteIncoming
    *
    * Param - fromPlayerId The id of the player who sent the event
    * Param - eventId The event id
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Event")
        static UBCEventProxy* DeleteIncomingEvent(FString fromPlayerId, int32 eventId);

    /**
    * Delete an event from the player's sent mailbox.
    *
    * Note that only events sent with the "recordLocally" flag
    * set to true will be added to a player's sent mailbox.
    *
    * Service Name - Event
    * Service Operation - DeleteSent
    *
    * Param - toPlayerId The id of the player who is being sent the even
    * Param - eventId The event id
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Event")
        static UBCEventProxy* DeleteSentEvent(FString toPlayerId, int32 eventId);

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
        static UBCEventProxy* GetEvents(bool includeIncomingEvents, bool includeSentEvents);

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
