// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "OnlineSubsystemBrainCloudPrivatePCH.h"

#include "OnlineSubsystemBrainCloud.h"
#include "BrainCloudClient.h"

#include "OnlineAchievementsInterfaceBrainCloud.h"
#include "OnlineIdentityInterfaceBrainCloud.h"
#include "OnlineLeaderboardInterfaceBrainCloud.h"
#include "OnlineTimeInterfaceBrainCloud.h"
#include "OnlineMessageInterfaceBrainCloud.h"
#include "OnlineTitleFileInterfaceBrainCloud.h"

#include "AssignableServerCallback.h"

IOnlineSessionPtr FOnlineSubsystemBrainCloud::GetSessionInterface() const
{
	return nullptr;
}

IOnlineFriendsPtr FOnlineSubsystemBrainCloud::GetFriendsInterface() const
{
	return nullptr;
}

IOnlinePartyPtr FOnlineSubsystemBrainCloud::GetPartyInterface() const
{
	return nullptr;
}

IOnlineGroupsPtr FOnlineSubsystemBrainCloud::GetGroupsInterface() const
{
	return nullptr;
}

IOnlineSharedCloudPtr FOnlineSubsystemBrainCloud::GetSharedCloudInterface() const
{
	return nullptr;
}

IOnlineUserCloudPtr FOnlineSubsystemBrainCloud::GetUserCloudInterface() const
{
	return nullptr;
}

IOnlineEntitlementsPtr FOnlineSubsystemBrainCloud::GetEntitlementsInterface() const
{
	return nullptr;
};

IOnlineLeaderboardsPtr FOnlineSubsystemBrainCloud::GetLeaderboardsInterface() const
{
	return LeaderboardsInterface;
}

IOnlineVoicePtr FOnlineSubsystemBrainCloud::GetVoiceInterface() const
{
	return nullptr;
}

IOnlineExternalUIPtr FOnlineSubsystemBrainCloud::GetExternalUIInterface() const
{
	return nullptr;
}

IOnlineTimePtr FOnlineSubsystemBrainCloud::GetTimeInterface() const
{
	return TimeInterface;
}

IOnlineIdentityPtr FOnlineSubsystemBrainCloud::GetIdentityInterface() const
{
	return IdentityInterface;
}

IOnlineTitleFilePtr FOnlineSubsystemBrainCloud::GetTitleFileInterface() const
{
	return TitleFileInterface;
}

IOnlineStorePtr FOnlineSubsystemBrainCloud::GetStoreInterface() const
{
	return nullptr;
}

#if ENGINE_MINOR_VERSION >= 11
IOnlineStoreV2Ptr FOnlineSubsystemBrainCloud::GetStoreV2Interface() const
{
	return nullptr;
}

IOnlinePurchasePtr FOnlineSubsystemBrainCloud::GetPurchaseInterface() const
{
	return nullptr;
}
#endif

IOnlineEventsPtr FOnlineSubsystemBrainCloud::GetEventsInterface() const
{
	return nullptr;
}

IOnlineAchievementsPtr FOnlineSubsystemBrainCloud::GetAchievementsInterface() const
{
	return AchievementsInterface;
}

IOnlineSharingPtr FOnlineSubsystemBrainCloud::GetSharingInterface() const
{
	return nullptr;
}

IOnlineUserPtr FOnlineSubsystemBrainCloud::GetUserInterface() const
{
	return nullptr;
}

IOnlineMessagePtr FOnlineSubsystemBrainCloud::GetMessageInterface() const
{
	return MessageInterface;
}

IOnlinePresencePtr FOnlineSubsystemBrainCloud::GetPresenceInterface() const
{
	return nullptr;
}

IOnlineChatPtr FOnlineSubsystemBrainCloud::GetChatInterface() const
{
	return nullptr;
}

IOnlineTurnBasedPtr FOnlineSubsystemBrainCloud::GetTurnBasedInterface() const
{
	return nullptr;
}

bool FOnlineSubsystemBrainCloud::Tick(float DeltaTime)
{
	if (!FOnlineSubsystemImpl::Tick(DeltaTime))
	{
		return false;
	}

	BrainCloudClient::getInstance()->runCallbacks();

	CleanupCallbackObjects();

	return true;
}

