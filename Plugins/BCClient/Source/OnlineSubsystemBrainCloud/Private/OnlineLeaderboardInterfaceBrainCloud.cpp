// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "OnlineLeaderboardInterfaceBrainCloud.h"
#include "OnlineSubsystemBrainCloudPrivatePCH.h"
#include "Online.h"

#include "BrainCloudClient.h"

#include "OnlineSubsystemBrainCloud.h"
#include "ServiceOperation.h"
#include "ServiceName.h"
#include "LeaderboardCallback.h"

using namespace std::placeholders;

FOnlineLeaderboardsBrainCloud::FOnlineLeaderboardsBrainCloud(FOnlineSubsystemBrainCloud* InSubsystem)
    : Subsystem(InSubsystem)
{
    check(Subsystem);
}

bool FOnlineLeaderboardsBrainCloud::ReadLeaderboards(const TArray< TSharedRef<const FUniqueNetId> >& Players, FOnlineLeaderboardReadRef& ReadObject)
{
    ReadObject->Rows.Empty();
    ReadObject->ReadState = EOnlineAsyncTaskState::InProgress;


    LeaderboardCallback* lbcb = Subsystem->GetCallbackObject<LeaderboardCallback>(ReadObject);

    lbcb->OnSuccessDelegate.AddRaw(this, &FOnlineLeaderboardsBrainCloud::readLeaderboardSuccess);
    lbcb->OnFailDelegate.AddRaw(this, &FOnlineLeaderboardsBrainCloud::readLeaderboardFail);

    Subsystem->GetClient()->getLeaderboardService()->getGlobalLeaderboardView(ReadObject->LeaderboardName.ToString(), ESortOrder::HIGH_TO_LOW, 9, 10, lbcb);

    return true;
}

bool FOnlineLeaderboardsBrainCloud::ReadLeaderboardsForFriends(int32 LocalUserNum, FOnlineLeaderboardReadRef& ReadObject)
{
    UE_LOG(LogOnline, Warning, TEXT("ReadLeaderboardsForFriends is not supported"));
    TriggerOnLeaderboardReadCompleteDelegates(false);
    return false;
}

#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION >= 16
bool FOnlineLeaderboardsBrainCloud::ReadLeaderboardsAroundRank(int32 Rank, uint32 Range, FOnlineLeaderboardReadRef& ReadObject)
{
    UE_LOG(LogOnline, Warning, TEXT("ReadLeaderboardsAroundRank is not supported"));
    TriggerOnLeaderboardReadCompleteDelegates(false);
    return false;
}
bool FOnlineLeaderboardsBrainCloud::ReadLeaderboardsAroundUser(TSharedRef<const FUniqueNetId> Player, uint32 Range, FOnlineLeaderboardReadRef& ReadObject)
{
    UE_LOG(LogOnline, Warning, TEXT("ReadLeaderboardsAroundUser is not supported"));
    TriggerOnLeaderboardReadCompleteDelegates(false);
    return false;
}
#elif ENGINE_MAJOR_VERSION >= 5
bool FOnlineLeaderboardsBrainCloud::ReadLeaderboardsAroundRank(int32 Rank, uint32 Range, FOnlineLeaderboardReadRef& ReadObject)
{
	UE_LOG(LogOnline, Warning, TEXT("ReadLeaderboardsAroundRank is not supported"));
	TriggerOnLeaderboardReadCompleteDelegates(false);
	return false;
}

bool FOnlineLeaderboardsBrainCloud::ReadLeaderboardsAroundUser(TSharedRef<const FUniqueNetId> Player, uint32 Range, FOnlineLeaderboardReadRef& ReadObject)
{
	UE_LOG(LogOnline, Warning, TEXT("ReadLeaderboardsAroundUser is not supported"));
	TriggerOnLeaderboardReadCompleteDelegates(false);
	return false;
}
#endif

