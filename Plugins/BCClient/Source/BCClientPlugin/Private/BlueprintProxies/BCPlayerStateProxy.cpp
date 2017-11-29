// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BCPlayerStateProxy.h"
#include "BrainCloudWrapper.h"

UBCPlayerStateProxy::UBCPlayerStateProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStateProxy* UBCPlayerStateProxy::ReadPlayerState(ABrainCloud *brainCloud)
{
	UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->readUserState(Proxy);
	return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::ReadUserState(ABrainCloud *brainCloud)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->readUserState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::DeletePlayer(ABrainCloud *brainCloud)
{
	UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->deleteUser(Proxy);
	return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::DeleteUser(ABrainCloud *brainCloud)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->deleteUser(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::ResetPlayerState(ABrainCloud *brainCloud)
{
	UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->resetUserState(Proxy);
	return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::ResetUserState(ABrainCloud *brainCloud)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->resetUserState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::Logout(ABrainCloud *brainCloud)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->logout(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdatePlayerName(ABrainCloud *brainCloud, FString playerName)
{
	UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateUserName(playerName, Proxy);
	return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateUserName(ABrainCloud *brainCloud, FString userName)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateUserName(userName, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateSummaryFriendData(ABrainCloud *brainCloud, const FString& jsonSummaryData)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateSummaryFriendData(jsonSummaryData, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::GetAttributes(ABrainCloud *brainCloud)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->getAttributes(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateAttributes(ABrainCloud *brainCloud, FString jsonAttributes, bool wipeExisting)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateAttributes(jsonAttributes, wipeExisting, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::RemoveAttributes(ABrainCloud *brainCloud, const TArray<FString>& attributeNames)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->removeAttributes(attributeNames, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdatePlayerPictureUrl(ABrainCloud *brainCloud, const FString& pictureUrl)
{
	UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateUserPictureUrl(pictureUrl, Proxy);
	return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateUserPictureUrl(ABrainCloud *brainCloud, const FString& pictureUrl)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateUserPictureUrl(pictureUrl, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateContactEmail(ABrainCloud *brainCloud, const FString& contactEmail)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateContactEmail(contactEmail, Proxy);
    return Proxy;
}

//callbacks
void UBCPlayerStateProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCPlayerStateProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

