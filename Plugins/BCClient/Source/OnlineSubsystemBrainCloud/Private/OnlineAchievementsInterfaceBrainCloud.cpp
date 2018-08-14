// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "OnlineSubsystemBrainCloudPrivatePCH.h"
#include "OnlineAchievementsInterfaceBrainCloud.h"
#include "OnlineSubsystemBrainCloud.h"
#include "BrainCloudClient.h"
#include "AchievementCallback.h"

FOnlineAchievementsBrainCloud::FOnlineAchievementsBrainCloud(class FOnlineSubsystemBrainCloud* InSubsystem)
    : Subsystem(InSubsystem)
{
    check(Subsystem);
    bHaveConfiguredAchievements = ReadAchievementsFromConfig();
}

bool FOnlineAchievementsBrainCloud::ReadAchievementsFromConfig()
{
    if (Achievements.Num() > 0)
    {
        return true;
    }

    BrainCloudAchievementsConfig Config(Subsystem->GetConfigPath());
    return Config.ReadAchievements(Achievements);
}

void FOnlineAchievementsBrainCloud::WriteAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate)
{
    if (!bHaveConfiguredAchievements)
    {
        // we don't have achievements
        UE_LOG_ONLINE(Warning, TEXT("BrainCloud achievements have not been configured in .ini"));

        WriteObject->WriteState = EOnlineAsyncTaskState::Failed;
        Delegate.ExecuteIfBound(PlayerId, false);
        return;
    }

    FUniqueNetIdString BrainCloudId(PlayerId);
    const TArray<FOnlineAchievement> * PlayerAch = PlayerAchievements.Find(BrainCloudId);
    if (NULL == PlayerAch)
    {
        // achievements haven't been read for a player
        UE_LOG_ONLINE(Warning, TEXT("BrainCloud achievements have not been read for player %s"), *PlayerId.ToString());

        WriteObject->WriteState = EOnlineAsyncTaskState::Failed;
        Delegate.ExecuteIfBound(PlayerId, false);
        return;
    }

    TArray<FString> achievements;

    const int32 AchNum = PlayerAch->Num();
    for (FStatPropertyArray::TConstIterator It(WriteObject->Properties); It; ++It)
    {
        const FString AchievementId = It.Key().ToString();
        for (int32 AchIdx = 0; AchIdx < AchNum; ++AchIdx)
        {
            if ((*PlayerAch)[AchIdx].Id == AchievementId)
            {
                float Value = 0.0f;
                It.Value().GetValue(Value);
                if (Value >= 100.0f)
                {
                    achievements.Add(AchievementId);
                    UE_LOG_ONLINE(Verbose, TEXT("Setting achievement '%s'"), *AchievementId);
                }
                break;
            }
        }
    }

    if (achievements.Num() > 0)
    {
        AchievementCallback* cb = new AchievementCallback(PlayerId, WriteObject, Delegate);
        cb->OnWriteCompleteDelegate.AddRaw(this, &FOnlineAchievementsBrainCloud::OnWriteAchievementsComplete);
        Subsystem->RegisterCallbackObject(cb);
        Subsystem->GetClient()->getGamificationService()->awardAchievements(achievements, cb);
    }
    else
    {
        WriteObject->WriteState = EOnlineAsyncTaskState::Failed;
        Delegate.ExecuteIfBound(PlayerId, false);
    }
};

void FOnlineAchievementsBrainCloud::QueryAchievements(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate)
{
    if (!bHaveConfiguredAchievements)
    {
        // we don't have achievements
        UE_LOG_ONLINE(Warning, TEXT("BrainCloud achievements have not been configured in .ini"));

        Delegate.ExecuteIfBound(PlayerId, false);
        return;
    }
    AchievementQueryCallback* cb = Subsystem->GetCallbackObject<AchievementQueryCallback>(&PlayerId, Delegate);
    cb->OnQueryCompleteDelegate.AddRaw(this, &FOnlineAchievementsBrainCloud::OnQueryAchievementsComplete);
    Subsystem->RegisterCallbackObject(cb);
    Subsystem->GetClient()->getGamificationService()->readAchievements(cb, true);
}

void FOnlineAchievementsBrainCloud::QueryAchievementDescriptions(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate)
{
    if (!bHaveConfiguredAchievements)
    {
        // we don't have achievements
        UE_LOG_ONLINE(Warning, TEXT("BrainCloud achievements have not been configured in .ini"));

        Delegate.ExecuteIfBound(PlayerId, false);
        return;
    }
    AchievementQueryCallback* cb = Subsystem->GetCallbackObject<AchievementQueryCallback>(&PlayerId, Delegate);
    cb->OnQueryCompleteDelegate.AddRaw(this, &FOnlineAchievementsBrainCloud::OnQueryAchievementDescComplete);
    Subsystem->RegisterCallbackObject(cb);
    Subsystem->GetClient()->getGamificationService()->readAchievements(cb, true);
}