void FOnlineLeaderboardsBrainCloud::FreeStats(FOnlineLeaderboardRead& ReadObject)
{
    UE_LOG(LogOnline, Warning, TEXT("FreeStats is unsupported"));
}

bool FOnlineLeaderboardsBrainCloud::WriteLeaderboards(const FName& SessionName, const FUniqueNetId& Player, FOnlineLeaderboardWrite& WriteObject)
{
    UE_LOG_ONLINE(Display, TEXT("WriteLeaderboards"));

    bool bWroteAnyLeaderboard = false;

    for (int32 LeaderboardIdx = 0; LeaderboardIdx < WriteObject.LeaderboardNames.Num(); ++LeaderboardIdx)
    {
        FString LeaderboardName = WriteObject.LeaderboardNames[LeaderboardIdx].ToString();

        UE_LOG_ONLINE(Display, TEXT("Going through stats for leaderboard :  %s "), *LeaderboardName);

        for (FStatPropertyArray::TConstIterator It(WriteObject.Properties); It; ++It)
        {
            const FVariantData& Stat = It.Value();
            int32 Score;

            UE_LOG_ONLINE(Display, TEXT("Here's a stat"));

            if (Stat.GetType() == EOnlineKeyValuePairDataType::Int32)
            {
                Stat.GetValue(Score);

                FOnlinePendingLeaderboardWrite* UnreportedScore = new (UnreportedScores)FOnlinePendingLeaderboardWrite();
                UnreportedScore->LeaderboardName = LeaderboardName;
                UnreportedScore->Score = Score;
                UE_LOG_ONLINE(Display, TEXT("FOnlineLeaderboardsAndroid::WriteLeaderboards() Int32 value Score: %d"), Score);

                bWroteAnyLeaderboard = true;
            }
            else
            {
                UE_LOG_ONLINE(Error, TEXT("Unsupported data type for leaderboard write"));
            }
        }
    }

    //Return whether any stat was cached
    return bWroteAnyLeaderboard;
}

bool FOnlineLeaderboardsBrainCloud::FlushLeaderboards(const FName& SessionName)
{
    UE_LOG_ONLINE(Display, TEXT("flush leaderboards session name :%s"), *SessionName.ToString());

    bool Success = true;

    for (int32 i = 0; i < UnreportedScores.Num(); ++i)
    {
        UE_LOG_ONLINE(Display, TEXT("Submitting an unreported score to %s. Value: %d"), *UnreportedScores[i].LeaderboardName, UnreportedScores[i].Score);
        Subsystem->GetClient()->getLeaderboardService()->postScore(UnreportedScores[i].LeaderboardName, (int32)UnreportedScores[i].Score, TEXT(""), nullptr);
    }

    UnreportedScores.Empty();
    TriggerOnLeaderboardFlushCompleteDelegates(SessionName, Success);

    return true;
}

bool FOnlineLeaderboardsBrainCloud::WriteOnlinePlayerRatings(const FName& SessionName, int32 LeaderboardId, const TArray<FOnlinePlayerScore>& PlayerScores)
{
    UE_LOG(LogOnline, Warning, TEXT("WriteOnlinePlayerRatings is unsupported"));
    return false;
}

FString FOnlineLeaderboardsBrainCloud::GetLeaderboardID(const FString& LeaderboardName)
{
    UE_LOG(LogOnline, Warning, TEXT("GetLeaderboardID is unsupported"));
    return LeaderboardName;
}

