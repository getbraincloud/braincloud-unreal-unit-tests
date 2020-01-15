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

        MinFilesUsingPrecompiledHeaderOverride = 1;
        //need to wrap
// #if WITH_FORWARDED_MODULE_RULES_CTOR
//     #if UE_4_24_OR_LATER
//         bUseUnity=true;
//     #else
//         bFasterWithoutUnity=true;
//     #endif
// #else
//         bFasterWithoutUnity=true;
// #endif

#if WITH_FORWARDED_MODULE_RULES_CTOR
    #if UE_4_23_OR_EARLIER
        bFasterWithoutUnity=true;
    #if UE_4_24_OR_LATER
        bUseUnity=true;
    #endif
    #endif
#endif

//bFasterWithoutUnity=true;

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
