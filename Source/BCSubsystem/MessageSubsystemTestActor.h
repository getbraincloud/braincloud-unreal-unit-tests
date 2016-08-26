// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "OnlineSubsystem.h"
#include "OnlineIdentityInterface.h"
#include "OnlineMessageInterface.h"

#include "MessageSubsystemTestActor.generated.h"

UCLASS()
class BCSUBSYSTEM_API AMessageSubsystemTestActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMessageSubsystemTestActor();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    void LoginCallback(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

    void SendMessageCallback(int userNum, bool wasSuccess, const FString& errorStr);
	void EumerateMessagesCallback(int userNum, bool wasSuccess, const FString& errorStr);
	void ReadMessageCallback(int userNum, bool wasSuccess, const FUniqueMessageId& messageId, const FString& errorStr);
	void DeleteMessageCallback(int userNum, bool wasSuccess, const FUniqueMessageId& messageId, const FString& errorStr);
    
    TSharedPtr <const FUniqueNetId> _id;
    IOnlineSubsystem* _subsystem;
    IOnlineIdentityPtr _identity;
    IOnlineMessagePtr _message;
};
