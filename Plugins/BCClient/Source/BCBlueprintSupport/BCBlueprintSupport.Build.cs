// Copyright 2016 bitHeads, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class BCBlueprintSupport : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    public BCBlueprintSupport(ReadOnlyTargetRules Target) : base(Target)
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
