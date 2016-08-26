// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCPushNotificationProxy.generated.h"

enum class EBCPlatform : uint8;

UCLASS(MinimalAPI)
class UBCPushNotificationProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCPushNotificationProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Deregisters all device tokens currently registered to the player.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Push Notification")
        static UBCPushNotificationProxy* DeregisterAllPushNotificationDeviceTokens();

    /**
    * Deregisters the given device token from the server to disable this device
    * from receiving push notifications.
    *
    * Param - platform The device platform
    * Param - deviceToken The platform-dependant device token needed for push notifications.
    *   On IOS, this is obtained using the application:didRegisterForRemoteNotificationsWithDeviceToken callback
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Push Notification")
        static UBCPushNotificationProxy* DeregisterPushNotificationDeviceToken(EBCPlatform platform, const FString& deviceToken);

    /**
    * Registers the given device token with the server to enable this device
    * to receive push notifications.
    *
    * Param - platform The device platform
    * Param - deviceToken The platform-dependant device token needed for push notifications.
    *   On IOS, this is obtained using the application:didRegisterForRemoteNotificationsWithDeviceToken callback
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Push Notification")
        static UBCPushNotificationProxy* RegisterPushNotificationDeviceToken(EBCPlatform platform, const FString& deviceToken);

    /**
    * Sends a simple push notification based on the passed in message.
    * NOTE: It is possible to send a push notification to oneself.
    *
    * Param - toPlayerId The braincloud playerId of the user to receive the notification
    * Param - message Text of the push notification
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Push Notification")
        static UBCPushNotificationProxy* SendSimplePushNotification(const FString& toPlayerId, const FString& message);

    /**
    * Sends a notification to a user based on a brainCloud portal configured notification template.
    * NOTE: It is possible to send a push notification to oneself.
    *
    * Param - toPlayerId The braincloud playerId of the user to receive the notification
    * Param - notificationTemplateId Id of the notification template
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Push Notification")
        static UBCPushNotificationProxy* SendRichPushNotification(const FString& toPlayerId, int32 notificationTemplateId);

    /**
    * Sends a notification to a user based on a brainCloud portal configured notification template.
    * Includes JSON defining the substitution params to use with the template.
    * See the Portal documentation for more info.
    * NOTE: It is possible to send a push notification to oneself.
    *
    * Param - toPlayerId The braincloud playerId of the user to receive the notification
    * Param - notificationTemplateId Id of the notification template
    * Param - substitutionJson JSON defining the substitution params to use with the template
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Push Notification")
        static UBCPushNotificationProxy* SendRichPushNotificationWithParams(const FString& toPlayerId, int32 notificationTemplateId, const FString& substitutionJson);

    /**
    * Sends a notification to a "group" of user based on a brainCloud portal configured notification template.
    * Includes JSON defining the substitution params to use with the template.
    * See the Portal documentation for more info.
    *
    * Param - groupId Target group
    * Param - notificationTemplateId Template to use
    * Param - substitutionsJson Map of substitution positions to strings
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Push Notification")
        static UBCPushNotificationProxy* SendTemplatedPushNotificationToGroup(const FString& groupId, int32 notificationTemplateId, const FString& substitutionJson);

    /**
    * Sends a notification to a "group" of user consisting of alert content and custom data.
    * See the Portal documentation for more info.
    *
    * Param - groupId Target group
    * Param - alertContentJson Body and title of alert
    * Param - customDataJson Optional custom data
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Push Notification")
        static UBCPushNotificationProxy* SendNormalizedPushNotificationToGroup(const FString& toPlayerId, const FString& alertContentJson, const FString& customDataJson);

	/**
	* Sends a notification to a user consisting of alert content and custom data.
	*
	* Param - toPlayerId The playerId of the user to receive the notification
	* Param - alertContent Body and title of alert
	* Param - customData Optional custom data
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Push Notification")
		static UBCPushNotificationProxy* SendNormalizedPushNotification(const FString& toPlayerId, const FString& alertContentJson, const FString& customDataJson);

	/**
	* Sends a notification to a user consisting of alert content and custom data.
	*
	* Param - profileIds Collection of profile IDs to send the notification to
	* Param - alertContent Body and title of alert
	* Param - customData Optional custom data
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Push Notification")
		static UBCPushNotificationProxy* SendNormalizedPushNotificationBatch(const TArray<FString> profileIds, const FString& alertContentJson, const FString& customDataJson);

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
