// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

enum class BCRTTConnectionStatus : uint8;
enum class BCRTTConnectionType : uint8;
class BrainCloudClient;
class BrainCloudRTTComms;
class UBCBlueprintRTTCallProxyBase;
class IRTTCallback;
class IServerCallback;
class UBCRTTProxy;

class BCCLIENTPLUGIN_API BrainCloudRTT
{
  public:
	BrainCloudRTT(BrainCloudRTTComms *comms, BrainCloudClient *client);

	/// <summary>
	/// Requests the event server address
	/// </summary>
	void requestClientConnection(IServerCallback *callback);

	/*
	* Enables Real Time event for this session.
	* Real Time events are disabled by default. Usually events
	* need to be polled using GET_EVENTS. By enabling this, events will
	* be received instantly when they happen through a TCP connection to an Event Server.
	*
	* This function will first call requestClientConnection, then connect to the address
	*/
	void enableRTT(BCRTTConnectionType in_type, IServerCallback *in_callback);

	/*
	* Enables Real Time event for this session.
	* Real Time events are disabled by default. Usually events
	* need to be polled using GET_EVENTS. By enabling this, events will
	* be received instantly when they happen through a TCP connection to an Event Server.
	*
	* This function will first call requestClientConnection, then connect to the address
	*/
	void enableRTT(BCRTTConnectionType in_type, UBCRTTProxy *in_callback);

	/*
	* Disables Real Time event for this session.
	*/
	void disableRTT();

	/*
	*Returns true id RTT is enabled
	*/
	bool isRTTEnabled();

	/**
	* 
	*/
	void setRTTHeartBeatSeconds(int32 in_value);

	/**
	* 
	*/
	void deregisterAllRTTCallbacks();

	/**
	* 
	*/
	void registerRTTEventCallback(UBCBlueprintRTTCallProxyBase *in_callback);

	/**
	* 
	*/
	void registerRTTEventCallback(IRTTCallback *in_callback);

	/**
	* 
	*/
	void deregisterRTTEventCallback();

	/**
	* 
	*/
	void registerRTTChatCallback(UBCBlueprintRTTCallProxyBase *in_callback);

	/**
	* 
	*/
	void registerRTTChatCallback(IRTTCallback *in_callback);

	/**
	* 
	*/
	void deregisterRTTChatCallback();

	/**
	* 
	*/
	void registerRTTMessagingCallback(UBCBlueprintRTTCallProxyBase *in_callback);

	/**
	* 
	*/
	void registerRTTMessagingCallback(IRTTCallback *in_callback);

	/**
	* 
	*/
	void deregisterRTTMessagingCallback();

	/**
	* 
	*/
	void registerRTTPresenceCallback(UBCBlueprintRTTCallProxyBase *in_callback);

	/**
	* 
	*/
	void registerRTTPresenceCallback(IRTTCallback *in_callback);

	/**
	* 
	*/
	void deregisterRTTPresenceCallback();
	/**
	* 
	*/
	void registerRTTLobbyCallback(UBCBlueprintRTTCallProxyBase *in_callback);

	/**
	* 
	*/
	void registerRTTLobbyCallback(IRTTCallback *in_callback);

	/**
	* 
	*/
	void deregisterRTTLobbyCallback();

		/**
	* 
	*/
	void registerRTTBlockchainRefresh(IRTTCallback *in_callback);

	/**
	* 
	*/
	void deregisterRTTBlockchainRefresh();

	const FString &getRTTConnectionId() const;
	BCRTTConnectionStatus getConnectionStatus();

  private:
	BrainCloudClient *_client = nullptr;
	BrainCloudRTTComms *_commsLayer = nullptr;
};
