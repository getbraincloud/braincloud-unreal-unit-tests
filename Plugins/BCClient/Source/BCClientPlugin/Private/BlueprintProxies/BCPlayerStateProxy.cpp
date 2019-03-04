// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BCPlayerStateProxy.h"
#include "BrainCloudWrapper.h"

UBCPlayerStateProxy::UBCPlayerStateProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStateProxy *UBCPlayerStateProxy::ReadPlayerState(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->readUserState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::ReadUserState(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->readUserState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::DeletePlayer(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->deleteUser(Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::DeleteUser(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->deleteUser(Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::ResetPlayerState(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->resetUserState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::ResetUserState(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->resetUserState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::Logout(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->logout(Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdatePlayerName(UBrainCloudWrapper *brainCloudWrapper, FString playerName)
{
    return UpdateName(brainCloudWrapper, playerName);
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdateUserName(UBrainCloudWrapper *brainCloudWrapper, FString userName)
{
    return UpdateName(brainCloudWrapper, userName);
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdateName(UBrainCloudWrapper *brainCloudWrapper, FString name)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->updateUserName(name, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdateSummaryFriendData(UBrainCloudWrapper *brainCloudWrapper, const FString &jsonSummaryData)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->updateSummaryFriendData(jsonSummaryData, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::GetAttributes(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->getAttributes(Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdateAttributes(UBrainCloudWrapper *brainCloudWrapper, FString jsonAttributes, bool wipeExisting)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->updateAttributes(jsonAttributes, wipeExisting, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::RemoveAttributes(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &attributeNames)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->removeAttributes(attributeNames, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdatePlayerPictureUrl(UBrainCloudWrapper *brainCloudWrapper, const FString &pictureUrl)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->updateUserPictureUrl(pictureUrl, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdateUserPictureUrl(UBrainCloudWrapper *brainCloudWrapper, const FString &pictureUrl)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->updateUserPictureUrl(pictureUrl, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdateContactEmail(UBrainCloudWrapper *brainCloudWrapper, const FString &contactEmail)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->updateContactEmail(contactEmail, Proxy);
    return Proxy;
}