bool FOnlineSubsystemBrainCloud::Init()
{
	UE_LOG_ONLINE(Display, TEXT("FOnlineSubsystemBrainCloud::Init()"));
	const bool bBrainCloudInit = true;

	_configPath = FPaths::SourceConfigDir();
	_configPath += TEXT("BrainCloudConfig.ini");

	if (FPaths::FileExists(_configPath))
	{
		FConfigSection* Configs = GConfig->GetSectionPrivate(TEXT("BrainCloud.Client"), false, true, _configPath);
		if (Configs)
		{
#if ENGINE_MINOR_VERSION >= 12
			FString test = Configs->Find(TEXT("ServerURL"))->GetValue();
			BrainCloudClient::getInstance()->initialize(
				Configs->Find(TEXT("ServerURL"))->GetValue(),
				Configs->Find(TEXT("Secret"))->GetValue(),
				Configs->Find(TEXT("AppID"))->GetValue(),
				Configs->Find(TEXT("Version"))->GetValue());
#else
			FString test = *Configs->Find(TEXT("ServerURL"));
			BrainCloudClient::getInstance()->initialize(
				*Configs->Find(TEXT("ServerURL")),
				*Configs->Find(TEXT("Secret")),
				*Configs->Find(TEXT("AppID")),
				*Configs->Find(TEXT("Version")));
#endif
		}
		else
		{
			UE_LOG_ONLINE(Warning, TEXT("Could not find BrainCloud.Client in BrainCloudConfig.ini"));
		}
	}
	else
	{
		UE_LOG_ONLINE(Warning, TEXT("Could not find BrainCloudConfig.ini, must Initialize manually!"));
	}

	if (bBrainCloudInit)
	{
		AchievementsInterface = MakeShareable(new FOnlineAchievementsBrainCloud(this));
		IdentityInterface = MakeShareable(new FOnlineIdentityBrainCloud(this));
		LeaderboardsInterface = MakeShareable(new FOnlineLeaderboardsBrainCloud(this));
		TimeInterface = MakeShareable(new FOnlineTimeBrainCloud(this));
		MessageInterface = MakeShareable(new FOnlineMessageBrainCloud(this));
		TitleFileInterface = MakeShareable(new FOnlineTitleFileBrainCloud(this));

		_clientPtr = BrainCloudClient::getInstance();
	}
	else
	{
		Shutdown();
	}

	return bBrainCloudInit;
}

bool FOnlineSubsystemBrainCloud::Shutdown()
{
	UE_LOG_ONLINE(Display, TEXT("FOnlineSubsystemBrainCloud::Shutdown()"));

	FOnlineSubsystemImpl::Shutdown();

#define DESTRUCT_INTERFACE(Interface) \
    if (Interface.IsValid()) \
                        { \
        ensure(Interface.IsUnique()); \
        Interface = nullptr; \
                        }

	// Destruct the interfaces
	DESTRUCT_INTERFACE(IdentityInterface);
	DESTRUCT_INTERFACE(AchievementsInterface);
	DESTRUCT_INTERFACE(LeaderboardsInterface);
	DESTRUCT_INTERFACE(MessageInterface);
	DESTRUCT_INTERFACE(TimeInterface);
	DESTRUCT_INTERFACE(TitleFileInterface);

#undef DESTRUCT_INTERFACE

	return true;
}

FString FOnlineSubsystemBrainCloud::GetAppId() const
{
	return TEXT("");
}

bool FOnlineSubsystemBrainCloud::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return false;
}
#if ENGINE_MINOR_VERSION >= 17
FText FOnlineSubsystemBrainCloud::GetOnlineServiceName() const
{
	return NSLOCTEXT("brainCloud", "brainCloud", "brainCloud");
}
#endif

bool FOnlineSubsystemBrainCloud::IsEnabled() const
{
	return true;
}

BrainCloudClient* FOnlineSubsystemBrainCloud::GetClient()
{
	return _clientPtr;
}

TSharedPtr<FJsonObject> FOnlineSubsystemBrainCloud::GetJsonData(const FString & jsonString)
{
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(jsonString);
	TSharedPtr<FJsonObject> jsonValue = MakeShareable(new FJsonObject());
	FJsonSerializer::Deserialize(reader, jsonValue);
	TSharedPtr<FJsonObject> data = jsonValue->GetObjectField("data");
	return data;
}

void FOnlineSubsystemBrainCloud::RegisterCallbackObject(AssignableServerCallback* callback)
{
	_activeCallbacks.Add(callback);
}

void FOnlineSubsystemBrainCloud::CleanupCallbackObjects()
{
	if (_activeCallbacks.Num() <= 0) return;

	for (int32 i = _activeCallbacks.Num() - 1; i >= 0; i--)
	{
		if (_activeCallbacks[i] == nullptr)
		{
			_activeCallbacks.RemoveAt(i);
			continue;
		}

		if (_activeCallbacks[i]->IsComplete())
		{
			delete(_activeCallbacks[i]);
			_activeCallbacks[i] = nullptr;
			_activeCallbacks.RemoveAt(i);
		}
	}
}
