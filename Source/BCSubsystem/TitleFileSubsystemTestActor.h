// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "OnlineSubsystem.h"
#include "OnlineIdentityInterface.h"
#include "OnlineTitleFileInterface.h"

#include "TitleFileSubsystemTestActor.generated.h"

UCLASS()
class BCSUBSYSTEM_API ATitleFileSubsystemTestActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATitleFileSubsystemTestActor();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    void LoginCallback(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

    void OnEnumerateFilesCompleteCallback(bool wasSuccess, const FString& fileName);
	void OnReadFileCompleteCallback(bool wasSuccess, const FString& fileName);
    
    TSharedPtr <const FUniqueNetId> _id;
    IOnlineSubsystem* _subsystem;
    IOnlineIdentityPtr _identity;
    IOnlineTitleFilePtr _titleFile;
};
