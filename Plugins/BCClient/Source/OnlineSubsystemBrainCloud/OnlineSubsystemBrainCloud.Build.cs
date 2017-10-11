// Copyright 2016 bitHeads, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class OnlineSubsystemBrainCloud : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

#if WITH_FORWARDED_MODULE_RULES_CTOR
    public OnlineSubsystemBrainCloud(ReadOnlyTargetRules Target) : base(Target)
#else
    public OnlineSubsystemBrainCloud(TargetInfo Target)
#endif
    {
        Definitions.Add("ONLINESUBSYSTEMBRAINCLOUD_PACKAGE=1");

        PrivateIncludePaths.AddRange(
            new string[] {
                        "OnlineSubsystemBrainCloud/Private",
                        "OnlineSubsystemBrainCloud/Private/OnlineCallbacks"
                    });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "Sockets",
                    "OnlineSubsystem",
                    "OnlineSubsystemUtils",
                    "Json",
                    "JsonUtilities",                    
                    "BCClientPlugin",
                    "HTTP"
                });
    }
}

