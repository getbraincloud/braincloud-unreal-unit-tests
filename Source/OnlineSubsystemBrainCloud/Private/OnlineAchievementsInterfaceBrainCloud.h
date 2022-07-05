// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "Interfaces/OnlineAchievementsInterface.h"
#include "OnlineSubsystemBrainCloudPackage.h"

/**
 *  IOnlineAchievements - Interface class for acheivements
 */
class FOnlineAchievementsBrainCloud : public IOnlineAchievements
{
private:

    /** Structure describing a Null achievement */
    struct FOnlineAchievementBrainCloud : public FOnlineAchievement, public FOnlineAchievementDesc
    {
        /** Whether achievement info has been read from BrainCloud */
        bool bReadFromBrainCloud;

        /** Returns debugging string to print out achievement info */
        FString ToDebugString() const
        {
            return FString::Printf(TEXT("Achievement:{%s},  Description:{%s}, bReadFromBrainCloud=%s"),
                *FOnlineAchievement::ToDebugString(),
                *FOnlineAchievementDesc::ToDebugString(),
                bReadFromBrainCloud ? TEXT("true") : TEXT("false")
                );
        }
    };

    /**
     * A helper class for configuring achievements in ini
     */
    struct BrainCloudAchievementsConfig
    {
        /**
         * Create a config using the default values:
         * IniName - BrainCloudClient
         */
        BrainCloudAchievementsConfig(FString iniName)
            : IniName(iniName)
            , SectionName(TEXT("BrainCloud.Achievements"))
        {
        }

        /** Returns empty string if couldn't read */
        FString GetKey(const FString& KeyName)
        {
            FString Result;
            if (!GConfig->GetString(*SectionName, *KeyName, Result, IniName))
            {
                return TEXT("");    // could just return Result, but being explicit is better?!
            }
            return Result;
        }

        bool ReadAchievements(TArray<FOnlineAchievementBrainCloud> & OutArray)
        {
            OutArray.Empty();
            int NumAchievements = 0;

            for (;; ++NumAchievements)
            {
                FString Id = GetKey(FString::Printf(TEXT("Achievement_%d_Id"), NumAchievements));
                if (Id.IsEmpty())
                {
                    break;
                }

                FOnlineAchievementBrainCloud NewAch;
                NewAch.Id = Id;
                NewAch.Progress = 0.0;
                NewAch.bReadFromBrainCloud = false;

                OutArray.Add(NewAch);
            }

            return NumAchievements > 0;
        }


        /** Ini file name to find the config values */
        FString IniName;
        /** Section name for Null */
        FString SectionName;
    };

    /** Reference to the owning subsystem */
    class FOnlineSubsystemBrainCloud* Subsystem;

    /** hide the default constructor, we need a reference to our OSS */
    FOnlineAchievementsBrainCloud() {};

    /** Mapping of players to their achievements */
    TMap<FUniqueNetIdString, TArray<FOnlineAchievement>> PlayerAchievements;

    /** Cached achievement descriptions for an Id */
    TMap<FString, FOnlineAchievementDesc> AchievementDescriptions;

    /** Cached achievements (not player-specific) */
    TArray<FOnlineAchievementBrainCloud> Achievements;

    /** Whether we have achievements specified in the .ini */
    bool bHaveConfiguredAchievements;

    /** Initializes achievements from config. Returns true if there is at least one achievement */
    bool ReadAchievementsFromConfig();

    void OnWriteAchievementsComplete(bool bWasSuccessful, const FString& jsonData, const FUniqueNetId& PlayerId, FOnlineAchievementsWritePtr& WriteObject, const FOnAchievementsWrittenDelegate& Delegate);
    void OnQueryAchievementsComplete(bool bWasSuccessful, const FString& jsonData, const FUniqueNetId* PlayerId, FOnQueryAchievementsCompleteDelegate& Delegate);
    void OnQueryAchievementDescComplete(bool bWasSuccessful, const FString& jsonData, const FUniqueNetId* PlayerId, FOnQueryAchievementsCompleteDelegate& Delegate);

    /* Helper to convert an achievement JSON object to a FOnlineAchievementBrainCloud */
    bool getAchievementFromJson(const TSharedPtr<FJsonObject>& jsonObj, FOnlineAchievementBrainCloud& achievementOut);

public:

    /**
     * Constructor
     *
     * @param InSubsystem - A reference to the owning subsystem
     */
    FOnlineAchievementsBrainCloud(class FOnlineSubsystemBrainCloud* InSubsystem);

    /**
     * Default destructor
     */
    virtual ~FOnlineAchievementsBrainCloud(){}

    // Begin IOnlineAchievements interface
    virtual void WriteAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate = FOnAchievementsWrittenDelegate()) override;
    virtual void QueryAchievements(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) override;
    virtual void QueryAchievementDescriptions(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) override;
    virtual EOnlineCachedResult::Type GetCachedAchievement(const FUniqueNetId& PlayerId, const FString& AchievementId, FOnlineAchievement& OutAchievement) override;
    virtual EOnlineCachedResult::Type GetCachedAchievements(const FUniqueNetId& PlayerId, TArray<FOnlineAchievement> & OutAchievements) override;
    virtual EOnlineCachedResult::Type GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc& OutAchievementDesc) override;

#if !UE_BUILD_SHIPPING
    virtual bool ResetAchievements(const FUniqueNetId& PlayerId) override;
#endif // !UE_BUILD_SHIPPING
    // End IOnlineAchievements interface
};
