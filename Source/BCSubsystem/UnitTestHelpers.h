// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "UnitTestHelpers.generated.h"

UCLASS(MinimalAPI)
class UUnitTestHelpers : public UObject
{
	GENERATED_BODY()

public:
	UUnitTestHelpers(const FObjectInitializer& ObjectInitializer);

};
