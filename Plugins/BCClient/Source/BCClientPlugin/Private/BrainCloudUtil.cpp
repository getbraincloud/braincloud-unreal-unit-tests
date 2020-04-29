// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudUtil.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudWrapper.h"
#include "BCWrapperProxy.h"

BrainCloudUtil::BrainCloudUtil(BrainCloudClient *client) : _client(client){};

int64 BrainCloudUtil::UTCDateTimeToUTCMillis(FDateTime dateTime)
{
    FTimespan mySpan;
    FDateTime date = dateTime.UtcNow();
    FDateTime myFDateTime(1970, 1, 1, 0, 0, 0, 0);
    int64 ticks = date.GetTicks() - myFDateTime.GetTicks();
    int64 ts = ticks / mySpan.GetTicks();
    return ts;
}

FDateTime BrainCloudUtil::ToDateTimeFromUTCEpoch(int64 utcDateTime)
{
    FTimespan mySpan;
    FDateTime timeInTicks = utcDateTime * mySpan.GetTicks();
    FDateTime myFDateTime= FDateTime(1970, 1, 1, 0, 0, 0, 0)+timeInTicks.GetTicks();
    return myFDateTime;
}

int64 UTimeUtilsBase::UTCDateTimeToUTCMillisBP(FDateTime utcDate)
{
 return BrainCloudUtil::UTCDateTimeToUTCMillis(utcDate);
}	

UTimeUtilsBase::UTimeUtilsBase()
{

}

void UTimeUtilsBase::BeginDestroy()
{
	Super::BeginDestroy();
}

// UWebSocketBase::UWebSocketBase()
// {
// #if PLATFORM_UWP
// 	messageWebSocket = nullptr;
// 	uwpSocketHelper = ref new FUWPSocketHelper();
// 	uwpSocketHelper->SetParent((int64)this);
// #if ENGINE_MINOR_VERSION <24
// #if PLATFORM_HTML5
// 	mWebSocketRef = -1;
// 	mConnectSuccess = false;
// 	mIsError = false;
// 	#endif
// 	#endif

// #else
// 	mlwsContext = nullptr;
// 	mlws = nullptr;
// #endif
// }
