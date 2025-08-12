// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class BCSubsystem : ModuleRules
{
    public BCSubsystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "BCSubsystem.h";
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "BCClientPlugin", "OnlineSubsystem", "OnlineSubsystemUtils", "Sockets" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Json", "OnlineSubsystem" });

        PublicIncludePaths.AddRange(new string[] {
            ModuleDirectory,
            Path.Combine(ModuleDirectory, "Public")
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
