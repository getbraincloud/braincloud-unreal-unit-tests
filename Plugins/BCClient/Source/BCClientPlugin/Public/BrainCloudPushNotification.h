// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;
enum class EBCPlatform : uint8;

class BCCLIENTPLUGIN_API BrainCloudPushNotification
{
  public:
	BrainCloudPushNotification(BrainCloudClient *client);

	/**
    * Deregisters all device tokens currently registered to the user.
    *
    * @param callback The method to be invoked when the server response is received
    */
	void deregisterAllPushNotificationDeviceTokens(IServerCallback *callback = nullptr);

	/**
    * Deregisters the given device token from the server to disable this device
    * from receiving push notifications.
    *
    * @param platform The device platform being deregistered.
    * @param token The platform-dependant device token needed for push notifications.
    * @param callback The method to be invoked when the server response is received
    */
	void deregisterPushNotificationDeviceToken(EBCPlatform platform, const FString &token, IServerCallback *callback = nullptr);

	/**
    * Registers the given device token with the server to enable this device
    * to receive push notifications.
    *
    * @param platform The device platform
    * @param deviceToken The platform-dependant device token needed for push notifications.
    *   On IOS, this is obtained using the application:didRegisterForRemoteNotificationsWithDeviceToken callback
    * @param callback The method to be invoked when the server response is received
    */
	void registerPushNotificationDeviceToken(EBCPlatform platform, const FString &deviceToken, IServerCallback *callback);

	/**
    * Registers the given device token with the server to enable this device
    * to receive push notifications.
    *
    * @param deviceType The type of device (see DEVICE_TYPE_* constants)
    * @param deviceToken The platform-dependant device token needed for push notifications.
    *   On IOS, this is obtained using the application:didRegisterForRemoteNotificationsWithDeviceToken callback
    * @param callback The method to be invoked when the server response is received
    */
	void registerPushNotificationDeviceToken(const FString &deviceType, const FString &deviceToken, IServerCallback *callback);

	/**
    * Sends a simple push notification based on the passed in message.
    * NOTE: It is possible to send a push notification to oneself.
    *
    * @param toProfileId The braincloud profileId of the user to receive the notification
    * @param message Text of the push notification
    * @param callback The method to be invoked when the server response is received
    */
	void sendSimplePushNotification(const FString &toProfileId, const FString &message, IServerCallback *callback);

	/**
    * Sends a notification to a user based on a brainCloud portal configured notification template.
    * NOTE: It is possible to send a push notification to oneself.
    *
    * @param toProfileId The braincloud profileId of the user to receive the notification
    * @param notificationTemplateId Id of the notification template
    * @param callback The method to be invoked when the server response is received
    */
	void sendRichPushNotification(const FString &toProfileId, int32 notificationTemplateId, IServerCallback *callback);

	/**
    * Sends a notification to a user based on a brainCloud portal configured notification template.
    * Includes JSON defining the substitution params to use with the template.
    * See the Portal documentation for more info.
    * NOTE: It is possible to send a push notification to oneself.
    *
    * @param toProfileId The braincloud profileId of the user to receive the notification
    * @param notificationTemplateId Id of the notification template
    * @param substitutionJson JSON defining the substitution params to use with the template
    * @param callback The method to be invoked when the server response is received
    */
	void sendRichPushNotificationWithParams(const FString &toProfileId, int32 notificationTemplateId, const FString &substitutionJson, IServerCallback *callback);

	/**
    * Sends a notification to a "group" of user based on a brainCloud portal configured notification template.
    * Includes JSON defining the substitution params to use with the template.
    * See the Portal documentation for more info.
    *
    * @param groupId Target group
    * @param notificationTemplateId Template to use
    * @param substitutionsJson Map of substitution positions to strings
    * @param callback The method to be invoked when the server response is received
    */
	void sendTemplatedPushNotificationToGroup(const FString &groupId, int32 notificationTemplateId, const FString &substitutionsJson, IServerCallback *callback = nullptr);

	/**
    * Sends a notification to a "group" of user consisting of alert content and custom data.
    * See the Portal documentation for more info.
    *
    * @param groupId Target group
    * @param alertContentJson Body and title of alert
    * @param customDataJson Optional custom data
    * @param callback The method to be invoked when the server response is received
    */
	void sendNormalizedPushNotificationToGroup(const FString &groupId, const FString &alertContentJson, const FString &customDataJson, IServerCallback *callback = nullptr);

	/**
	* Schedules a normalized push notification to a user
	*
	* @param profileId The profileId of the user to receive the notification
	* @param fcmContent Valid Fcm data content
	* @param iosContent Valid ios data content
	* @param facebookContent Facebook template string
	* @param startTime Start time of sending the push notification
	* @param callback The method to be invoked when the server response is received
	*/
	void scheduleRawPushNotificationUTC(const FString &profileId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, int64 startTime, IServerCallback *callback = NULL);

