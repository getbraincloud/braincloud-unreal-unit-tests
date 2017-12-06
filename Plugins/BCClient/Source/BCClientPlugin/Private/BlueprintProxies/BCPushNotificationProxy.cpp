// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BCPlatform.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCPushNotificationProxy.h"

UBCPushNotificationProxy::UBCPushNotificationProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPushNotificationProxy* UBCPushNotificationProxy::DeregisterAllPushNotificationDeviceTokens(ABrainCloud *brainCloud)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->deregisterAllPushNotificationDeviceTokens(Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::DeregisterPushNotificationDeviceToken(ABrainCloud *brainCloud, EBCPlatform platform, const FString& deviceToken)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->deregisterPushNotificationDeviceToken(platform, deviceToken, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::RegisterPushNotificationDeviceToken(ABrainCloud *brainCloud, EBCPlatform platform, const FString& deviceToken)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->registerPushNotificationDeviceToken(platform, deviceToken, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendSimplePushNotification(ABrainCloud *brainCloud, const FString& toPlayerId, const FString& message)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendSimplePushNotification(toPlayerId, message, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRichPushNotification(ABrainCloud *brainCloud, const FString& toPlayerId, int32 notificationTemplateId)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendRichPushNotification(toPlayerId, notificationTemplateId, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRichPushNotificationWithParams(ABrainCloud *brainCloud, const FString& toPlayerId, int32 notificationTemplateId, const FString& substitutionJson)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendRichPushNotificationWithParams(toPlayerId, notificationTemplateId, substitutionJson, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendTemplatedPushNotificationToGroup(ABrainCloud *brainCloud, const FString& groupId, int32 notificationTemplateId, const FString& substitutionJson)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendTemplatedPushNotificationToGroup(groupId, notificationTemplateId, substitutionJson, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleRawPushNotificationUTC(ABrainCloud *brainCloud, const FString& profileId, const FString& fcmContent, const FString& iosContent, const FString& facebookContent, int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleRawPushNotificationUTC(profileId, fcmContent, iosContent, facebookContent, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleRawPushNotificationMinutes(ABrainCloud *brainCloud, const FString& profileId, const FString& fcmContent, const FString& iosContent, const FString& facebookContent, int32 minutesFromNow)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleRawPushNotificationMinutes(profileId, fcmContent, iosContent, facebookContent, minutesFromNow, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRawPushNotification(ABrainCloud *brainCloud, const FString& profileId, const FString& fcmContent, const FString& iosContent, const FString& facebookContent)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendRawPushNotification(profileId, fcmContent, iosContent, facebookContent, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRawPushNotificationBatch(ABrainCloud *brainCloud, const TArray<FString> profileIds, const FString& fcmContent, const FString& iosContent, const FString& facebookContent)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendRawPushNotificationBatch(profileIds, fcmContent, iosContent, facebookContent, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRawPushNotificationToGroup(ABrainCloud *brainCloud, const FString& groupId, const FString& fcmContent, const FString& iosContent, const FString& facebookContent)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendRawPushNotificationToGroup(groupId, fcmContent, iosContent, facebookContent, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendNormalizedPushNotificationToGroup(ABrainCloud *brainCloud, const FString& groupId, const FString& alertContentJson, const FString& customDataJson)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendNormalizedPushNotificationToGroup(groupId, alertContentJson, customDataJson, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleNormalizedPushNotificationUTC(ABrainCloud *brainCloud, const FString& profileId, const FString& alertContentJson, const FString& substitutionJson, const int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleNormalizedPushNotificationUTC(profileId, alertContentJson, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleNormalizedPushNotificationMinutes(ABrainCloud *brainCloud, const FString& profileId, const FString& alertContentJson, const FString& substitutionJson, const int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleNormalizedPushNotificationMinutes(profileId, alertContentJson, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleRichPushNotificationUTC(ABrainCloud *brainCloud, const FString& profileId, const int32 notificationTemplateId, const FString& substitutionJson, const int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleRichPushNotificationUTC(profileId, notificationTemplateId, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleRichPushNotificationMinutes(ABrainCloud *brainCloud, const FString& profileId, const int32 notificationTemplateId, const FString& substitutionJson, const int32 minutesFromNow)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleRichPushNotificationMinutes(profileId, notificationTemplateId, substitutionJson, minutesFromNow, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendNormalizedPushNotification(ABrainCloud *brainCloud, const FString& toPlayerId, const FString& alertContentJson, const FString& customDataJson)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendNormalizedPushNotification(toPlayerId, alertContentJson, customDataJson, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendNormalizedPushNotificationBatch(ABrainCloud *brainCloud, const TArray<FString> profileIds, const FString& alertContentJson, const FString& customDataJson)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendNormalizedPushNotificationBatch(profileIds, alertContentJson, customDataJson, Proxy);
	return Proxy;
}

//callbacks
void UBCPushNotificationProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCPushNotificationProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

