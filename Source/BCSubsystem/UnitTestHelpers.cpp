// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCSubsystem.h"
#include "UnitTestHelpers.h"
#include "BrainCloudClient.h"

UUnitTestHelpers::UUnitTestHelpers(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

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
				params.ServerUrl.TrimEnd();
			}
			else if (line.StartsWith("appId"))
			{
				line.Split(TEXT("="), nullptr, &params.AppId);
				params.AppId.TrimEnd();
			}
			else if (line.StartsWith("secret"))
			{
				line.Split(TEXT("="), nullptr, &params.Secret);
				params.Secret.TrimEnd();
			}
			else if (line.StartsWith("version"))
			{
				line.Split(TEXT("="), nullptr, &params.Version);
				params.Version.TrimEnd();
			}
			else if (line.StartsWith("childAppId"))
			{
				line.Split(TEXT("="), nullptr, &params.ChildAppId);
				params.ChildAppId.TrimEnd();
			}
			else if (line.StartsWith("parentLevelName"))
			{
				line.Split(TEXT("="), nullptr, &params.ParentLevelName);
				params.ParentLevelName.TrimEnd();
			}
			else if (line.StartsWith("peerName"))
			{
				line.Split(TEXT("="), nullptr, &params.PeerName);
				params.PeerName.TrimEnd();
			}
		}
	}
	else UE_LOG(LogTemp, Error, TEXT("Could not find ids.txt file at %s"), *filePath);

	return params;
}