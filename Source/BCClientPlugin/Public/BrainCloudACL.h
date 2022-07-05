// Copyright 2018 bitHeads, Inc. All Rights Reserved.
#pragma once

#include "IAcl.h"
#include "BrainCloudACL.generated.h"

UCLASS(BlueprintType)
class BCCLIENTPLUGIN_API UBrainCloudACL : public UObject, public IAcl
{
  GENERATED_BODY()

public:
  UFUNCTION()
  virtual FString toJsonString();

  UFUNCTION(BlueprintCallable, Category = "BrainCloud|ACL")
  static UBrainCloudACL *CreateNewACL(EAcl access);

  virtual TSharedRef<FJsonObject> toJsonObject();

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  EAcl Other;
};
