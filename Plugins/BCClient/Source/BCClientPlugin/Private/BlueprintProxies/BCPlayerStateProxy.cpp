// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BCPlayerStateProxy.h"
#include "BrainCloudWrapper.h"

UBCPlayerStateProxy::UBCPlayerStateProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStateProxy* UBCPlayerStateProxy::ReadPlayerState(ABrainCloudActor *brainCloud)
{
	UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->readUserState(Proxy);
	return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::ReadUserState(ABrainCloudActor *brainCloud)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->readUserState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::DeletePlayer(ABrainCloudActor *brainCloud)
{
	UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->deleteUser(Proxy);
	return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::DeleteUser(ABrainCloudActor *brainCloud)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->deleteUser(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::ResetPlayerState(ABrainCloudActor *brainCloud)
{
	UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->resetUserState(Proxy);
	return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::ResetUserState(ABrainCloudActor *brainCloud)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->resetUserState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::Logout(ABrainCloudActor *brainCloud)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->logout(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdatePlayerName(ABrainCloudActor *brainCloud, FString playerName)
{
	return UpdateName(brainCloud, playerName);
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateUserName(ABrainCloudActor *brainCloud, FString userName)
{
    return UpdateName(brainCloud, userName);
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateName(ABrainCloudActor *brainCloud, FString name)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateUserName(name, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateSummaryFriendData(ABrainCloudActor *brainCloud, const FString& jsonSummaryData)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateSummaryFriendData(jsonSummaryData, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::GetAttributes(ABrainCloudActor *brainCloud)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->getAttributes(Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateAttributes(ABrainCloudActor *brainCloud, FString jsonAttributes, bool wipeExisting)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateAttributes(jsonAttributes, wipeExisting, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::RemoveAttributes(ABrainCloudActor *brainCloud, const TArray<FString>& attributeNames)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->removeAttributes(attributeNames, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdatePlayerPictureUrl(ABrainCloudActor *brainCloud, const FString& pictureUrl)
{
	UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateUserPictureUrl(pictureUrl, Proxy);
	return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateUserPictureUrl(ABrainCloudActor *brainCloud, const FString& pictureUrl)
{
    UBCPlayerStateProxy* Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStateService()->updateUserPictureUrl(pictureUrl, Proxy);
    return Proxy;
}

UBCPlayerStateProxy* UBCPlayerStateProxy::UpdateContactEmail(ABrainCloudActor *brainCloud, const FString& contactEmail)
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

