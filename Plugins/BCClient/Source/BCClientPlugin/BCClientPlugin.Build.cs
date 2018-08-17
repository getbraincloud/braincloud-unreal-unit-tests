// Copyright 2018 bitHeads, Inc. All Rights Reserved.

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

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDefinitions.Add("PLATFORM_UWP=0");
            PrivateDependencyModuleNames.Add("zlib");
            PrivateDependencyModuleNames.Add("OpenSSL");
            PublicIncludePaths.Add(Path.Combine(ModulePath,"ThirdParty/include/Win64"));

            PublicLibraryPaths.AddRange(
                new string[] {
                    Path.Combine(ModulePath, "ThirdParty/lib/Win64"),
                });

            string[] StaticLibrariesX64 = new string[] {
                Path.Combine(ModulePath,"ThirdParty/lib/Win64/websockets_static.lib"),
                //"libcrypto.lib",
                //"libssl.lib",
            };

            foreach (string Lib in StaticLibrariesX64)
            {
                PublicAdditionalLibraries.Add(Lib);
            }
        }
    }
}
