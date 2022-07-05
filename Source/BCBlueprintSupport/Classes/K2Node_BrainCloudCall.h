// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "Editor/BlueprintGraph/Classes/K2Node_BaseAsyncTask.h"
#include "K2Node_BrainCloudCall.generated.h"

// This node is a latent brainCloud client call (handles scanning all UBCBlueprintCallProxyBase classes for static factory calls)
UCLASS()
class UK2Node_BrainCloudCall : public UK2Node_BaseAsyncTask
{
    GENERATED_UCLASS_BODY()
    
    // UK2Node interface
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    // End of UK2Node interface
};
