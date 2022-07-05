// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCPresenceProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCPresenceProxy::UBCPresenceProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPresenceProxy *UBCPresenceProxy::ForcePush(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPresenceProxy *Proxy = NewObject<UBCPresenceProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPresenceService()->forcePush(Proxy);
    return Proxy;
}

UBCPresenceProxy *UBCPresenceProxy::GetPresenceOfFriends(UBrainCloudWrapper *brainCloudWrapper, const FString &platform, bool includeOffline)
{
    UBCPresenceProxy *Proxy = NewObject<UBCPresenceProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPresenceService()->getPresenceOfFriends(platform, includeOffline, Proxy);
    return Proxy;
}

UBCPresenceProxy *UBCPresenceProxy::GetPresenceOfGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, bool includeOffline)
{
    UBCPresenceProxy *Proxy = NewObject<UBCPresenceProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPresenceService()->getPresenceOfGroup(groupId, includeOffline, Proxy);
    return Proxy;
}

UBCPresenceProxy *UBCPresenceProxy::GetPresenceOfUsers(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &profileIds, bool includeOffline)
{
    UBCPresenceProxy *Proxy = NewObject<UBCPresenceProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPresenceService()->getPresenceOfUsers(profileIds, includeOffline, Proxy);
    return Proxy;
}

UBCPresenceProxy *UBCPresenceProxy::RegisterListenersForFriends(UBrainCloudWrapper *brainCloudWrapper, const FString &platform, bool bidirectional)
{
    UBCPresenceProxy *Proxy = NewObject<UBCPresenceProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPresenceService()->registerListenersForFriends(platform, bidirectional, Proxy);
    return Proxy;
}

UBCPresenceProxy *UBCPresenceProxy::RegisterListenersForGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, bool bidirectional)
{
    UBCPresenceProxy *Proxy = NewObject<UBCPresenceProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPresenceService()->registerListenersForGroup(groupId, bidirectional, Proxy);
    return Proxy;
}

UBCPresenceProxy *UBCPresenceProxy::RegisterListenersForProfiles(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &profileIds, bool bidirectional)
{
    UBCPresenceProxy *Proxy = NewObject<UBCPresenceProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPresenceService()->registerListenersForProfiles(profileIds, bidirectional, Proxy);
    return Proxy;
}

UBCPresenceProxy *UBCPresenceProxy::SetVisibility(UBrainCloudWrapper *brainCloudWrapper, bool visible)
{
    UBCPresenceProxy *Proxy = NewObject<UBCPresenceProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPresenceService()->setVisibility(visible, Proxy);
    return Proxy;
}

UBCPresenceProxy *UBCPresenceProxy::StopListening(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPresenceProxy *Proxy = NewObject<UBCPresenceProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPresenceService()->stopListening(Proxy);
    return Proxy;
}

UBCPresenceProxy *UBCPresenceProxy::UpdateActivity(UBrainCloudWrapper *brainCloudWrapper, const FString &activity)
{
    UBCPresenceProxy *Proxy = NewObject<UBCPresenceProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPresenceService()->updateActivity(activity, Proxy);
    return Proxy;
}
