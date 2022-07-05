// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCPlayerStateProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCPlayerStateProxy::UBCPlayerStateProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStateProxy *UBCPlayerStateProxy::ReadUserState(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->readUserState(Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::DeleteUser(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->deleteUser(Proxy);
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

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdateUserName(UBrainCloudWrapper *brainCloudWrapper, FString userName)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->updateUserName(userName, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdateName(UBrainCloudWrapper *brainCloudWrapper, FString name)
{
    return UpdateUserName(brainCloudWrapper, name);
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

UBCPlayerStateProxy *UBCPlayerStateProxy::ClearUserStatus(UBrainCloudWrapper *brainCloudWrapper, const FString &statusName)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->clearUserStatus(statusName, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::ExtendUserStatus(UBrainCloudWrapper *brainCloudWrapper, const FString &statusName, int additionalSecs, const FString &details)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->extendUserStatus(statusName, additionalSecs, details, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::GetUserStatus(UBrainCloudWrapper *brainCloudWrapper, const FString &statusName)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->getUserStatus(statusName, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::SetUserStatus(UBrainCloudWrapper *brainCloudWrapper, const FString &statusName, int durationSecs, const FString &details)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->setUserStatus(statusName, durationSecs, details, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdateTimeZoneOffset(UBrainCloudWrapper *brainCloudWrapper, int32 timeZoneOffset)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->updateTimeZoneOffset(timeZoneOffset, Proxy);
    return Proxy;
}

UBCPlayerStateProxy *UBCPlayerStateProxy::UpdateLanguageCode(UBrainCloudWrapper *brainCloudWrapper, const FString &languageCode)
{
    UBCPlayerStateProxy *Proxy = NewObject<UBCPlayerStateProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStateService()->updateLanguageCode(languageCode, Proxy);
    return Proxy;
}
