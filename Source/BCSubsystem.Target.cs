// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BCSubsystemTarget : TargetRules
{
    public BCSubsystemTarget(TargetInfo Target) : base(Target)
    {
		Type = TargetType.Game;
        ExtraModuleNames.AddRange(new string[] { "BCSubsystem" });
        // use this compiler flag for Xcode 14 (Apple clang version 14.0.0)
        // commandline option to avoid errors in Unreal source
        // not available in Xcode 13.2 or less (Apple clang version 13.0.0)
        if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            bOverrideBuildEnvironment = true;
            AdditionalCompilerArguments = "-Wno-unused-but-set-variable";
        }
}
