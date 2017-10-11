// Copyright 2016 bitHeads, Inc. All Rights Reserved.

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
