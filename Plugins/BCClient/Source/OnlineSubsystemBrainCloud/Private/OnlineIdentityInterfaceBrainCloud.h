// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "OnlineIdentityInterface.h"
#include "OnlineSubsystemBrainCloud.h"

/**
 * BrainCloud service implementation of the online identity interface
 */
class FOnlineIdentityBrainCloud : public IOnlineIdentity
{
public:

    /**
    * Constructor
    * @param InSubsystem online subsystem being used
    */
    FOnlineIdentityBrainCloud(FOnlineSubsystemBrainCloud* InSubsystem);

    /**
    * Destructor
    */
    virtual ~FOnlineIdentityBrainCloud();

    // Begin IOnlineIdentity interface
    virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;
    virtual bool Logout(int32 LocalUserNum) override;
    virtual bool AutoLogin(int32 LocalUserNum) override;
    virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;
    virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const override;
    virtual TSharedPtr<const FUniqueNetId> GetUniquePlayerId(int32 LocalUserNum) const override;
    virtual TSharedPtr<const FUniqueNetId> CreateUniquePlayerId(uint8* Bytes, int32 Size) override;
    virtual TSharedPtr<const FUniqueNetId> CreateUniquePlayerId(const FString& Str) override;
    virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;
    virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;
    virtual FString GetPlayerNickname(int32 LocalUserNum) const override;
    virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;
    virtual FString GetAuthToken(int32 LocalUserNum) const override;
    virtual void RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate);
    virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate) override;
    virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const override;
#if ENGINE_MINOR_VERSION >= 11
    virtual FString GetAuthType() const override;
#endif
    // End IOnlineIdentity interface

    //BC Callbacks
    void authenticateSuccess(const FString& jsonData);
    void authenticateFail(int32 returnCode, const FString& jsonData);

    void logoutSuccess(const FString& jsonData);
    void logoutFail(int32 returnCode, const FString& jsonData);

private:
    FOnlineSubsystemBrainCloud* Subsystem;
    bool bLoggingInUser = false;
};

typedef TSharedPtr<FOnlineIdentityBrainCloud, ESPMode::ThreadSafe> FOnlineIdentityBrainCloudPtr;
