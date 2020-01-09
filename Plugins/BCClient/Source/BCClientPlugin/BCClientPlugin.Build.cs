// Copyright 2018 bitHeads, Inc. All Rights Reserved.

using System.Collections.Generic;
using System;
using System.IO;
using UnrealBuildTool;
public class BCClientPlugin : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

#if WITH_FORWARDED_MODULE_RULES_CTOR
    public BCClientPlugin(ReadOnlyTargetRules Target) : base(Target)
#else
    public BCClientPlugin(TargetInfo Target)
#endif
    {
        PrivatePCHHeaderFile = "Private/BCClientPluginPrivatePCH.h";

        PrivateIncludePaths.AddRange(
            new string[] {
                    Path.Combine(ModulePath,"Private"),
                    Path.Combine(ModulePath,"Private/BlueprintProxies")
                });

        PrivateDependencyModuleNames.AddRange(
            new string[]
                {
                    "JsonUtilities",
                    "HTTP"
                });

        PublicDependencyModuleNames.AddRange(
            new string[]
                {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "Json"
                });

        // win64
        PublicDefinitions.Add("PLATFORM_UWP=0");
        if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32)
        {
            PrivateDependencyModuleNames.Add("zlib");
            PublicDependencyModuleNames.Add("libWebSockets");
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {           
            PublicDependencyModuleNames.Add("libWebSockets");
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicDependencyModuleNames.Add("libWebSockets");
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicDependencyModuleNames.Add("libWebSockets");
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicDependencyModuleNames.Add("libWebSockets");
        }
        //PublicAdditionalLibraries.pu
        // else
        // {
            
        //     PublicLibraryPaths.Add(Path.Combine(ModulePath, "ThirdParty/lib/HTML5"));
        //     PublicAdditionalLibraries.Add(Path.Combine(ModulePath,"ThirdParty/lib/HTML5/WebSocket.js"));
        // }
    }
}
