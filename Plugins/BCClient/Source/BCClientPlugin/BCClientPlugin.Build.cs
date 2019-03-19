// Copyright 2018 bitHeads, Inc. All Rights Reserved.

//Uncomment the android architecture you are building for.
//#define ANDROID_ARM64
#define ANDROID_ARMv7
//#define ANDROID_x86
//#define ANDROID_x86_64

using System.Collections.Generic;
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
            PublicIncludePaths.Add(Path.Combine(ModulePath, "ThirdParty/include/Win64"));

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
            PublicIncludePaths.Add(Path.Combine(ModulePath, "ThirdParty/include/Win32"));

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
        else if (Target.Platform == UnrealTargetPlatform.HTML5)
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
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicIncludePaths.Add(Path.Combine(ModulePath, "ThirdParty/include/Mac"));
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
            PublicIncludePaths.Add(Path.Combine(ModulePath, "ThirdParty/include/Linux"));
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
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicIncludePaths.Add(Path.Combine(ModulePath, "ThirdParty/include/IOS"));

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
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicIncludePaths.Add(Path.Combine(ModulePath, "ThirdParty/include/Android/"));

            string folderDir = "ThirdParty/lib/Android/";
            string libDir = "ThirdParty/lib/Android/";
            string libName = "/libwebsockets.a";
            string buildScript = "BCClientPlugin.Build.cs";

            List<string> StaticLibrariesAndroid = new List<string>();
            // multiple supported arch types
#if ANDROID_ARM64
            System.Console.WriteLine(Path.Combine(ModulePath, buildScript) + " building for ARM64");
            PublicLibraryPaths.Add(Path.Combine(ModulePath, folderDir + "ARM64"));
            StaticLibrariesAndroid.Add(Path.Combine(ModulePath, libDir + "ARM64" + libName));
#endif

#if ANDROID_ARMv7
            System.Console.WriteLine(Path.Combine(ModulePath, buildScript) + " building for ARMv7");
            PublicLibraryPaths.Add(Path.Combine(ModulePath, folderDir + "ARMv7"));
            StaticLibrariesAndroid.Add(Path.Combine(ModulePath, libDir + "ARMv7" + libName));
#endif

#if ANDROID_x86
            System.Console.WriteLine(Path.Combine(ModulePath, buildScript) + " building for x86");
            PublicLibraryPaths.Add(Path.Combine(ModulePath, folderDir + "x86"));
            StaticLibrariesAndroid.Add(Path.Combine(ModulePath, libDir + "x86" + libName));
#endif

#if ANDROID_x86_64
            System.Console.WriteLine(Path.Combine(ModulePath, buildScript) + " building for x86_64");
            PublicLibraryPaths.Add(Path.Combine(ModulePath, folderDir + "x64"));
            StaticLibrariesAndroid.Add(Path.Combine(ModulePath, libDir + "x64" + libName));
#endif

            //if StaticLibraries has nothing in it, none of their libraries matched up, so we'll use the default ARM64 libWebSockets, 
            //and send them a message telling them that they are using an unsupported library. 
            if (StaticLibrariesAndroid.Count == 0)
            {
                System.Console.WriteLine("UNSUPPORTED ARCHITECTURE - Go to " + Path.Combine(ModulePath, buildScript) + " and uncomment #define for the architecture you are trying to build apk for.");
                System.Console.WriteLine(Path.Combine(ModulePath, buildScript) + " building for default ARMv7");
                //unreal default ARMv7 paths.
                PublicLibraryPaths.Add(Path.Combine(ModulePath, folderDir + "ARMv7"));
                StaticLibrariesAndroid.Add(Path.Combine(ModulePath, libDir + "ARMv7" + libName));
            }

            if (StaticLibrariesAndroid.Count > 1)
            {
                System.Console.WriteLine("Can only build an apk for one architecture at a time, if you need multiple apks, build the architectures separately.");
                System.Console.WriteLine("Go to " + Path.Combine(ModulePath, buildScript) + " and uncomment #define for the architecture you are trying to build apk for. Then make sure that in your editor or Engine.ini, that only one architecture is set to true");
            }

            foreach (string Lib in StaticLibrariesAndroid)
            {
                PublicAdditionalLibraries.Add(Lib);
            }
        }
    }
}
