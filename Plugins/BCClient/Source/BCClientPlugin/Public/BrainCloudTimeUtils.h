// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once
#include "Components/ActorComponent.h"
#include "BrainCloudTimeUtils.generated.h"

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudTimeUtils
{
  public:
    BrainCloudTimeUtils(BrainCloudClient *client);

    static int64 UTCDateTimeToUTCMillis(FDateTime dateTime);
    static FDateTime ToDateTimeFromUTCEpoch(int64 utcDateTime);
    static FDateTime LocalTimeToUTCTime(FDateTime localDate);
    static FDateTime UTCTimeToLocalTime(FDateTime utcDate);
      
  private:
    BrainCloudClient *_client = nullptr;
};
 //#include "UObject/NoExportTypes.h"
//#include "Delegates/DelegateCombinations.h"
//#pragma once


 UCLASS(Blueprintable, BlueprintType)
 class BCCLIENTPLUGIN_API UTimeUtilsBase : public UObject
 {
 	GENERATED_BODY()
  public:
    UTimeUtilsBase();
	virtual void BeginDestroy() override;

UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|TimeUtils")
static int64 UTCDateTimeToUTCMillisBP(FDateTime utcDate);	

UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|TimeUtils")
static FDateTime ToDateTimeFromUTCEpochBP(int64 utcDateTime);

UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|TimeUtils")
static FDateTime LocalTimeToUTCTimeBP(FDateTime localDate);

UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|TimeUtils")
static FDateTime UTCTimeToLocalTimeBP(FDateTime utcDate);

 };
