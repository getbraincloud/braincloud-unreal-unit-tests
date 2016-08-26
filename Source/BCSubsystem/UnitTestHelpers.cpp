// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCSubsystem.h"

#include "BrainCloudClient.h"
#include "UnitTestHelpers.h"

UUnitTestHelpers::UUnitTestHelpers(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FBrainCloudInitParams UUnitTestHelpers::InitializeFromFile()
{
	FBrainCloudInitParams params;

	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString projectDir = FPaths::GameDir();
	FString filePath = FPaths::Combine(*FPaths::GameDir(), TEXT("ids.txt"));

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
				params.ServerUrl.TrimTrailing();
			}
			else if (line.StartsWith("appId"))
			{
				line.Split(TEXT("="), nullptr, &params.AppId);
				params.AppId.TrimTrailing();
			}
			else if (line.StartsWith("secret"))
			{
				line.Split(TEXT("="), nullptr, &params.Secret);
				params.Secret.TrimTrailing();
			}
			else if (line.StartsWith("version"))
			{
				line.Split(TEXT("="), nullptr, &params.Version);
				params.Version.TrimTrailing();
			}
			else if (line.StartsWith("childAppId"))
			{
				line.Split(TEXT("="), nullptr, &params.ChildAppId);
				params.ChildAppId.TrimTrailing();
			}
			else if (line.StartsWith("parentLevelName"))
			{
				line.Split(TEXT("="), nullptr, &params.ParentLevelName);
				params.ParentLevelName.TrimTrailing();
			}
		}
	}
	else UE_LOG(LogTemp, Error, TEXT("Could not find ids.txt file at %s"), *filePath);

	return params;
}