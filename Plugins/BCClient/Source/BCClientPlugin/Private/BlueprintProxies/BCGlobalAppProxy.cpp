// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCGlobalAppProxy.h"

UBCGlobalAppProxy::UBCGlobalAppProxy(const FObjectInitializer& ObjectInitializer)
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
UBCGlobalAppProxy* UBCGlobalAppProxy::ReadProperties()
{
    UBCGlobalAppProxy* Proxy = NewObject<UBCGlobalAppProxy>();
    BrainCloudClient::getInstance()->getGlobalAppService()->readProperties(Proxy);
    return Proxy;
}

//callbacks
void UBCGlobalAppProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCGlobalAppProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

