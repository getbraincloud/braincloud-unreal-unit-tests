// Fill out your copyright notice in the Description page of Project Settings.

#include "BCSubsystem.h"
#include "TitleFileSubsystemTestActor.h"
#include "BrainCloudClient.h"

// Sets default values
ATitleFileSubsystemTestActor::ATitleFileSubsystemTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;	
}

// Called every frame
void ATitleFileSubsystemTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void ATitleFileSubsystemTestActor::BeginPlay()
{
	Super::BeginPlay();
	/////////////////////////////////////////////////////
    //#pragma warning(suppress: 4996)
	//BrainCloudClient::getInstance()->enableLogging(true);
	/////////////////////////////////////////////////////

	_subsystem = IOnlineSubsystem::Get();
	if (_subsystem)
	{
		_identity = _subsystem->GetIdentityInterface();
		_titleFile = _subsystem->GetTitleFileInterface();
	}

	if (!_subsystem)
	{
		UE_LOG(LogTemp, Log, TEXT("Subsystem null in ATitleFileSubsystemTestActor"));
		return;
	}

	_identity->OnLoginCompleteDelegates->AddUObject(this, &ATitleFileSubsystemTestActor::LoginCallback);

	//TODO Jon
	_titleFile->OnEnumerateFilesCompleteDelegates.AddUObject(this, &ATitleFileSubsystemTestActor::OnEnumerateFilesCompleteCallback);
	_titleFile->OnReadFileCompleteDelegates.AddUObject(this, &ATitleFileSubsystemTestActor::OnReadFileCompleteCallback);

	_identity->Login(0, FOnlineAccountCredentials("BrainCloud", "UnrealUser2", "UnrealUser2"));
}

void ATitleFileSubsystemTestActor::LoginCallback(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), (_identity->GetLoginStatus(0) == ELoginStatus::LoggedIn) ? TEXT("true") : TEXT("false"));

	TArray<TSharedRef<const FUniqueNetId>> ids;
	ids.Add(UserId.AsShared());

	_titleFile->EnumerateFiles();
}

void ATitleFileSubsystemTestActor::OnEnumerateFilesCompleteCallback(bool wasSuccess, const FString& fileName)
{
	UE_LOG(LogTemp, Log, TEXT("EumerateMessages: %s"), wasSuccess ? TEXT("true") : TEXT("false"));

	TArray<FCloudFileHeader> headers;
	_titleFile->GetFileList(headers);
	_titleFile->ReadFile(headers[0].DLName);
}

void ATitleFileSubsystemTestActor::OnReadFileCompleteCallback(bool wasSuccess, const FString& fileName)
{
	UE_LOG(LogTemp, Log, TEXT("Read File: %s"), wasSuccess ? TEXT("true") : TEXT("false"));

	UE_LOG(LogTemp, Log, TEXT("GetFileContents"));
	TArray<uint8> fileBin;
	_titleFile->GetFileContents(fileName, fileBin);

	UE_LOG(LogTemp, Log, TEXT("DeleteCachedFiles"));

	_titleFile->DeleteCachedFiles(true);

	UE_LOG(LogTemp, Log, TEXT("ClearFile"));

	_titleFile->ClearFile(fileName);

	UE_LOG(LogTemp, Log, TEXT("ClearFiles"));

	_titleFile->ClearFiles();
}