//BC Callbacks
void FOnlineLeaderboardsBrainCloud::readLeaderboardSuccess(const FString& jsonData, FOnlineLeaderboardReadRef leaderboardRead)
{
    bool bWasSuccessful = false;

    TArray<TSharedPtr<FJsonValue>> leaderboard = FOnlineSubsystemBrainCloud::GetJsonData(jsonData)->GetArrayField("leaderboard");

    TSharedPtr<const FUniqueNetId> currentUserId = Subsystem->GetIdentityInterface()->GetUniquePlayerId(0);

    FOnlineStatsRow* currentUserRow = leaderboardRead.Get().FindPlayerRecord(*currentUserId);
    if (currentUserRow == NULL)
    {
        currentUserRow = new (leaderboardRead->Rows) FOnlineStatsRow(currentUserId->ToString(), currentUserId.ToSharedRef());
    }

    UE_LOG(LogOnline, Display, TEXT("----------------------------------------------------------------"));
    for (int32 i = 0; i < leaderboard.Num(); i++)
    {
        TSharedPtr<FJsonObject> lbObj = leaderboard[i]->AsObject();
        FString playerID = lbObj->GetStringField("playerId");
        int32 score = (int32)lbObj->GetNumberField("score");
        FString playerName = lbObj->GetStringField("name");

        UE_LOG(LogOnline, Display, TEXT("PlayerId: %s"), *playerID);
        UE_LOG(LogOnline, Display, TEXT("Name: %s"), *playerName);
        UE_LOG(LogOnline, Display, TEXT("Value: %d"), score);
        UE_LOG(LogOnline, Display, TEXT("----------------------------------------------------------------"));

        TSharedRef<const FUniqueNetId> userId = MakeShareable(new FUniqueNetIdString(playerID));

        FOnlineStatsRow* userRow = leaderboardRead.Get().FindPlayerRecord(userId.Get());
        if (userRow == NULL)
        {
            userRow = new (leaderboardRead->Rows) FOnlineStatsRow(playerName, userId);
        }

        for (int32 StatIdx = 0; StatIdx < leaderboardRead->ColumnMetadata.Num(); StatIdx++)
        {
            const FColumnMetaData& columnMeta = leaderboardRead->ColumnMetadata[StatIdx];

            if (columnMeta.DataType == EOnlineKeyValuePairDataType::Int32)
            {
                int32 Value = score;
                userRow->Columns.Add(columnMeta.ColumnName, FVariantData(Value));
                bWasSuccessful = true;
            }
            else
            {
                UE_LOG_ONLINE(Warning, TEXT("Unsupported key value pair during retrieval from BrainCloud %s"), *columnMeta.ColumnName.ToString());
            }
        }
    }

    leaderboardRead->ReadState = EOnlineAsyncTaskState::Done;
    TriggerOnLeaderboardReadCompleteDelegates(bWasSuccessful);
}

void FOnlineLeaderboardsBrainCloud::readLeaderboardFail(int32 returnCode, const FString& jsonData, FOnlineLeaderboardReadRef leaderboardRead)
{
    leaderboardRead->ReadState = EOnlineAsyncTaskState::Failed;
    TriggerOnLeaderboardReadCompleteDelegates(false);
}

void FOnlineLeaderboardsBrainCloud::FlushNext()
{
    //if (UnreportedScores.Num() <= 0)
    //{
    //    _isFlushing = false;
    //    return;
    //}

    //FOnlinePendingLeaderboardWrite pendingWrite = UnreportedScores.Pop(false);

    //LeaderboardCallback* lbcb = new LeaderboardCallback(
    //    std::bind(&FOnlineLeaderboardsBrainCloud::flushLeaderboardSuccess, this, _1, _2, _3, _4),
    //    std::bind(&FOnlineLeaderboardsBrainCloud::flushLeaderboardFail, this, _1, _2, _3, _4, _5),
    //    nullptr);

    //Subsystem->RegisterCallbackObject(lbcb);

    //Subsystem->GetClient()->getLeaderboardService()->postScore(pendingWrite.LeaderboardName, pendingWrite.Score, TEXT(""), lbcb);
}

void FOnlineLeaderboardsBrainCloud::flushLeaderboardSuccess(const FString& jsonData, FOnlineLeaderboardReadRef leaderboardRead)
{

}

void FOnlineLeaderboardsBrainCloud::flushLeaderboardFail(int32 returnCode, const FString& jsonData, FOnlineLeaderboardReadRef leaderboardRead)
{

}