	/**
	* Schedules a normalized push notification to a user
	*
	* @param profileId The profileId of the user to receive the notification
	* @param fcmContent Valid Fcm data content
	* @param iosContent Valid ios data content
	* @param facebookContent Facebook template string
	* @param minutesFromNow Minutes from now to send the push notification
	* @param callback The method to be invoked when the server response is received
	*/
	void scheduleRawPushNotificationMinutes(const FString &profileId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, int32 minutesFromNow, IServerCallback *callback = NULL);

	/**
	* Sends a raw push notification to a target user.
	*
	* @param toProfileId The profileId of the user to receive the notification
	* @param fcmContent Valid Fcm data content
	* @param iosContent Valid ios data content
	* @param facebookContent Facebook template string
	* @param callback The method to be invoked when the server response is received
	*/
	void sendRawPushNotification(const FString &profileId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, IServerCallback *callback = NULL);

	/**
	* Sends a raw push notification to a target list of users.
	*
	* @param profileIds Collection of profile IDs to send the notification to
	* @param fcmContent Valid Fcm data content
	* @param iosContent Valid ios data content
	* @param facebookContent Facebook template string
	* @param callback The method to be invoked when the server response is received
	*/
	void sendRawPushNotificationBatch(const TArray<FString> profileIds, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, IServerCallback *callback = NULL);

	/**
	* Sends a raw push notification to a target group.
	*
	* @param groupId Target group
	* @param fcmContent Valid Fcm data content
	* @param iosContent Valid ios data content
	* @param facebookContent Facebook template stringn
	* @param callback The method to be invoked when the server response is received
	*/
	void sendRawPushNotificationToGroup(const FString &groupId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, IServerCallback *callback = NULL);

	/**
	* Schedules a normalized push notification to a user
	*
	* @param profileId The profileId of the user to receive the notification
	* @param alertContentJson Body and title of alert
	* @param customDataJson Optional custom data
	* @param startTime Start time of sending the push notification
	* @param callback The method to be invoked when the server response is received
	*/
	void scheduleNormalizedPushNotificationUTC(const FString &profileId, const FString &alertContentJson, const FString &customDataJson, const int64 startTime, IServerCallback *callback);

	/**
	* Schedules a normalized push notification to a user
	*
	* @param profileId The profileId of the user to receive the notification
	* @param alertContentJson Body and title of alert
	* @param customDataJson Optional custom data
	* @param minutesFromNow Minutes from now to send the push notification
	* @param callback The method to be invoked when the server response is received
	*/
	void scheduleNormalizedPushNotificationMinutes(const FString &profileId, const FString &alertContentJson, const FString &customDataJson, const int32 minutesFromNow, IServerCallback *callback);

	/**
	* Schedules a rich push notification to a user
	*
	* @param profileId The profileId of the user to receive the notification
	* @param notificationTemplateId Body and title of alert
	* @param substitutionJson Map of substitution positions to strings
	* @param startTime Start time of sending the push notification
	* @param callback The method to be invoked when the server response is received
	*/
	void scheduleRichPushNotificationUTC(const FString &profileId, const int32 notificationTemplateId, const FString &substitutionJson, const int64 startTime, IServerCallback *callback);

	/**
	* Schedules a rich push notification to a user
	*
	* @param profileId The profileId of the user to receive the notification
	* @param notificationTemplateId Body and title of alert
	* @param substitutionJson Map of substitution positions to strings
	* @param minutesFromNow Minutes from now to send the push notification
	* @param callback The method to be invoked when the server response is received
	*/
	void scheduleRichPushNotificationMinutes(const FString &profileId, const int32 notificationTemplateId, const FString &substitutionJson, const int32 minutesFromNow, IServerCallback *callback);

	/**
	* Sends a notification to a user consisting of alert content and custom data.
	*
	* @param toProfileId The profileId of the user to receive the notification
	* @param alertContent Body and title of alert
	* @param customData Optional custom data
	* @param callback The method to be invoked when the server response is received
	*/
	void sendNormalizedPushNotification(const FString &toProfileId, const FString &alertContentJson, const FString &customDataJson, IServerCallback *callback = nullptr);

	/**
	* Sends a notification to multiple users consisting of alert content and custom data.
	*
	* @param profileIds Collection of profile IDs to send the notification to
	* @param alertContent Body and title of alert
	* @param customData Optional custom data
	* @param callback The method to be invoked when the server response is received
	*/
	void sendNormalizedPushNotificationBatch(const TArray<FString> profileIds, const FString &alertContentJson, const FString &customDataJson, IServerCallback *callback = nullptr);

  private:
	BrainCloudClient *_client = nullptr;
};
