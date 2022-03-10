// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once
enum class BCRelayConnectionType : uint8;
enum class BCRelayChannel : uint8;
class BrainCloudClient;
class BrainCloudRelayComms;
class UBCBlueprintRelayConnectCallProxyBase;
class UBCBlueprintRelayCallProxyBase;
class UBCBlueprintRelaySystemCallProxyBase;
class IRelayConnectCallback;
class IRelayCallback;
class IRelaySystemCallback;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudRelay
{
public:
    static const uint64 TO_ALL_PLAYERS = 0x000000FFFFFFFFFF;

    BrainCloudRelay(BrainCloudClient *in_client, BrainCloudRelayComms *in_comms);

    /**
     * Start a connection, based on connection type to 
     * brainClouds Relay Servers. Connect options come in
     * from ROOM_ASSIGNED lobby callback.
     * 
     * @param connectionType
     * @param host
     * @param port
     * @param passcode
     * @param lobbyId
     * @param callback Callback objects that report Success or Failure|Disconnect.
     */
    void connect(BCRelayConnectionType in_connectionType, const FString &host, int port, const FString &passcode, const FString &lobbyId, IRelayConnectCallback *in_callback);

    /** 
     * Disables relay event for this session.
     */
    void disconnect();

    /**
     * Returns whether or not we have a successful connection with
     * the relay server.
     */
    bool isConnected() const;

    /**
     * Get the current ping for our user.
     * Note: Pings are not distributed among other members. Your game will
     * have to bundle it inside a packet and distribute to other peers.
     */
    int getPing() const;

    /**
     * Get the lobby's owner profile Id.
     */
    const FString &getOwnerProfileId() const;

    /**
     * Get the lobby's owner Connection Id.
     */
    const FString &getOwnerCxId() const;

    /**
     * Returns the profileId associated with a netId.
     */
    const FString &getProfileIdForNetId(int in_netId) const;

    /**
     * Returns the netId associated with a profileId.
     */
    int getNetIdForProfileId(const FString &in_profileId) const;

    /**
     * Returns the connection Id associated with a netId.
     */
    const FString &getCxIdForNetId(int in_netId) const;

    /**
     * Returns the netId associated with a connection Id.
     */
    int getNetIdForCxId(const FString &in_cxId) const;

    /**
     * Register callback for relay messages coming from peers.
     *
     * @param callback Called whenever a relay message was received.
     */
    void registerRelayCallback(IRelayCallback *in_callback);
    void registerRelayCallback(UBCBlueprintRelayCallProxyBase *in_callback);
    void deregisterRelayCallback();

    /**
     * Register callback for RelayServer system messages.
     *
     * @param callback Called whenever a system message was received. function(json)
     *
     * # CONNECT
     * Received when a new member connects to the server.
     * {
     *   op: "CONNECT",
     *   profileId: "...",
     *   ownerId: "...",
     *   netId: #
     * }
     *
     * # NET_ID
     * Receive the Net Id assossiated with a profile Id. This is
     * sent for each already connected members once you
     * successfully connected.
     * {
     *   op: "NET_ID",
     *   profileId: "...",
     *   netId: #
     * }
     *
     * # DISCONNECT
     * Received when a member disconnects from the server.
     * {
     *   op: "DISCONNECT",
     *   profileId: "..."
     * }
     *
     * # MIGRATE_OWNER
     * If the owner left or never connected in a timely manner,
     * the relay-server will migrate the role to the next member
     * with the best ping. If no one else is currently connected
     * yet, it will be transferred to the next member in the
     * lobby members' list. This last scenario can only occur if
     * the owner connected first, then quickly disconnected.
     * Leaving only unconnected lobby members.
     * {
     *   op: "MIGRATE_OWNER",
     *   profileId: "..."
     * }
     */
    void registerSystemCallback(IRelaySystemCallback* in_callback);
    void registerSystemCallback(UBCBlueprintRelaySystemCallProxyBase *in_callback);
    void deregisterSystemCallback();

    /**
     * Send a packet to peer(s)
     *
     * @param data Byte array for the data to send
     * @param toNetId The net id to send to, TO_ALL_PLAYERS to relay to all.
     * @param reliable Send this reliable or not.
     * @param ordered Receive this ordered or not.
     * @param channel One of: (CHANNEL_HIGH_PRIORITY_1, CHANNEL_HIGH_PRIORITY_2, CHANNEL_NORMAL_PRIORITY, CHANNEL_LOW_PRIORITY)
     */
    void send(const TArray<uint8> &in_data, uint64 toNetId, bool in_reliable, bool in_ordered, BCRelayChannel in_channel);

    /**
     * Send a packet to any players by using a mask
     *
     * @param data Byte array for the data to send
     * @param playerMask Mask of the players to send to. 0001 = netId 0, 0010 = netId 1, etc. If you pass ALL_PLAYER_MASK you will be included and you will get an echo for your message. Use sendToAll instead, you will be filtered out. You can manually filter out by : ALL_PLAYER_MASK &= ~(1 << myNetId)
     * @param reliable Send this reliable or not.
     * @param ordered Receive this ordered or not.
     * @param channel One of: (CHANNEL_HIGH_PRIORITY_1, CHANNEL_HIGH_PRIORITY_2, CHANNEL_NORMAL_PRIORITY, CHANNEL_LOW_PRIORITY)
     */
    void sendToPlayers(const TArray<uint8> &in_data, uint64 in_playerMask, bool in_reliable, bool in_ordered, BCRelayChannel in_channel);

    /**
     * Send a packet to all except yourself
     *
     * @param data Byte array for the data to send
     * @param reliable Send this reliable or not.
     * @param ordered Receive this ordered or not.
     * @param channel One of: (CHANNEL_HIGH_PRIORITY_1, CHANNEL_HIGH_PRIORITY_2, CHANNEL_NORMAL_PRIORITY, CHANNEL_LOW_PRIORITY)
     */
    void sendToAll(const TArray<uint8> &in_data, bool in_reliable, bool in_ordered, BCRelayChannel in_channel);

private:
    BrainCloudClient *_client = nullptr;
    BrainCloudRelayComms *_relayComms = nullptr;
};
