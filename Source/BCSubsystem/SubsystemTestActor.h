// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "OnlineSubsystem.h"
#include "OnlineIdentityInterface.h"
#include "OnlineLeaderboardInterface.h"
#include "OnlineAchievementsInterface.h"

#include "SubsystemTestActor.generated.h"

UCLASS()
class BCSUBSYSTEM_API ASubsystemTestActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASubsystemTestActor();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    void LoginCallback(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
    void LeaderboardCallback(bool bWasSuccessful);
    void AchievementReadCallback(const FUniqueNetId& UserId, bool success);

    FOnQueryAchievementsCompleteDelegate delegates;

    void Test1();
    void Test2();
    
    TSharedPtr <const FUniqueNetId> _id;

    IOnlineSubsystem* _subsystem;
    IOnlineIdentityPtr _identity;
    IOnlineLeaderboardsPtr _leaderboard;
    IOnlineAchievementsPtr _achievements;

    bool _didFire = false;

    FOnlineLeaderboardReadPtr _readObject;
    FOnlineAchievementsWritePtr _achWriteObj;
};
