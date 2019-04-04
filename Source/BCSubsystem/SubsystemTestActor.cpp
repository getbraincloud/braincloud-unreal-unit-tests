// Fill out your copyright notice in the Description page of Project Settings.

#include "BCSubsystem.h"
#include "SubsystemTestActor.h"
#include "BrainCloudClient.h"


// Sets default values
ASubsystemTestActor::ASubsystemTestActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    //PrimaryActorTick.bCanEverTick = true;

    _readObject = MakeShareable(new FOnlineLeaderboardRead());

    _achWriteObj = MakeShareable(new FOnlineAchievementsWrite());

    _subsystem = IOnlineSubsystem::Get();
    if (_subsystem)
    {
        _identity = _subsystem->GetIdentityInterface();
        _leaderboard = _subsystem->GetLeaderboardsInterface();
        _achievements = _subsystem->GetAchievementsInterface();
    }
}

// Called every frame
void ASubsystemTestActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void ASubsystemTestActor::BeginPlay()
{
    Super::BeginPlay();
	//#pragma warning(suppress: 4996)
    //BrainCloudClient::getInstance()->enableLogging(true);

    _identity->OnLoginCompleteDelegates->AddUObject(this, &ASubsystemTestActor::LoginCallback);
    _leaderboard->OnLeaderboardReadCompleteDelegates.AddUObject(this, &ASubsystemTestActor::LeaderboardCallback);

    _identity->Login(0, FOnlineAccountCredentials("BrainCloud", "UnrealUser2", "UnrealUser2"));
}

void ASubsystemTestActor::LoginCallback(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
    UE_LOG(LogTemp, Log, TEXT("%s"), (_identity->GetLoginStatus(0) == ELoginStatus::LoggedIn) ? TEXT("true") : TEXT("false"));

    _readObject->LeaderboardName = TEXT("Test");
    _readObject->SortedColumn = TEXT("score");
    new (_readObject->ColumnMetadata) FColumnMetaData(TEXT("score"), EOnlineKeyValuePairDataType::Int32);

    TArray< TSharedRef<const FUniqueNetId> > ListOfIDs;
    _id = _identity->GetUniquePlayerId(0);
    ListOfIDs.Add(_identity->GetUniquePlayerId(0).ToSharedRef());

    FOnlineLeaderboardReadRef ReadObjectRef = _readObject.ToSharedRef();
    _leaderboard->ReadLeaderboards(ListOfIDs, ReadObjectRef);
}

void ASubsystemTestActor::LeaderboardCallback(bool bWasSuccessful)
{
    TSharedPtr<const FUniqueNetId> id = _identity->GetUniquePlayerId(0);
    int32 score = 0;

    if (_readObject.IsValid())
    {
        FOnlineStatsRow* row = _readObject->FindPlayerRecord(*id.Get());

        if (row != nullptr)
        {
            FVariantData* Variant = row->Columns.Find("score");

            if (Variant != nullptr)
            {
                Variant->GetValue(score);
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("Cant get data"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Cant get player"));
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Score: %i"), score);

   
    delegates.BindUObject(this, &ASubsystemTestActor::AchievementReadCallback);

    FOnQueryAchievementsCompleteDelegate del = FOnQueryAchievementsCompleteDelegate::CreateUObject(this, &ASubsystemTestActor::AchievementReadCallback);
    _achievements->QueryAchievements(*_id, del);
}

void ASubsystemTestActor::AchievementReadCallback(const FUniqueNetId& UserId, const bool success)
{
    UE_LOG(LogTemp, Warning, TEXT("Achievements %s"), success ? TEXT("true") : TEXT("false"));
}

void ASubsystemTestActor::Test1()
{
}

void ASubsystemTestActor::Test2()
{
}