EOnlineCachedResult::Type FOnlineAchievementsBrainCloud::GetCachedAchievement(const FUniqueNetId& PlayerId, const FString& AchievementId, FOnlineAchievement& OutAchievement)
{
    if (!bHaveConfiguredAchievements)
    {
        // we don't have achievements
        return EOnlineCachedResult::NotFound;
    }

    FUniqueNetIdString BrainCloudId(PlayerId);
    const TArray<FOnlineAchievement> * PlayerAch = PlayerAchievements.Find(BrainCloudId);
    if (PlayerAch == nullptr)
    {
        // achievements haven't been read for a player
        return EOnlineCachedResult::NotFound;
    }

    const int32 AchNum = PlayerAch->Num();
    for (int32 AchIdx = 0; AchIdx < AchNum; ++AchIdx)
    {
        if ((*PlayerAch)[AchIdx].Id == AchievementId)
        {
            OutAchievement = (*PlayerAch)[AchIdx];
            return EOnlineCachedResult::Success;
        }
    }

    // no such achievement
    return EOnlineCachedResult::NotFound;
};

EOnlineCachedResult::Type FOnlineAchievementsBrainCloud::GetCachedAchievements(const FUniqueNetId& PlayerId, TArray<FOnlineAchievement> & OutAchievements)
{
    if (!bHaveConfiguredAchievements)
    {
        // we don't have achievements
        return EOnlineCachedResult::NotFound;
    }

    FUniqueNetIdString BrainCloudId(PlayerId);
    const TArray<FOnlineAchievement> * PlayerAch = PlayerAchievements.Find(BrainCloudId);
    if (PlayerAch == nullptr)
    {
        // achievements haven't been read for a player
        return EOnlineCachedResult::NotFound;
    }

    OutAchievements = *PlayerAch;
    return EOnlineCachedResult::Success;
};

EOnlineCachedResult::Type FOnlineAchievementsBrainCloud::GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc& OutAchievementDesc)
{
    if (!bHaveConfiguredAchievements)
    {
        // we don't have achievements
        return EOnlineCachedResult::NotFound;
    }

    if (AchievementDescriptions.Num() == 0)
    {
        // don't have descs
        return EOnlineCachedResult::NotFound;
    }

    FOnlineAchievementDesc * AchDesc = AchievementDescriptions.Find(AchievementId);
    if (AchDesc == nullptr)
    {
        // no such achievement
        return EOnlineCachedResult::NotFound;
    }

    OutAchievementDesc = *AchDesc;
    return EOnlineCachedResult::Success;
};

void FOnlineAchievementsBrainCloud::OnWriteAchievementsComplete(bool bWasSuccessful, const FString& jsonData, const FUniqueNetId& PlayerId, FOnlineAchievementsWritePtr& WriteObject, const FOnAchievementsWrittenDelegate& Delegate)
{
    // if write completed successfully, unlock the achievements (and update their cache)
    if (bWasSuccessful)
    {
        TArray<FOnlineAchievement> * PlayerAch = PlayerAchievements.Find(FUniqueNetIdString(PlayerId));
        check(PlayerAch);   // were we writing for a non-existing player?
        if (PlayerAch != nullptr)
        {
            // treat each achievement as unlocked
            const int32 AchNum = PlayerAch->Num();
            for (FStatPropertyArray::TConstIterator It(WriteObject->Properties); It; ++It)
            {
                const FString AchievementId = It.Key().ToString();
                for (int32 AchIdx = 0; AchIdx < AchNum; ++AchIdx)
                {
                    if ((*PlayerAch)[AchIdx].Id == AchievementId)
                    {
                        // Update and trigger the callback
                        (*PlayerAch)[AchIdx].Progress = 100.0;
                        TriggerOnAchievementUnlockedDelegates(PlayerId, (*PlayerAch)[AchIdx].Id);
                        break;
                    }
                }
            }
        }
        Delegate.ExecuteIfBound(PlayerId, bWasSuccessful);
    }
    else
    {
        UE_LOG_ONLINE(Error, TEXT("Error writing achievements: %s"), *jsonData);
        Delegate.ExecuteIfBound(PlayerId, bWasSuccessful);
    }
}

