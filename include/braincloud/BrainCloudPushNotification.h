// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include <vector>
#include "braincloud/BrainCloudTypes.h"

#include "braincloud/Platform.h"

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudPushNotification
    {
    public:
        BrainCloudPushNotification(BrainCloudClient* in_client);

        /**
         * Deregisters all device tokens currently registered to the user.
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void deregisterAllPushNotificationDeviceTokens(IServerCallback * in_callback = NULL);

        /**
         * Deregisters the given device token from the server to disable this device
         * from receiving push notifications.
         *
         * @param in_device The device platform being deregistered.
         * @param in_token The platform-dependent device token needed for push notifications.
         * @param in_callback The method to be invoked when the server response is received
         */
        void deregisterPushNotificationDeviceToken(const Platform & in_platform, const char * in_token, IServerCallback * in_callback = NULL);

        /**
         * Registers the given device token with the server to enable this device
         * to receive push notifications.
         *
         * @param in_platform The device platform
         * @param in_deviceToken The platform-dependent device token needed for push notifications.
         *  On IOS, this is obtained using the application:didRegisterForRemoteNotificationsWithDeviceToken callback
         * @param in_callback The method to be invoked when the server response is received
         */
        void registerPushNotificationDeviceToken(const Platform & in_platform, const char * in_deviceToken, IServerCallback * in_callback = NULL);
		
        /**
         * Sends a simple push notification based on the passed in message.
         * NOTE: It is possible to send a push notification to oneself.
         *
         * @param in_toProfileId The braincloud profileId of the user to receive the notification
         * @param in_message Text of the push notification
         * @param in_callback The method to be invoked when the server response is received
         */
        void sendSimplePushNotification(const char * in_toProfileId, const char * in_message, IServerCallback * in_callback = NULL);

        /**
         * Sends a notification to a user based on a brainCloud portal configured notification template.
         * NOTE: It is possible to send a push notification to oneself.
         *
         * @param in_toProfileId The braincloud profileId of the user to receive the notification
         * @param in_notificationTemplateId Id of the notification template
         * @param in_callback The method to be invoked when the server response is received
         */
        void sendRichPushNotification(const char * in_toProfileId, int32_t in_notificationTemplateId, IServerCallback * in_callback = NULL);

        /**
         * Sends a notification to a user based on a brainCloud portal configured notification template.
         * Includes JSON defining the substitution params to use with the template.
         * See the Portal documentation for more info.
         * NOTE: It is possible to send a push notification to oneself.
         *
         * @param in_toProfileId The braincloud profileId of the user to receive the notification
         * @param in_notificationTemplateId Id of the notification template
         * @param in_substitutionJson JSON defining the substitution params to use with the template
         * @param in_callback The method to be invoked when the server response is received
         */
        void sendRichPushNotificationWithParams(const char * in_toProfileId, int32_t in_notificationTemplateId, const char * in_substitutionJson, IServerCallback * in_callback = NULL);

        /**
        * Sends a notification to a "group" of user based on a brainCloud portal configured notification template.
        * Includes JSON defining the substitution params to use with the template.
        * See the Portal documentation for more info.
        *
        * @param in_groupId Target group
        * @param in_notificationTemplateId Template to use
        * @param in_substitutionsJson Map of substitution positions to strings
        * @param in_callback The method to be invoked when the server response is received
        */
        void sendTemplatedPushNotificationToGroup(const char * in_groupId, int32_t in_notificationTemplateId, std::string in_substitutionsJson, IServerCallback * in_callback = NULL);

        /**
        * Sends a notification to a "group" of user consisting of alert content and custom data.
        * See the Portal documentation for more info.
        *
        * @param in_groupId Target group
        * @param in_alertContentJson Body and title of alert
        * @param in_customDataJson Optional custom data
        * @param in_callback The method to be invoked when the server response is received
        */
        void sendNormalizedPushNotificationToGroup(const char * in_groupId, std::string in_alertContentJson, std::string in_customDataJson, IServerCallback * in_callback = NULL);

		/**
     	* Schedules a normalized push notification to a user
     	*
     	* @param in_profileId The profileId of the user to receive the notification
     	* @param in_fcmContent Valid Fcm data content
     	* @param in_iosContent Valid ios data content
     	* @param in_facebookContent Facebook template string
     	* @param in_startTime Start time of sending the push notification
     	* @param in_callback The method to be invoked when the server response is received
     	*/
		void scheduleRawPushNotificationUTC(const char * in_profileId, std::string in_fcmContent, std::string in_iosContent, std::string in_facebookContent, int32_t in_startTime, IServerCallback * in_callback = NULL);

		/**
     	* Schedules a normalized push notification to a user
     	*
     	* @param in_profileId The profileId of the user to receive the notification
     	* @param in_fcmContent Valid Fcm data content
     	* @param in_iosContent Valid ios data content
     	* @param in_facebookContent Facebook template string
     	* @param minutesFromNow Minutes from now to send the push notification
		* @param callback The method to be invoked when the server response is received
     	*/
		void scheduleRawPushNotificationMinutes(const char * in_profileId, std::string in_fcmContent, std::string in_iosContent, std::string in_facebookContent, int32_t in_minutesFromNow, IServerCallback * in_callback = NULL);

		/**
     	* Sends a raw push notification to a target user.
     	*
     	* @param toProfileId The profileId of the user to receive the notification
 		* @param fcmContent Valid Fcm data content
 		* @param iosContent Valid ios data content
 		* @param facebookContent Facebook template string
 		* @param callback The method to be invoked when the server response is received
     	*/
		void sendRawPushNotification(const char * in_profileId, std::string in_fcmContent, std::string in_iosContent, std::string in_facebookContent, IServerCallback * in_callback = NULL);

		/**
     	* Sends a raw push notification to a target list of users.
     	*
     	* @param in_profileIds Collection of profile IDs to send the notification to
     	* @param in_fcmContent Valid Fcm data content
     	* @param in_iosContent Valid ios data content
     	* @param in_facebookContent Facebook template string
     	* @param in_callback The method to be invoked when the server response is received
     	*/
		void sendRawPushNotificationBatch(std::vector<std::string> in_profileIds, std::string in_fcmContent, std::string in_iosContent, std::string in_facebookContent, IServerCallback * in_callback = NULL);

		/**
     	* Sends a raw push notification to a target group.
     	*
     	* @param in_groupId Target group
     	* @param in_fcmContent Valid Fcm data content
     	* @param in_iosContent Valid ios data content
     	* @param in_facebookContent Facebook template stringn
     	* @param in_callback The method to be invoked when the server response is received
     	*/
		void sendRawPushNotificationToGroup(const char * in_groupId, std::string in_fcmContent, std::string in_iosContent, std::string in_facebookContent, IServerCallback * in_callback = NULL);

		/**
		* Schedules a normalized push notification to a user
	    *
		* @param in_toProfileId The profileId of the user to receive the notification
		* @param in_alertContentJson Body and title of alert
		* @param in_customDataJson Optional custom data
		* @param in_startTime Start time of sending the push notification
		* @param in_callback The method to be invoked when the server response is received
		*/
		void scheduleNormalizedPushNotificationUTC(const char * in_toProfileId, std::string in_alertContentJson, std::string in_customDataJson, int32_t in_startTime, IServerCallback * in_callback = NULL);

		/**
		* Schedules a normalized push notification to a user
		*
		* @param in_toProfileId The profileId of the user to receive the notification
		* @param in_alertContentJson Body and title of alert
		* @param in_customDataJson Optional custom data
		* @param in_minutesFromNow Minutes from now to send the push notification
		* @param in_callback The method to be invoked when the server response is received
		*/
		void scheduleNormalizedPushNotificationMinutes(const char * in_toProfileId, std::string in_alertContentJson, std::string in_customDataJson, int32_t in_minutesFromNow, IServerCallback * in_callback = NULL);

		/**
		* Schedules a rich push notification to a user
		*
		* @param in_toProfileId The profileId of the user to receive the notification
		* @param in_notificationTemplateId Body and title of alert
		* @param in_substitutionsJson Map of substitution positions to strings
		* @param in_startTime Start time of sending the push notification
		* @param in_callback The method to be invoked when the server response is received
		*/
		void scheduleRichPushNotificationUTC(const char * in_toProfileId, int32_t in_notificationTemplateId, std::string in_substitutionsJson, int32_t in_startTime, IServerCallback * in_callback = NULL);

		/**
		* Schedules a rich push notification to a user
		*
		* @param in_toProfileId The profileId of the user to receive the notification
		* @param in_notificationTemplateId Body and title of alert
		* @param in_substitutionsJson Map of substitution positions to strings
		* @param in_minutesFromNow Minutes from now to send the push notification
		* @param in_callback The method to be invoked when the server response is received
		*/
		void scheduleRichPushNotificationMinutes(const char * in_toProfileId, int32_t in_notificationTemplateId, std::string in_substitutionsJson, int32_t in_minutesFromNow, IServerCallback * in_callback = NULL);

		/**
		* Sends a notification to a user consisting of alert content and custom data.
		*
		* @param in_toProfileId The profileId of the user to receive the notification
		* @param in_alertContent Body and title of alert
		* @param in_customData Optional custom data
		* @param in_callback The method to be invoked when the server response is received
		*/
		void sendNormalizedPushNotification(const char * in_toProfileId, std::string in_alertContentJson, std::string in_customDataJson, IServerCallback * in_callback = NULL);

		/**
		* Sends a notification to multiple users consisting of alert content and custom data.
		*
		* @param in_profileIds Collection of profile IDs to send the notification to
		* @param in_alertContent Body and title of alert
		* @param in_customData Optional custom data
		* @param in_callback The method to be invoked when the server response is received
		*/
		void sendNormalizedPushNotificationBatch(std::vector<std::string> in_profileIds, std::string in_alertContentJson, std::string in_customDataJson, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
        void sendRichPushNotification(const char * in_toProifleId, int32_t in_notificationTemplateId, const char * in_substitutionJson, IServerCallback * in_callback = NULL);
    };
}