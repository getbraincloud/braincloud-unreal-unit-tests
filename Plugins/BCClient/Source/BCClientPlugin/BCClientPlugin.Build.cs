// Copyright 2016 bitHeads, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class BCClientPlugin : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    public BCClientPlugin(TargetInfo Target)
    {
        PrivateIncludePaths.AddRange(
            new string[] {
                    "BCClientPlugin/Private",
                    "BCClientPlugin/Private/BlueprintProxies"
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
    }
}
