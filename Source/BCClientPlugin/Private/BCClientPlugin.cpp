// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"

class FBCClientPlugin : public IBCClientPlugin
{
    /** IModuleInterface implementation */
    virtual void StartupModule() override
    {
        // @HACK Force classes to be compiled on shipping build
    }

    virtual void ShutdownModule() override
    {
    }
};

IMPLEMENT_MODULE(FBCClientPlugin, BCClientPlugin)

DEFINE_LOG_CATEGORY(LogBrainCloud);
DEFINE_LOG_CATEGORY(LogBrainCloudComms);
DEFINE_LOG_CATEGORY(LogBrainCloudRelayComms);
