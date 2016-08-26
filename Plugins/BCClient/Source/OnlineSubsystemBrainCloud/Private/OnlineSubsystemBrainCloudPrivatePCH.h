// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "OnlineSubsystemBrainCloudModule.h"
#include "OnlineSubsystemModule.h"
#include "OnlineSubsystem.h"
#include "ModuleManager.h"

#define INVALID_INDEX -1

/** FName declaration of BrainCloud subsystem */
#define BRAINCLOUD_SUBSYSTEM FName(TEXT("brainCloud"))
/** URL Prefix when using BrainCloud socket connection */
#define BRAINCLOUD_URL_PREFIX TEXT("brainCloud.")

/** pre-pended to all BrainCloud logging */
#undef ONLINE_LOG_PREFIX
#define ONLINE_LOG_PREFIX TEXT("brainCloud: ")


