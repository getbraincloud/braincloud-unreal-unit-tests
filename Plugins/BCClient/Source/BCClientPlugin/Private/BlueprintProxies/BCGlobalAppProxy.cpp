// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCGlobalAppProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCGlobalAppProxy::UBCGlobalAppProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

/**
* Read game's global properties
*
* Service Name - GlobalApp
* Service Operation - ReadProperties
*
* JSON describing the global properties:
* {
*   "status":200,
*   "data":{
*     {
*        "pName": {
*         "name": "pName",
*         "description": "pValue",
*         "value": "pDescription"
*        }
*       }
*   }
* }
*/
UBCGlobalAppProxy *UBCGlobalAppProxy::ReadProperties(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCGlobalAppProxy *Proxy = NewObject<UBCGlobalAppProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalAppService()->readProperties(Proxy);
    return Proxy;
}

UBCGlobalAppProxy* UBCGlobalAppProxy::ReadSelectedProperties(const TArray<FString>& in_propertyIds, UBrainCloudWrapper* brainCloudWrapper)
{
    UBCGlobalAppProxy *Proxy = NewObject<UBCGlobalAppProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalAppService()->readSelectedProperties(in_propertyIds,Proxy);
    return Proxy;
}

UBCGlobalAppProxy* UBCGlobalAppProxy::ReadPropertiesInCategories(const TArray<FString>& in_categories, UBrainCloudWrapper* brainCloudWrapper)
{
    UBCGlobalAppProxy *Proxy = NewObject<UBCGlobalAppProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalAppService()->readPropertiesInCategories(in_categories,Proxy);
    return Proxy;
}

