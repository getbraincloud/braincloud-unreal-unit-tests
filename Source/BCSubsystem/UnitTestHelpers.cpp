// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCSubsystem.h"
#include "UnitTestHelpers.h"
#include "BrainCloudClient.h"
#include "BrainCloudWrapper.h"
#include "ids.h"

UUnitTestHelpers::UUnitTestHelpers(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FBrainCloudInitParams UUnitTestHelpers::InitializeFromHeader()
{
	FBrainCloudInitParams params;

    // initialize from ids.h file
    params.ServerUrl = BRAINCLOUD_SERVER_URL;
    params.Secret = BRAINCLOUD_APP_SECRET;
    params.AppId = BRAINCLOUD_APP_ID;
	params.Version = BRAINCLOUD_APP_VERSION;
	params.ChildAppId = BRAINCLOUD_CHILD_APP_ID;
	params.ParentLevelName = BRAINCLOUD_PARENT_LEVEL_NAME;
	params.PeerName= BRAINCLOUD_PEER_NAME;

    // fall back on environment variables if not set in ids.h
    if(params.AppId==""){
        char* env = getenv("BC_CLIENTUNIT_APP_ID");
        if(env != NULL)
            params.AppId = env;
    }
    
    if(params.ServerUrl==""){
        char* env = getenv("BC_BRAINCLOUD_SERVER_URL");
        if(env != NULL)
            params.ServerUrl = env;
    }
    
    if(params.Secret==""){
        char* env = getenv("BC_CLIENTUNIT_APP_SECRET");
        if(env != NULL)
            params.Secret = env;
    }

    if(params.ChildAppId==""){
        char* env = getenv("BC_CLIENTUNIT_CHILD_APP_ID");
        if(env != NULL)
            params.ChildAppId = env;
    }
    
    return params;
}
// deprecated: use ids.h and InitializeFromHeader above
// this function exists because some Old Tests call it, the file ids.txt no longer exists in github.
FBrainCloudInitParams UUnitTestHelpers::InitializeFromFile()
{
	FBrainCloudInitParams params;

	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString projectDir = FPaths::ProjectDir();
	FString filePath = FPaths::Combine(*FPaths::ProjectDir(), TEXT("ids.txt"));

	if (platformFile.FileExists(*filePath))
	{
		FString file;
		FFileHelper::LoadFileToString(file, *filePath);

		TArray<FString> lines;
		file.ParseIntoArray(lines, TEXT("\n"), true);

		for (int32 i = 0; i < lines.Num(); i++)
		{
			FString line = lines[i];

			if (line.StartsWith("serverUrl"))
			{
				line.Split(TEXT("="), nullptr, &params.ServerUrl);
				params.ServerUrl.TrimEndInline();
			}
			else if (line.StartsWith("appId"))
			{
				line.Split(TEXT("="), nullptr, &params.AppId);
				params.AppId.TrimEndInline();
			}
			else if (line.StartsWith("secret"))
			{
				line.Split(TEXT("="), nullptr, &params.Secret);
				params.Secret.TrimEndInline();
			}
			else if (line.StartsWith("version"))
			{
				line.Split(TEXT("="), nullptr, &params.Version);
				params.Version.TrimEndInline();
			}
			else if (line.StartsWith("childAppId"))
			{
				line.Split(TEXT("="), nullptr, &params.ChildAppId);
				params.ChildAppId.TrimEndInline();
			}
			else if (line.StartsWith("parentLevelName"))
			{
				line.Split(TEXT("="), nullptr, &params.ParentLevelName);
				params.ParentLevelName.TrimEndInline();
			}
			else if (line.StartsWith("peerName"))
			{
				line.Split(TEXT("="), nullptr, &params.PeerName);
				params.PeerName.TrimEndInline();
			}
		}
	}
	else UE_LOG(LogTemp, Error, TEXT("Could not find ids.txt file at %s"), *filePath);

	return params;
}
