// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class IEventCallback;
class IRewardCallback;
class ServerCall;

class BCCLIENTPLUGIN_API IBrainCloudComms
{
public:
    virtual ~IBrainCloudComms() {}

    virtual void initialize(const FString& serverURL, const FString& secretKey, const FString& gameId) = 0;
    virtual void enableLogging(bool shouldEnable) = 0;
    virtual bool isAuthenticated() = 0;
	virtual void setAuthenticated() = 0;
	virtual bool isInitialized() = 0;

    virtual void addToQueue(ServerCall *) = 0;

    virtual void clearSessionId() = 0;
    virtual const FString& getSessionId() const = 0;
    virtual void setSessionId(const TCHAR *) = 0;

    virtual void setServerUrl(const TCHAR *) = 0;
    virtual void setHeartbeatInterval(int milliseconds) = 0;

    virtual void heartbeat() = 0;
    virtual void resetCommunication() = 0;
    virtual void runCallbacks() = 0;

    virtual const TArray<int32> & getPacketTimeouts() = 0;
    virtual void setPacketTimeouts(const TArray<int32> & packetTimeouts) = 0;
    virtual void setPacketTimeoutsToDefault() = 0;

    virtual int32 getAuthenticationPacketTimeout() = 0;
    virtual void setAuthenticationPacketTimeout(int32 timeoutSecs) = 0;

    virtual void setOldStyleStatusMessageErrorCallback(bool useOldStatusMessage) = 0;

    //Event callback
    virtual void registerEventCallback(IEventCallback * eventCallback) = 0;
    virtual void deregisterEventCallback() = 0;

    //reward callback
    virtual void registerRewardCallback(IRewardCallback *rewardCallback) = 0;
    virtual void deregisterRewardCallback() = 0;
};
