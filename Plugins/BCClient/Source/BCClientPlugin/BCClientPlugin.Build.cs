// Copyright 2018 bitHeads, Inc. All Rights Reserved.

using System;
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
        PrivatePCHHeaderFile = "Private/BCClientPluginPrivatePCH.h";
        
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

        // win64
        PublicDefinitions.Add("PLATFORM_UWP=0");
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PrivateDependencyModuleNames.Add("zlib");
            PrivateDependencyModuleNames.Add("OpenSSL");
            PublicIncludePaths.Add(Path.Combine(ModulePath,"ThirdParty/include/Win64"));

            PublicLibraryPaths.AddRange(
                new string[] {
                    Path.Combine(ModulePath, "ThirdParty/lib/Win64"),
                });

            string[] StaticLibrariesX64 = new string[] {
                Path.Combine(ModulePath,"ThirdParty/lib/Win64/websockets_static.lib"),
            };

            foreach (string Lib in StaticLibrariesX64)
            {
                PublicAdditionalLibraries.Add(Lib);
            }
        }
        //win32
        else if (Target.Platform == UnrealTargetPlatform.Win32)
        {
            PrivateDependencyModuleNames.Add("zlib");
            PrivateDependencyModuleNames.Add("OpenSSL");
            PublicIncludePaths.Add(Path.Combine(ModulePath,"ThirdParty/include/Win32"));

            PublicLibraryPaths.AddRange(
                new string[] {
                    Path.Combine(ModulePath, "ThirdParty/lib/Win32"),
                });

            string[] StaticLibrariesX32 = new string[] {
                Path.Combine(ModulePath,"ThirdParty/lib/Win32/websockets_static.lib"),
            };

            foreach (string Lib in StaticLibrariesX32)
            {
                PublicAdditionalLibraries.Add(Lib);
            }
        }
        else if(Target.Platform == UnrealTargetPlatform.HTML5)
        {
            PublicLibraryPaths.AddRange(
                new string[] {
                    Path.Combine(ModulePath, "ThirdParty/lib/HTML5"),
                });

            string[] StaticLibrariesHTML5 = new string[] {
                Path.Combine(ModulePath,"ThirdParty/lib/HTML5/WebSocket.js"),
            };

            foreach (string Lib in StaticLibrariesHTML5)
            {
                PublicAdditionalLibraries.Add(Lib);
            }
        }
        else if(Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicIncludePaths.Add(Path.Combine(ModulePath,"ThirdParty/include/Mac"));
            PublicLibraryPaths.AddRange(
                new string[] {
                    Path.Combine(ModulePath, "ThirdParty/lib/Mac"),
                });

            string[] StaticLibrariesMac = new string[] {
                 Path.Combine(ModulePath,"ThirdParty/lib/Mac/libwebsockets.a"),
                 Path.Combine(ModulePath,"ThirdParty/lib/Mac/libssl.a"),
                 Path.Combine(ModulePath,"ThirdParty/lib/Mac/libcrypto.a"),
            };

            foreach (string Lib in StaticLibrariesMac)
            {
                PublicAdditionalLibraries.Add(Lib);
            }
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PrivateDependencyModuleNames.Add("OpenSSL");
            PublicIncludePaths.Add(Path.Combine(ModulePath,"ThirdParty/include/Linux"));
            PublicLibraryPaths.AddRange(
                new string[] {
                    Path.Combine(ModulePath, "ThirdParty/lib/Linux"),
                });

             string[] StaticLibrariesLinux = new string[] {
                 Path.Combine(ModulePath,"ThirdParty/lib/Linux/libwebsockets.a"),
            };
            
            foreach (string Lib in StaticLibrariesLinux)
            {
                PublicAdditionalLibraries.Add(Lib);
            }
        }
        else if(Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicIncludePaths.Add(Path.Combine(ModulePath,"ThirdParty/include/IOS"));

            PublicLibraryPaths.AddRange(
                new string[] {
                    Path.Combine(ModulePath, "ThirdParty/lib/IOS"),
                });

            string[] StaticLibrariesIOS = new string[] {
                 Path.Combine(ModulePath,"ThirdParty/lib/IOS/libwebsockets.a"),
                 Path.Combine(ModulePath,"ThirdParty/lib/IOS/libssl.a"),
                 Path.Combine(ModulePath,"ThirdParty/lib/IOS/libcrypto.a"),
            };

            foreach (string Lib in StaticLibrariesIOS)
            {
                PublicAdditionalLibraries.Add(Lib);
            }
        }
        else if(Target.Platform == UnrealTargetPlatform.Android && Target.Architecture == "ARMv7")
        {
            //TODO : find a way to get the engine path with UnrealBuildTool - note, have tried Fpaths and BuildConfiguration.RelativeEnginePath() and 
                //DirectoryReference.GetCurrentDirectory(). We want to use the UE4 shipped socket lib, otherwise the static ones we save may get old. 
                //libWebSockets for Android are located in the Engine here "/Source/ThirdParty/libWebSockets/libwebsockets/lib/Android"
            //string pathToAndroidLibWebSockets = BuildConfiguration.RelativeEnginePath() + "/Source/ThirdParty/libWebSockets/libwebsockets/lib/Android"; 
            PublicIncludePaths.Add(Path.Combine(ModulePath, "ThirdParty/include/Android/"));

            //we have several types of targets. Need to separate those targets when building so that the right target builds with the right libWebSockets lib

            //////////////////////////////////////////////////////////////////////////////

            //so we want to build ARM_7 and ARM64 separately by default
            string folderDir = "ThirdParty/lib/Android/ARMv7"; //Default to ARMv7
            string staticLibLoc = "ThirdParty/lib/Android/ARMv7/libwebsockets.a"; //ARMv7 Location
            
            if(Target.Architecture == "ARM64")
            {
                folderDir = "ThirdParty/lib/Android/ARM64";
                staticLibLoc = "ThirdParty/lib/Android/ARM64/libwebsockets.a"; //ARM64 location
            }

            PublicLibraryPaths.AddRange(
                new string[] {
                    Path.Combine(ModulePath, folderDir),
                });

            string[] StaticLibrariesAndroid = new string[] {
                    Path.Combine(ModulePath, staticLibLoc),
            };

            foreach (string Lib in StaticLibrariesAndroid)
            {
                PublicAdditionalLibraries.Add(Lib);
            }

            //////////////////////////////////////////////////////////////////////////////////////////////

            //string folderDir = "ThirdParty/lib/Android/";
            //string staticLibLoc = "ThirdParty/lib/Android/ARMv7/libwebsockets.a"; //ARMv7 Location

            //ARMv7
            // PublicLibraryPaths.AddRange(
            //     new string[] {
            //         Path.Combine(ModulePath, folderDir + "ARMv7"),
            // });

            // string[] StaticLibrariesAndroidARMv7 = new string[] {
            //         Path.Combine(ModulePath, "ThirdParty/lib/Android/ARMv7/libwebsockets.a"),
            // };

            // foreach (string Lib in StaticLibrariesAndroidARMv7)
            // {
            //     PublicAdditionalLibraries.Add(Lib);
            // }

            // //ARM64
            // PublicLibraryPaths.AddRange(
            //     new string[] {
            //         Path.Combine(ModulePath, folderDir + "ARM64"),
            // });

            // string[] StaticLibrariesAndroidARM64 = new string[] {
            //         Path.Combine(ModulePath, "ThirdParty/lib/Android/ARM64/libwebsockets.a"),
            // };

            // foreach (string Lib in StaticLibrariesAndroidARM64)
            // {
            //     PublicAdditionalLibraries.Add(Lib);
            // }

        }

        else if(Target.Platform == UnrealTargetPlatform.Android && Target.Architecture == "ARM64")
        {
            PublicIncludePaths.Add(Path.Combine(ModulePath, "ThirdParty/include/Android/"));

            //so we want to build ARM_7 and ARM64 separately by default
            string folderDir = "ThirdParty/lib/Android/ARM64"; //Default to ARMv7
            string staticLibLoc = "ThirdParty/lib/Android/ARM64/libwebsockets.a"; //ARMv7 Location

            PublicLibraryPaths.AddRange(
                new string[] {
                    Path.Combine(ModulePath, folderDir),
                });

            string[] StaticLibrariesAndroid = new string[] {
                    Path.Combine(ModulePath, staticLibLoc),
            };

            foreach (string Lib in StaticLibrariesAndroid)
            {
                PublicAdditionalLibraries.Add(Lib);
            }
        }
    }
}
