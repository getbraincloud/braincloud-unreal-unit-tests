// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
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
         * Deregisters all device tokens currently registered to the player.
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void deregisterAllPushNotificationDeviceTokens(IServerCallback * in_callback = NULL);

        /**
         * Deregisters the given device token from the server to disable this device
         * from receiving push notifications.
         *
         * @param in_device The device platform being deregistered.
         * @param in_token The platform-dependant device token needed for push notifications.
         * @param in_callback The method to be invoked when the server response is received
         */
        void deregisterPushNotificationDeviceToken(const Platform & in_platform, const char * in_token, IServerCallback * in_callback = NULL);

        /**
         * Registers the given device token with the server to enable this device
         * to receive push notifications.
         *
         * @param in_platform The device platform
         * @param in_deviceToken The platform-dependant device token needed for push notifications.
         *  On IOS, this is obtained using the application:didRegisterForRemoteNotificationsWithDeviceToken callback
         * @param in_callback The method to be invoked when the server response is received
         */
        void registerPushNotificationDeviceToken(const Platform & in_platform, const char * in_deviceToken, IServerCallback * in_callback = NULL);

        /**
         * Deprecated - Use method with Platform object paramater instead - Removal on June 21 2016
         */
        DEPRECATED void registerPushNotificationDeviceToken(const char * in_deviceType, const char * in_deviceToken, IServerCallback * in_callback = NULL);

        /**
         * Sends a simple push notification based on the passed in message.
         * NOTE: It is possible to send a push notification to oneself.
         *
         * @param in_toPlayerId The braincloud playerId of the user to receive the notification
         * @param in_message Text of the push notification
         * @param in_callback The method to be invoked when the server response is received
         */
        void sendSimplePushNotification(const char * in_toPlayerId, const char * in_message, IServerCallback * in_callback = NULL);

        /**
         * Sends a notification to a user based on a brainCloud portal configured notification template.
         * NOTE: It is possible to send a push notification to oneself.
         *
         * @param in_toPlayerId The braincloud playerId of the user to receive the notification
         * @param in_notificationTemplateId Id of the notification template
         * @param in_callback The method to be invoked when the server response is received
         */
        void sendRichPushNotification(const char * in_toPlayerId, int32_t in_notificationTemplateId, IServerCallback * in_callback = NULL);

        /**
         * Sends a notification to a user based on a brainCloud portal configured notification template.
         * Includes JSON defining the substitution params to use with the template.
         * See the Portal documentation for more info.
         * NOTE: It is possible to send a push notification to oneself.
         *
         * @param in_toPlayerId The braincloud playerId of the user to receive the notification
         * @param in_notificationTemplateId Id of the notification template
         * @param in_substitutionJson JSON defining the substitution params to use with the template
         * @param in_callback The method to be invoked when the server response is received
         */
        void sendRichPushNotificationWithParams(const char * in_toPlayerId, int32_t in_notificationTemplateId, const char * in_substitutionJson, IServerCallback * in_callback = NULL);

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

    private:
        BrainCloudClient * m_client;
        void sendRichPushNotification(const char * in_toPlayerId, int32_t in_notificationTemplateId, const char * in_substitutionJson, IServerCallback * in_callback = NULL);
    };
}