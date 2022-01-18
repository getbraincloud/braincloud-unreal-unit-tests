// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "OnlineIdentityInterfaceBrainCloud.h"
#include "OnlineSubsystemBrainCloudPrivatePCH.h"
#include "IPAddress.h"
#include "SocketSubsystem.h"

#include "BrainCloudClient.h"
#include "ServiceOperation.h"
#include "ServiceName.h"

#include "AssignableServerCallback.h"

FOnlineIdentityBrainCloud::FOnlineIdentityBrainCloud(class FOnlineSubsystemBrainCloud* InSubsystem) 
    : Subsystem(InSubsystem)
{
}

FOnlineIdentityBrainCloud::~FOnlineIdentityBrainCloud()
{
}

inline FString GenerateRandomUserId(int32 LocalUserNum)
{
    FString HostName;
    if (!ISocketSubsystem::Get()->GetHostName(HostName))
    {
        // could not get hostname, use address
        bool bCanBindAll;
        TSharedPtr<class FInternetAddr> Addr = ISocketSubsystem::Get()->GetLocalHostAddr(*GLog, bCanBindAll);
        HostName = Addr->ToString(false);
    }

    return FString::Printf(TEXT("%s-%s"), *HostName, *FGuid::NewGuid().ToString());
}

bool FOnlineIdentityBrainCloud::Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials)
{
    FString ErrorStr;

    if (AccountCredentials.Id.IsEmpty())
    {
        ErrorStr = TEXT("Invalid account id, string empty");
    }
    else if (bLoggingInUser)
    {
        ErrorStr = TEXT("Already logging in a user");
    }
    else
    {
        AssignableServerCallback* cb = Subsystem->GetCallbackObject<AssignableServerCallback>();

        cb->OnSuccessDelegate.AddRaw(this, &FOnlineIdentityBrainCloud::authenticateSuccess);
        cb->OnFailDelegate.AddRaw(this, &FOnlineIdentityBrainCloud::authenticateFail);

        Subsystem->GetClient()->getAuthenticationService()->authenticateUniversal(
            AccountCredentials.Id,
            AccountCredentials.Token,
            true,
            cb);

        bLoggingInUser = true;
    }

    if (!ErrorStr.IsEmpty())
    {
        UE_LOG_ONLINE(Warning, TEXT("Login request failed: %s"), *ErrorStr);
        TriggerOnLoginCompleteDelegates(LocalUserNum, false, FUniqueNetIdString(), ErrorStr);
        return false;
    }
    return true;
}

bool FOnlineIdentityBrainCloud::Logout(int32 LocalUserNum)
{
    if (GetLoginStatus(LocalUserNum) == ELoginStatus::LoggedIn)
    {
        AssignableServerCallback* cb = Subsystem->GetCallbackObject<AssignableServerCallback>();

        cb->OnSuccessDelegate.AddRaw(this, &FOnlineIdentityBrainCloud::logoutSuccess);
        cb->OnFailDelegate.AddRaw(this, &FOnlineIdentityBrainCloud::logoutFail);

        Subsystem->GetClient()->getPlayerStateService()->logout(cb);
        return true;
    }

    UE_LOG_ONLINE(Warning, TEXT("No logged in user"));
    TriggerOnLogoutCompleteDelegates(LocalUserNum, false);
    return false;
}

bool FOnlineIdentityBrainCloud::AutoLogin(int32 LocalUserNum)
{
    FString LoginStr;
    FString PasswordStr;
    FString TypeStr;

    FParse::Value(FCommandLine::Get(), TEXT("AUTH_LOGIN="), LoginStr);
    FParse::Value(FCommandLine::Get(), TEXT("AUTH_PASSWORD="), PasswordStr);
    FParse::Value(FCommandLine::Get(), TEXT("AUTH_TYPE="), TypeStr);

    if (!LoginStr.IsEmpty())
    {
        if (!PasswordStr.IsEmpty())
        {
            if (!TypeStr.IsEmpty())
            {
                return Login(0, FOnlineAccountCredentials(TypeStr, LoginStr, PasswordStr));
            }
            else
            {
                UE_LOG_ONLINE(Warning, TEXT("AutoLogin missing AUTH_TYPE=<type>."));
            }
        }
        else
        {
            UE_LOG_ONLINE(Warning, TEXT("AutoLogin missing AUTH_PASSWORD=<password>."));
        }
    }
    else
    {
        UE_LOG_ONLINE(Warning, TEXT("AutoLogin missing AUTH_LOGIN=<login id>."));
    }
    return false;
}

