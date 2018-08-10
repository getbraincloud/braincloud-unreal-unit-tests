// Copyright 2018 bitHeads, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class BCBlueprintSupport : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

#if WITH_FORWARDED_MODULE_RULES_CTOR
    public BCBlueprintSupport(ReadOnlyTargetRules Target) : base(Target)
#else
    public BCBlueprintSupport(TargetInfo Target)
#endif
    {
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

        PrivateDependencyModuleNames.AddRange(
            new string[] { 
				"Core", 
				"CoreUObject", 
				"Engine",
                "BCClientPlugin",
                "UnrealEd",
                "BlueprintGraph"
			}
        );
    }
}