void FOnlineAchievementsBrainCloud::OnQueryAchievementsComplete(bool bWasSuccessful, const FString& jsonData, const FUniqueNetId* PlayerId, FOnQueryAchievementsCompleteDelegate& Delegate)
{
    if (!bWasSuccessful)
    {
        UE_LOG_ONLINE(Warning, TEXT("OnQueryAchievementDescComplete Failed"));
        Delegate.ExecuteIfBound(*PlayerId, false);
        return;
    }

    TArray<TSharedPtr<FJsonValue>> achievements = FOnlineSubsystemBrainCloud::GetJsonData(jsonData)->GetArrayField("achievements");

    TArray<FOnlineAchievement> achievementsForPlayer;

    for (int32 i = 0; i < achievements.Num(); ++i)
    {
        TSharedPtr<FJsonObject> achievement = achievements[i]->AsObject();
        FString id = achievement->GetStringField(TEXT("id"));

        for (int32 j = 0; j < Achievements.Num(); ++j)
        {
            if (Achievements[j].Id == id) //achievement must be configured locally
            {
                FString status = achievement->GetStringField(TEXT("status"));

                FOnlineAchievementBrainCloud ach;

                if (getAchievementFromJson(achievement, ach))
                {
                    achievementsForPlayer.Add(ach);
                }
                break;
            }
        }
    }

    FUniqueNetIdString brainCloudId(*PlayerId);

    if (PlayerAchievements.Contains(brainCloudId))
    {
        PlayerAchievements.Remove(brainCloudId);
    }
    PlayerAchievements.Add(brainCloudId, achievementsForPlayer);

    Delegate.ExecuteIfBound(*PlayerId, true);
}

void FOnlineAchievementsBrainCloud::OnQueryAchievementDescComplete(bool bWasSuccessful, const FString& jsonData, const FUniqueNetId* PlayerId, FOnQueryAchievementsCompleteDelegate& Delegate)
{
    if (!bWasSuccessful)
    {
        UE_LOG_ONLINE(Warning, TEXT("OnQueryAchievementDescComplete Failed"));
        Delegate.ExecuteIfBound(*PlayerId, false);
        return;
    }

    TArray<TSharedPtr<FJsonValue>> achievements = FOnlineSubsystemBrainCloud::GetJsonData(jsonData)->GetArrayField("achievements");

    TArray<FOnlineAchievement> achievementsForPlayer;

    for (int32 i = 0; i < achievements.Num(); ++i)
    {
        TSharedPtr<FJsonObject> achievement = achievements[i]->AsObject();
        FString id = achievement->GetStringField(TEXT("id"));

        for (int32 j = 0; j < Achievements.Num(); ++i)
        {
            if (Achievements[j].Id == id)
            {
                FString status = achievement->GetStringField(TEXT("status"));

                bool invisibleUntilEarned = false;
                if (achievement->HasField(TEXT("invisibleUntilEarned")))
                    invisibleUntilEarned = achievement->GetBoolField(TEXT("invisibleUntilEarned"));

                FOnlineAchievementBrainCloud ach;

                if (getAchievementFromJson(achievement, ach))
                {
                    AchievementDescriptions.Add(Achievements[j].Id, ach);
                }
                break;
            }
        }
    }

    Delegate.ExecuteIfBound(*PlayerId, true);
}

bool FOnlineAchievementsBrainCloud::getAchievementFromJson(const TSharedPtr<FJsonObject>& jsonObj, FOnlineAchievementBrainCloud& achievementOut)
{
    FString status = "";
    FString id = "";
    FString title = "";
    FString description = "";
    bool invisibleUntilEarned = false;

    status = jsonObj->GetStringField(TEXT("status"));
    id = jsonObj->GetStringField(TEXT("id"));
    title = jsonObj->GetStringField(TEXT("title"));
    description = jsonObj->GetStringField(TEXT("description"));

    if (jsonObj->HasField(TEXT("invisibleUntilEarned")))
        invisibleUntilEarned = jsonObj->GetBoolField(TEXT("invisibleUntilEarned"));

    achievementOut.Id = id;
    achievementOut.Progress = status == TEXT("AWARDED") ? 100.0 : 0.0;
    achievementOut.bIsHidden = invisibleUntilEarned && achievementOut.Progress < 100.0;

    achievementOut.Title = FText::FromString(title);
    achievementOut.LockedDesc = FText::FromString(description);
    achievementOut.UnlockedDesc = FText::FromString(description);

    achievementOut.bReadFromBrainCloud = true;
    return true;
}

#if !UE_BUILD_SHIPPING
bool FOnlineAchievementsBrainCloud::ResetAchievements(const FUniqueNetId& PlayerId)
{
    if (!bHaveConfiguredAchievements)
    {
        // we don't have achievements
        UE_LOG_ONLINE(Warning, TEXT("No achievements have been configured"));
        return false;
    }

    FUniqueNetIdString BrainCloudId(PlayerId);
    TArray<FOnlineAchievement> * PlayerAch = PlayerAchievements.Find(BrainCloudId);
    if (NULL == PlayerAch)
    {
        // achievements haven't been read for a player
        UE_LOG_ONLINE(Warning, TEXT("Could not find achievements for player %s"), *PlayerId.ToString());
        return false;
    }

    // treat each achievement as unlocked
    const int32 AchNum = PlayerAch->Num();
    for (int32 AchIdx = 0; AchIdx < AchNum; ++AchIdx)
    {
        (*PlayerAch)[AchIdx].Progress = 0.0;
    }

    return true;
};
#endif // !UE_BUILD_SHIPPING
