// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "Core.h"
#include "Modules/ModuleInterface.h"

/**
* Online subsystem module class  (BrainCloud Implementation)
* Code related to the loading of the BrainCloud module
*/
class FOnlineSubsystemBrainCloudModule : public IModuleInterface
{
private:

    /** Class responsible for creating instance(s) of the subsystem */
    class FOnlineFactoryBrainCloud* BrainCloudFactory;

public:

    FOnlineSubsystemBrainCloudModule() :
        BrainCloudFactory(NULL)
    {}

    virtual ~FOnlineSubsystemBrainCloudModule() {}

    // IModuleInterface

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    virtual bool SupportsDynamicReloading() override
    {
        return false;
    }

    virtual bool SupportsAutomaticShutdown() override
    {
        return false;
    }
};