TSharedPtr<FUserOnlineAccount> FOnlineIdentityBrainCloud::GetUserAccount(const FUniqueNetId& UserId) const
{
    return nullptr;
}

TArray<TSharedPtr<FUserOnlineAccount> > FOnlineIdentityBrainCloud::GetAllUserAccounts() const
{
    TArray<TSharedPtr<FUserOnlineAccount>> array;
    return array;
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityBrainCloud::GetUniquePlayerId(int32 LocalUserNum) const
{
    return MakeShareable(new FUniqueNetIdString(Subsystem->GetClient()->getAuthenticationService()->getProfileId()));
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityBrainCloud::CreateUniquePlayerId(uint8* Bytes, int32 Size)
{
    if (Bytes && Size == sizeof(uint64))
    {
        int32 StrLen = FCString::Strlen((TCHAR*)Bytes);
        if (StrLen > 0)
        {
            FString StrId((TCHAR*)Bytes);
            return MakeShareable(new FUniqueNetIdString(StrId));
        }
    }
    return NULL;
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityBrainCloud::CreateUniquePlayerId(const FString& Str)
{
    return MakeShareable(new FUniqueNetIdString(Str));
}

ELoginStatus::Type FOnlineIdentityBrainCloud::GetLoginStatus(int32 LocalUserNum) const
{
    if (Subsystem->GetClient()->isAuthenticated())
    {
        return ELoginStatus::LoggedIn;
    }

    return ELoginStatus::NotLoggedIn;
}

ELoginStatus::Type FOnlineIdentityBrainCloud::GetLoginStatus(const FUniqueNetId& UserId) const
{
    return GetLoginStatus(0);
}

FString FOnlineIdentityBrainCloud::GetPlayerNickname(int32 LocalUserNum) const
{
    return Subsystem->GetClient()->getPlayerStateService()->getUserName();
}

FString FOnlineIdentityBrainCloud::GetPlayerNickname(const FUniqueNetId& UserId) const
{
    return Subsystem->GetClient()->getPlayerStateService()->getUserName();
}

FString FOnlineIdentityBrainCloud::GetAuthToken(int32 LocalUserNum) const
{
    return TEXT("");
}

// Unreal Engine Version is >= 4.18 OR in Unreal Engine 5
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 18) || ENGINE_MAJOR_VERSION ==5
void FOnlineIdentityBrainCloud::RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate)
{

}
#endif

void FOnlineIdentityBrainCloud::GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate)
{
    Delegate.ExecuteIfBound(UserId, Privilege, (uint32)EPrivilegeResults::NoFailures);
}

// Unreal Engine Version is >= 4.18 OR in Unreal Engine 5
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 18) || ENGINE_MAJOR_VERSION == 5
FPlatformUserId FOnlineIdentityBrainCloud::GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& _uniqueNetId) const
#else
FPlatformUserId FOnlineIdentityBrainCloud::GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& _uniqueNetId)
#endif
{
    return PLATFORMUSERID_NONE;
}

// Unreal Engine Version is >= 4.11 OR in Unreal Engine 5
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 11) || ENGINE_MAJOR_VERSION == 5 
FString FOnlineIdentityBrainCloud::GetAuthType() const
{
    return TEXT("BrainCloud");
}
#endif

//BC Callbacks
void FOnlineIdentityBrainCloud::authenticateSuccess(const FString& jsonData)
{
    bLoggingInUser = false;
    TriggerOnLoginCompleteDelegates(0, true, *GetUniquePlayerId(0), FString());
}

void FOnlineIdentityBrainCloud::authenticateFail(int32 returnCode, const FString& jsonData)
{
    bLoggingInUser = false;
    TriggerOnLoginCompleteDelegates(0, false, FUniqueNetIdString(TEXT("")), FString());
}

void FOnlineIdentityBrainCloud::logoutSuccess(const FString&)
{
    TriggerOnLogoutCompleteDelegates(0, true);
}

void FOnlineIdentityBrainCloud::logoutFail(int32 returnCode, const FString&)
{
    TriggerOnLogoutCompleteDelegates(0, false);
}
