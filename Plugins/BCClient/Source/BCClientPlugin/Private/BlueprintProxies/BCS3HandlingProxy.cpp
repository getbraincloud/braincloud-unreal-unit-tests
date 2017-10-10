// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCS3HandlingProxy.h"

UBCS3HandlingProxy::UBCS3HandlingProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCS3HandlingProxy* UBCS3HandlingProxy::GetUpdatedFiles(FString category, FString fileDetails)
{
    UBCS3HandlingProxy* Proxy = NewObject<UBCS3HandlingProxy>();
    BrainCloudClient::getInstance()->getS3HandlingService()->getUpdatedFiles(category, fileDetails, Proxy);
    return Proxy;
}

UBCS3HandlingProxy* UBCS3HandlingProxy::GetFileList(FString category)
{
    UBCS3HandlingProxy* Proxy = NewObject<UBCS3HandlingProxy>();
    BrainCloudClient::getInstance()->getS3HandlingService()->getFileList(category, Proxy);
    return Proxy;
}

UBCS3HandlingProxy* UBCS3HandlingProxy::GetCDNUrl(const FString& fileId)
{
	UBCS3HandlingProxy* Proxy = NewObject<UBCS3HandlingProxy>();
	BrainCloudClient::getInstance()->getS3HandlingService()->getCDNUrl(fileId, Proxy);
	return Proxy;
}

//callbacks
void UBCS3HandlingProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCS3HandlingProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

