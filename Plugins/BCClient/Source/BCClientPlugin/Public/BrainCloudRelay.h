// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once
enum class BCRelayConnectionType : uint8;
class BrainCloudClient;
class BrainCloudRelayComms;
class UBCBlueprintRelayCallProxyBase;
class IRelayCallback;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudRelay
{
public:
	BrainCloudRelay(BrainCloudRelayComms *in_comms);
	/** 
 	* Use SetPingInterval() in order to set the interval for which Ping is calculated
	* does not average over the last N calls.  This is the value of the most recent Ping result
 	*/
	int64 ping();
	/** 
 	* NetId retrieved from the connected call
 	*/
	uint8 netId();
	/** 
 	* Start off a connection, based off connection type to brainClouds Relay Servers.  
	* Connect options come in from "ROOM_ASSIGNED" | "ROOM_READY" lobby callback
	* @param in_connectionType 
    * @param in_options
    * 	     in_options["ssl"] = false;
    * 	     in_options["host"] = "168.0.1.192";
    * 	     in_options["port"] = 9000;
    * 	     in_options["passcode"] = "somePasscode"
    * 	     in_options["lobbyId"] = "55555:v5v:001";
	* 
    * @param callback
 	*/
	void connect(BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *in_callback);
	/** 
 	* Disables relay event for this session.
 	*/
	void disconnect();
	/** 
 	* Is Connected
 	*/
	bool isConnected();
	/** 
 	* Register callback, so that data is received on the main thread
	* @param callback
 	*/
	void registerDataCallback(IRelayCallback *in_callback);
	/** 
 	* Register callback, so that data is received on the main thread, support for Blueprint
	* @param callback
 	*/
	void registerDataCallback(UBCBlueprintRelayCallProxyBase *in_callback);
	/** 
 	*  Deregister the data callback
 	*/
	void deregisterDataCallback();
	/** 
 	* Send byte array representation of data
	* @param in_message : message to be sent
    * @param to_netId : the net id to send to, RelayComms.TO_ALL_PLAYERS to relay to all
	* @param in_reliable : send this reliably or not
	* @param in_ordered : received this ordered or not
	* @param in_channel : 0,1,2,3 (max of four channels)
 	*/
	bool send(const TArray<uint8> &in_data, const uint8 in_target, 
				bool in_reliable = true, bool in_ordered = true, int in_channel = 0);
	/** 
 	* Set the ping interval.
 	*/
	void setPingInterval(float in_interval);

	/** 
 	* Convert an array of bytes to a TCHAR
 	* @param In byte array values to convert
 	* @param Count number of bytes to convert
 	* @return Valid in_string representing bytes.
 	*/
	static FString BCBytesToString(const uint8 *in, int32 count);

	/** 
 	* Convert FString of bytes into the byte array.
 	* @param in_string		The FString of byte values
 	* @param out_bytes		Ptr to memory must be preallocated large enough
 	* @param in_maxBufferSize	Max buffer size of the out_bytes array, to prevent overflow
 	* @return	The number of bytes copied
 	*/
	static int32 BCStringToBytes(const FString &in_string, uint8 *out_bytes, int32 in_maxBufferSize);

private:
	BrainCloudRelayComms *_relayComms = nullptr;
};
