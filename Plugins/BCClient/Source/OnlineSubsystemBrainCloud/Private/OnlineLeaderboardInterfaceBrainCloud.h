// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Interfaces/OnlineLeaderboardInterface.h"

struct FOnlinePendingLeaderboardWrite
{
    FString LeaderboardName;
    uint64 Score;
};

class ServiceName;
class ServiceOperation;

/**
 * Interface definition for the online services leaderboard services 
 */
class FOnlineLeaderboardsBrainCloud : public IOnlineLeaderboards
{
public:
    FOnlineLeaderboardsBrainCloud(class FOnlineSubsystemBrainCloud* InSubsystem);

    virtual bool ReadLeaderboards(const TArray< TSharedRef<const FUniqueNetId> >& Players, FOnlineLeaderboardReadRef& ReadObject) override;
    virtual bool ReadLeaderboardsForFriends(int32 LocalUserNum, FOnlineLeaderboardReadRef& ReadObject) override;

// Unreal Engine Version is >= 4.16 OR in Unreal Engine 5
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 16) || ENGINE_MAJOR_VERSION == 5
    virtual bool ReadLeaderboardsAroundRank(int32 Rank, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;
    virtual bool ReadLeaderboardsAroundUser(TSharedRef<const FUniqueNetId> Player, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;
#endif

    virtual void FreeStats(FOnlineLeaderboardRead& ReadObject) override;
    virtual bool WriteLeaderboards(const FName& SessionName, const FUniqueNetId& Player, FOnlineLeaderboardWrite& WriteObject) override;
    virtual bool FlushLeaderboards(const FName& SessionName) override;
    virtual bool WriteOnlinePlayerRatings(const FName& SessionName, int32 LeaderboardId, const TArray<FOnlinePlayerScore>& PlayerScores) override;

    //BC Callbacks
    void readLeaderboardSuccess(const FString& jsonData, FOnlineLeaderboardReadRef leaderboardRead);
    void readLeaderboardFail(int32 returnCode, const FString& jsonData, FOnlineLeaderboardReadRef leaderboardRead);

    void flushLeaderboardSuccess(const FString& jsonData, FOnlineLeaderboardReadRef leaderboardRead);
    void flushLeaderboardFail(int32 returnCode, const FString& jsonData, FOnlineLeaderboardReadRef leaderboardRead);

private:
    /** Pointer to owning subsystem */
    FOnlineSubsystemBrainCloud* Subsystem;

    /**
     * Helper function to get the platform- and game-specific leaderboard ID from the JSON config file.
     *
     * @param LeaderboardName the cross-platform name of the leaderboard to look up
     * @return The unique ID for the leaderboard as specified in the config file.
    */
    FString GetLeaderboardID(const FString& LeaderboardName);

    /** Scores are cached here in WriteLeaderboards until FlushLeaderboards is called */
    TArray<FOnlinePendingLeaderboardWrite> UnreportedScores;

    void FlushNext();

    bool _isFlushing = false;
};

typedef TSharedPtr<FOnlineLeaderboardsBrainCloud, ESPMode::ThreadSafe> FOnlineLeaderboardsBrainCloudPtr;
