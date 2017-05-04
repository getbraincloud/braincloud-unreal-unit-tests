// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BCPlatform.h"

#include "BCPushNotificationProxy.h"

UBCPushNotificationProxy::UBCPushNotificationProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPushNotificationProxy* UBCPushNotificationProxy::DeregisterAllPushNotificationDeviceTokens()
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    BrainCloudClient::getInstance()->getPushNotificationService()->deregisterAllPushNotificationDeviceTokens(Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::DeregisterPushNotificationDeviceToken(EBCPlatform platform, const FString& deviceToken)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    BrainCloudClient::getInstance()->getPushNotificationService()->deregisterPushNotificationDeviceToken(platform, deviceToken, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::RegisterPushNotificationDeviceToken(EBCPlatform platform, const FString& deviceToken)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    BrainCloudClient::getInstance()->getPushNotificationService()->registerPushNotificationDeviceToken(platform, deviceToken, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendSimplePushNotification(const FString& toPlayerId, const FString& message)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    BrainCloudClient::getInstance()->getPushNotificationService()->sendSimplePushNotification(toPlayerId, message, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRichPushNotification(const FString& toPlayerId, int32 notificationTemplateId)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    BrainCloudClient::getInstance()->getPushNotificationService()->sendRichPushNotification(toPlayerId, notificationTemplateId, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendRichPushNotificationWithParams(const FString& toPlayerId, int32 notificationTemplateId, const FString& substitutionJson)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    BrainCloudClient::getInstance()->getPushNotificationService()->sendRichPushNotificationWithParams(toPlayerId, notificationTemplateId, substitutionJson, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendTemplatedPushNotificationToGroup(const FString& groupId, int32 notificationTemplateId, const FString& substitutionJson)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    BrainCloudClient::getInstance()->getPushNotificationService()->sendTemplatedPushNotificationToGroup(groupId, notificationTemplateId, substitutionJson, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendNormalizedPushNotificationToGroup(const FString& groupId, const FString& alertContentJson, const FString& customDataJson)
{
    UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
    BrainCloudClient::getInstance()->getPushNotificationService()->sendNormalizedPushNotificationToGroup(groupId, alertContentJson, customDataJson, Proxy);
    return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleNormalizedPushNotificationUTC(const FString& profileId, FString& alertContentJson, const FString& substitutionJson, int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	BrainCloudClient::getInstance()->getPushNotificationService()->scheduleNormalizedPushNotificationUTC(profileId, alertContentJson, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleNormalizedPushNotificationMinutes(const FString& profileId, FString& alertContentJson, const FString& substitutionJson, int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	BrainCloudClient::getInstance()->getPushNotificationService()->scheduleNormalizedPushNotificationMinutes(profileId, alertContentJson, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleRichPushNotificationUTC(const FString& profileId, int32 notificationTemplateId, FString& substitutionJson, int32 startTime)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	BrainCloudClient::getInstance()->getPushNotificationService()->scheduleRichPushNotificationUTC(profileId, alertContentJson, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::ScheduleRichPushNotificationMinutes(const FString& profileId, int32 notificationTemplateId, FString& substitutionJson, int32 minutesFromNow)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	BrainCloudClient::getInstance()->getPushNotificationService()->scheduleRichPushNotificationMinutes(profileId, alertContentJson, substitutionJson, startTime, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendNormalizedPushNotification(const FString& toPlayerId, const FString& alertContentJson, const FString& customDataJson)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	BrainCloudClient::getInstance()->getPushNotificationService()->sendNormalizedPushNotification(toPlayerId, alertContentJson, customDataJson, Proxy);
	return Proxy;
}

UBCPushNotificationProxy* UBCPushNotificationProxy::SendNormalizedPushNotificationBatch(const TArray<FString> profileIds, const FString& alertContentJson, const FString& customDataJson)
{
	UBCPushNotificationProxy* Proxy = NewObject<UBCPushNotificationProxy>();
	BrainCloudClient::getInstance()->getPushNotificationService()->sendNormalizedPushNotificationBatch(profileIds, alertContentJson, customDataJson, Proxy);
	return Proxy;
}

//callbacks
void UBCPushNotificationProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCPushNotificationProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

