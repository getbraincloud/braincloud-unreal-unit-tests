// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "OnlineSubsystemBrainCloudModule.h"
#include "OnlineSubsystemBrainCloudPrivatePCH.h"
#include "OnlineSubsystemBrainCloud.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FOnlineSubsystemBrainCloudModule, OnlineSubsystemBrainCloud);

/**
* Class responsible for creating instance(s) of the subsystem
*/
class FOnlineFactoryBrainCloud : public IOnlineFactory
{
public:

    FOnlineFactoryBrainCloud() {}
    virtual ~FOnlineFactoryBrainCloud() {}

    virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName)
    {
        FOnlineSubsystemBrainCloudPtr OnlineSub = MakeShareable(new FOnlineSubsystemBrainCloud("BCSubsystem", InstanceName));
        if (OnlineSub->IsEnabled())
        {
            if (!OnlineSub->Init())
            {
                UE_LOG_ONLINE(Warning, TEXT("BrainCloud API failed to initialize!"));
                OnlineSub->Shutdown();
                OnlineSub = NULL;
            }
        }
        else
        {
            UE_LOG_ONLINE(Warning, TEXT("BrainCloud API disabled!"));
            OnlineSub->Shutdown();
            OnlineSub = NULL;
        }

        return OnlineSub;
    }
};

void FOnlineSubsystemBrainCloudModule::StartupModule()
{
    UE_LOG(LogOnline, Log, TEXT("BrainCloud Startup!"));
    BrainCloudFactory = new FOnlineFactoryBrainCloud();

    // Create and register our singleton factory with the main online subsystem for easy access
    FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
    OSS.RegisterPlatformService(BRAINCLOUD_SUBSYSTEM, BrainCloudFactory);
}

void FOnlineSubsystemBrainCloudModule::ShutdownModule()
{
    FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
    OSS.UnregisterPlatformService(BRAINCLOUD_SUBSYSTEM);

    delete BrainCloudFactory;
    BrainCloudFactory = NULL;
}
