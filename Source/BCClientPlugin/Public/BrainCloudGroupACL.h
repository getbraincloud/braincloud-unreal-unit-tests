// Copyright 2018 bitHeads, Inc. All Rights Reserved.
#pragma once

#include "IAcl.h"
#include "BrainCloudGroupACL.generated.h"

UCLASS(BlueprintType)
class BCCLIENTPLUGIN_API UBrainCloudGroupACL : public UObject, public IAcl
{
    GENERATED_BODY()

  public:
    UFUNCTION()
    virtual FString toJsonString();

    UFUNCTION(BlueprintCallable, Category = "BrainCloud|ACL")
    static UBrainCloudGroupACL *CreateNewGroupACL(EAcl other, EAcl member);

    virtual TSharedRef<FJsonObject> toJsonObject();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAcl Other;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAcl Member;
};
