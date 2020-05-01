#pragma once

//#include "Components/ActorComponent.h"
#include "BCTimeUtilsProxy.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BCCLIENTPLUGIN_API UBCTimeUtilsProxy : public UObject
{
    GENERATED_BODY()
    public:
      UBCTimeUtilsProxy(const FObjectInitializer &ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "BrainCloud|TimeUtils")
    static int64 UTCDateTimeToUTCMillisBP(FDateTime utcDate);	

    UFUNCTION(BlueprintCallable, Category = "BrainCloud|TimeUtils")
    static FDateTime UTCMillisToUTCDateTime(int64 utcDateTime);

    UFUNCTION(BlueprintCallable, Category = "BrainCloud|TimeUtils")
    static FDateTime LocalTimeToUTCTimeBP(FDateTime localDate);

    UFUNCTION(BlueprintCallable, Category = "BrainCloud|TimeUtils")
    static FDateTime UTCTimeToLocalTimeBP(FDateTime utcDate);
};
