// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/SaveGame.h"
#include "BrainCloudSave.generated.h"

/**
 *
 */
UCLASS()
class BCCLIENTPLUGIN_API UBrainCloudSave : public USaveGame
{
    GENERATED_BODY()

  public:
    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString ProfileId;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString AnonymousId;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString AuthenticationType;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    uint32 UserIndex;

    UBrainCloudSave();
};