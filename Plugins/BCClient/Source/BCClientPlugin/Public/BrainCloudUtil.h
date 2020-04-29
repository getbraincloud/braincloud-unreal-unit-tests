// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once
#include "Components/ActorComponent.h"
#include "BrainCloudUtil.generated.h"

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudUtil
{
  public:
    BrainCloudUtil(BrainCloudClient *client);

    static int64 UTCDateTimeToUTCMillis(FDateTime dateTime);
    static FDateTime ToDateTimeFromUTCEpoch(int64 utcDateTime);
      
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


    //static FDateTime UTCMillisToUTCDateTime(int64 utcMillis);

UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|TimeUtils")
static int64 UTCDateTimeToUTCMillisBP(FDateTime utcDate);	

 };
