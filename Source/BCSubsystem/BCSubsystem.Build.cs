// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BCSubsystem : ModuleRules
{
    public BCSubsystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "BCSubsystem.h";
        CppStandard = CppStandardVersion.Cpp20;
        PrivateIncludePaths.Add(ModuleDirectory);
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "BCClientPlugin", "OnlineSubsystem", "OnlineSubsystemUtils", "Sockets" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Json", "OnlineSubsystem" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "AssetRegistry" });

        // Test-only engine modules do not exist in Shipping builds.
        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PublicDependencyModuleNames.Add("AutomationController");
            PrivateDependencyModuleNames.Add("FunctionalTesting");
        }
    }
}
