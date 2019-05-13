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
	int64 ping();
	uint8 netId();

	void connect(BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *callback);
	void disconnect();
	void registerDataCallback(IRelayCallback *callback);
	void registerDataCallback(UBCBlueprintRelayCallProxyBase *callback);
	void deregisterDataCallback();

	bool send(TArray<uint8> in_data, uint8 in_target, bool in_reliable = true, bool in_ordered = true, int in_channel = 0);
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
