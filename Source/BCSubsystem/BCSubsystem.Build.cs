// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BCSubsystem : ModuleRules
{
    public BCSubsystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "BCSubsystem.h";
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "BCClientPlugin", "OnlineSubsystem", "OnlineSubsystemUtils", "Sockets" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Json", "OnlineSubsystem" });
        
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
        
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemBrainCloud");
    }
}
