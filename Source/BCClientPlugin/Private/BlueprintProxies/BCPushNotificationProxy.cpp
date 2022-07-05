// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCPushNotificationProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BCPlatform.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCPushNotificationProxy::UBCPushNotificationProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCPushNotificationProxy *UBCPushNotificationProxy::DeregisterAllPushNotificationDeviceTokens(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->deregisterAllPushNotificationDeviceTokens(Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::DeregisterPushNotificationDeviceToken(UBrainCloudWrapper *brainCloudWrapper, EBCPlatform platform, const FString &deviceToken)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->deregisterPushNotificationDeviceToken(platform, deviceToken, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::RegisterPushNotificationDeviceToken(UBrainCloudWrapper *brainCloudWrapper, EBCPlatform platform, const FString &deviceToken)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->registerPushNotificationDeviceToken(platform, deviceToken, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::SendSimplePushNotification(UBrainCloudWrapper *brainCloudWrapper, const FString &toPlayerId, const FString &message)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->sendSimplePushNotification(toPlayerId, message, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::SendRichPushNotification(UBrainCloudWrapper *brainCloudWrapper, const FString &toPlayerId, int32 notificationTemplateId)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->sendRichPushNotification(toPlayerId, notificationTemplateId, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::SendRichPushNotificationWithParams(UBrainCloudWrapper *brainCloudWrapper, const FString &toPlayerId, int32 notificationTemplateId, const FString &substitutionJson)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->sendRichPushNotificationWithParams(toPlayerId, notificationTemplateId, substitutionJson, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::SendTemplatedPushNotificationToGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, int32 notificationTemplateId, const FString &substitutionJson)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->sendTemplatedPushNotificationToGroup(groupId, notificationTemplateId, substitutionJson, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::ScheduleRawPushNotificationUTC(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, int64 startTime)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->scheduleRawPushNotificationUTC(profileId, fcmContent, iosContent, facebookContent, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::ScheduleRawPushNotificationMinutes(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, int32 minutesFromNow)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->scheduleRawPushNotificationMinutes(profileId, fcmContent, iosContent, facebookContent, minutesFromNow, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::SendRawPushNotification(UBrainCloudWrapper *brainCloudWrapper, const FString &playerId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->sendRawPushNotification(playerId, fcmContent, iosContent, facebookContent, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::SendRawPushNotificationBatch(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> profileIds, const FString &fcmContent, const FString &iosContent, const FString &facebookContent)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->sendRawPushNotificationBatch(profileIds, fcmContent, iosContent, facebookContent, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::SendRawPushNotificationToGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->sendRawPushNotificationToGroup(groupId, fcmContent, iosContent, facebookContent, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::SendNormalizedPushNotificationToGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &alertContentJson, const FString &customDataJson)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->sendNormalizedPushNotificationToGroup(groupId, alertContentJson, customDataJson, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::ScheduleNormalizedPushNotificationUTC(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &alertContentJson, const FString &substitutionJson, const int64 startTime)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->scheduleNormalizedPushNotificationUTC(profileId, alertContentJson, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::ScheduleNormalizedPushNotificationMinutes(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &alertContentJson, const FString &substitutionJson, const int32 startTime)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->scheduleNormalizedPushNotificationMinutes(profileId, alertContentJson, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::ScheduleRichPushNotificationUTC(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const int32 notificationTemplateId, const FString &substitutionJson, const int64 startTime)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->scheduleRichPushNotificationUTC(profileId, notificationTemplateId, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::ScheduleRichPushNotificationMinutes(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const int32 notificationTemplateId, const FString &substitutionJson, const int32 minutesFromNow)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->scheduleRichPushNotificationMinutes(profileId, notificationTemplateId, substitutionJson, minutesFromNow, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::SendNormalizedPushNotification(UBrainCloudWrapper *brainCloudWrapper, const FString &toPlayerId, const FString &alertContentJson, const FString &customDataJson)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->sendNormalizedPushNotification(toPlayerId, alertContentJson, customDataJson, Proxy);
	return Proxy;
}

UBCPushNotificationProxy *UBCPushNotificationProxy::SendNormalizedPushNotificationBatch(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> profileIds, const FString &alertContentJson, const FString &customDataJson)
{
	UBCPushNotificationProxy *Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPushNotificationService()->sendNormalizedPushNotificationBatch(profileIds, alertContentJson, customDataJson, Proxy);
	return Proxy;
}
