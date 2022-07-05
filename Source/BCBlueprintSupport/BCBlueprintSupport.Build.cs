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
        PrivatePCHHeaderFile = "Private/BCBlueprintSupportPrivatePCH.h";
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        MinFilesUsingPrecompiledHeaderOverride = 1;

#if WITH_FORWARDED_MODULE_RULES_CTOR
    #if UE_4_23_OR_EARLIER
        bFasterWithoutUnity=true;
    #if UE_4_24_OR_LATER
        bUseUnity=true;
    #endif
    #endif
#endif

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
