// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemBrainCloudPackage.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Json.h"

/** Forward declarations of all interface classes */
typedef TSharedPtr<class FOnlineLeaderboardsBrainCloud, ESPMode::ThreadSafe> FOnlineLeaderboardsBrainCloudPtr;
typedef TSharedPtr<class FOnlineIdentityBrainCloud, ESPMode::ThreadSafe> FOnlineIdentityBrainCloudPtr;
typedef TSharedPtr<class FOnlineAchievementsBrainCloud, ESPMode::ThreadSafe> FOnlineAchievementsBrainCloudPtr;
typedef TSharedPtr<class FOnlineMessageBrainCloud, ESPMode::ThreadSafe> FOnlineMessageBrainCloudPtr;
typedef TSharedPtr<class FOnlineTitleFileBrainCloud, ESPMode::ThreadSafe> FOnlineTitleFileBrainCloudPtr;
typedef TSharedPtr<class FOnlineTimeBrainCloud, ESPMode::ThreadSafe> FOnlineTimeBrainCloudPtr;

class BrainCloudClient;
class UBrainCloudWrapper;
class AssignableServerCallback;

/**
*   OnlineSubsystemBrainCloud - Implementation of the online subsystem for BrainCloud services
*/
class ONLINESUBSYSTEMBRAINCLOUD_API FOnlineSubsystemBrainCloud : public FOnlineSubsystemImpl
{

  public:
    FOnlineSubsystemBrainCloud();
    virtual ~FOnlineSubsystemBrainCloud();

    // IOnlineSubsystem

    virtual IOnlineSessionPtr GetSessionInterface() const override;
    virtual IOnlineFriendsPtr GetFriendsInterface() const override;
    virtual IOnlinePartyPtr GetPartyInterface() const override;
    virtual IOnlineGroupsPtr GetGroupsInterface() const override;
    virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;
    virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;
    virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;
    virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;
    virtual IOnlineVoicePtr GetVoiceInterface() const override;
    virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;
    virtual IOnlineTimePtr GetTimeInterface() const override;
    virtual IOnlineIdentityPtr GetIdentityInterface() const override;
    virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;
    virtual IOnlineStorePtr GetStoreInterface() const override;

    virtual IOnlineEventsPtr GetEventsInterface() const override;
    virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;
    virtual IOnlineSharingPtr GetSharingInterface() const override;
    virtual IOnlineUserPtr GetUserInterface() const override;
    virtual IOnlineMessagePtr GetMessageInterface() const override;
    virtual IOnlinePresencePtr GetPresenceInterface() const override;
    virtual IOnlineChatPtr GetChatInterface() const override;
    virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;

#if ENGINE_MINOR_VERSION >= 22
    virtual IOnlineStatsPtr GetStatsInterface() const override;
#endif

#if ENGINE_MINOR_VERSION >= 21
    virtual IOnlineTournamentPtr GetTournamentInterface() const override;
#endif

#if ENGINE_MINOR_VERSION >= 17
    virtual FText GetOnlineServiceName() const override;
#endif

#if ENGINE_MINOR_VERSION >= 11
    virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;
    virtual IOnlinePurchasePtr GetPurchaseInterface() const override;
#endif
    virtual bool Init() override;
    virtual bool Shutdown() override;
    virtual FString GetAppId() const override;
    virtual bool Exec(class UWorld *InWorld, const TCHAR *Cmd, FOutputDevice &Ar) override;

    // FTickerObjectBase

    virtual bool Tick(float DeltaTime) override;

    /**
    * Used to create BrainCloud callback objects
    * Adds all objects to tracked list to ensure proper cleanup
    */
    template <typename T, typename... Args>
    T *GetCallbackObject(Args... args)
    {
        T *cb = new T(args...);
        AssignableServerCallback *acb = static_cast<AssignableServerCallback *>(cb);
        _activeCallbacks.Add(acb);
        return cb;
    }

    /**
    * Adds an AssignableServerCallback object to tracked list to ensure proper cleanup
    */
    void RegisterCallbackObject(AssignableServerCallback *callback);

    BrainCloudClient *GetClient();
    FString GetConfigPath() { return _configPath; }

    static TSharedPtr<FJsonObject> GetJsonData(const FString &jsonString);

    /**
    * Is the BrainCloud API available for use
    * @return true if BrainCloud functionality is available, false otherwise
    */
    virtual bool IsEnabled() const override;

    PACKAGE_SCOPE :

        /** Only the factory makes instances */
        FOnlineSubsystemBrainCloud(FName InSubsystemName, FName InInstanceName);

  private:
    /** Interface to the leaderboard services */
    FOnlineLeaderboardsBrainCloudPtr LeaderboardsInterface = nullptr;

    /** Interface to the identity registration/auth services */
    FOnlineIdentityBrainCloudPtr IdentityInterface = nullptr;

    /** Interface for achievements */
    FOnlineAchievementsBrainCloudPtr AchievementsInterface = nullptr;

    /** Interface for messages */
    FOnlineMessageBrainCloudPtr MessageInterface = nullptr;

    /** Interface for title files */
    FOnlineTitleFileBrainCloudPtr TitleFileInterface = nullptr;

    /** Interface for server time */
    FOnlineTimeBrainCloudPtr TimeInterface = nullptr;

    void CleanupCallbackObjects();

    TArray<AssignableServerCallback *> _activeCallbacks = TArray<AssignableServerCallback *>();

    BrainCloudClient *_clientPtr = nullptr;
    FString _configPath = "";
};

typedef TSharedPtr<FOnlineSubsystemBrainCloud, ESPMode::ThreadSafe> FOnlineSubsystemBrainCloudPtr;
