// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BCPlatform.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCPushNotificationProxy.h"

UBCPushNotificationProxy::UBCPushNotificationProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPushNotificationProxy* UBCPushNotificationProxy::DeregisterAllPushNotificationDeviceTokens(ABrainCloudActor *brainCloud)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->deregisterAllPushNotificationDeviceTokens(Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::DeregisterPushNotificationDeviceToken(ABrainCloudActor *brainCloud, EBCPlatform platform, const FString& deviceToken)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->deregisterPushNotificationDeviceToken(platform, deviceToken, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::RegisterPushNotificationDeviceToken(ABrainCloudActor *brainCloud, EBCPlatform platform, const FString& deviceToken)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->registerPushNotificationDeviceToken(platform, deviceToken, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendSimplePushNotification(ABrainCloudActor *brainCloud, const FString& toPlayerId, const FString& message)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendSimplePushNotification(toPlayerId, message, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRichPushNotification(ABrainCloudActor *brainCloud, const FString& toPlayerId, int32 notificationTemplateId)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendRichPushNotification(toPlayerId, notificationTemplateId, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRichPushNotificationWithParams(ABrainCloudActor *brainCloud, const FString& toPlayerId, int32 notificationTemplateId, const FString& substitutionJson)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendRichPushNotificationWithParams(toPlayerId, notificationTemplateId, substitutionJson, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendTemplatedPushNotificationToGroup(ABrainCloudActor *brainCloud, const FString& groupId, int32 notificationTemplateId, const FString& substitutionJson)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendTemplatedPushNotificationToGroup(groupId, notificationTemplateId, substitutionJson, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleRawPushNotificationUTC(ABrainCloudActor *brainCloud, const FString& profileId, const FString& fcmContent, const FString& iosContent, const FString& facebookContent, int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleRawPushNotificationUTC(profileId, fcmContent, iosContent, facebookContent, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleRawPushNotificationMinutes(ABrainCloudActor *brainCloud, const FString& profileId, const FString& fcmContent, const FString& iosContent, const FString& facebookContent, int32 minutesFromNow)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleRawPushNotificationMinutes(profileId, fcmContent, iosContent, facebookContent, minutesFromNow, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRawPushNotification(ABrainCloudActor *brainCloud, const FString& profileId, const FString& fcmContent, const FString& iosContent, const FString& facebookContent)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendRawPushNotification(profileId, fcmContent, iosContent, facebookContent, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRawPushNotificationBatch(ABrainCloudActor *brainCloud, const TArray<FString> profileIds, const FString& fcmContent, const FString& iosContent, const FString& facebookContent)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendRawPushNotificationBatch(profileIds, fcmContent, iosContent, facebookContent, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRawPushNotificationToGroup(ABrainCloudActor *brainCloud, const FString& groupId, const FString& fcmContent, const FString& iosContent, const FString& facebookContent)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendRawPushNotificationToGroup(groupId, fcmContent, iosContent, facebookContent, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendNormalizedPushNotificationToGroup(ABrainCloudActor *brainCloud, const FString& groupId, const FString& alertContentJson, const FString& customDataJson)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendNormalizedPushNotificationToGroup(groupId, alertContentJson, customDataJson, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleNormalizedPushNotificationUTC(ABrainCloudActor *brainCloud, const FString& profileId, const FString& alertContentJson, const FString& substitutionJson, const int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleNormalizedPushNotificationUTC(profileId, alertContentJson, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleNormalizedPushNotificationMinutes(ABrainCloudActor *brainCloud, const FString& profileId, const FString& alertContentJson, const FString& substitutionJson, const int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleNormalizedPushNotificationMinutes(profileId, alertContentJson, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleRichPushNotificationUTC(ABrainCloudActor *brainCloud, const FString& profileId, const int32 notificationTemplateId, const FString& substitutionJson, const int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleRichPushNotificationUTC(profileId, notificationTemplateId, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleRichPushNotificationMinutes(ABrainCloudActor *brainCloud, const FString& profileId, const int32 notificationTemplateId, const FString& substitutionJson, const int32 minutesFromNow)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->scheduleRichPushNotificationMinutes(profileId, notificationTemplateId, substitutionJson, minutesFromNow, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendNormalizedPushNotification(ABrainCloudActor *brainCloud, const FString& toPlayerId, const FString& alertContentJson, const FString& customDataJson)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPushNotificationService()->sendNormalizedPushNotification(toPlayerId, alertContentJson, customDataJson, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendNormalizedPushNotificationBatch(ABrainCloudActor *brainCloud, const TArray<FString> profileIds, const FString& alertContentJson, const FString& customDataJson)
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

