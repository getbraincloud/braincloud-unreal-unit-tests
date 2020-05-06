// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#ifndef _BRAINCLOUDRELAY_H_
#define _BRAINCLOUDRELAY_H_

#include "braincloud/BrainCloudTypes.h"
#include "braincloud/RelayChannel.h"
#include "braincloud/RelayConnectionType.h"

#include <string>

namespace BrainCloud
{
    static const int RELAY_TO_ALL_PLAYERS = 131;
    static const int RELAY_INVALID_NET_ID = 128;

	class BrainCloudClient;
    class IRelayConnectCallback;
    class IRelayCallback;
    class IRelaySystemCallback;
    class RelayComms;

	class BrainCloudRelay
	{
	public:
		BrainCloudRelay(RelayComms* in_commsLayer, BrainCloudClient* in_client);

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
         *
         * @note SSL option will only work with WEBSOCKET connetion type.
         */
        void connect(eRelayConnectionType in_connectionType, const std::string& host, int port, const std::string& passcode, const std::string& lobbyId, IRelayConnectCallback* in_callback);

        /**
         * Disconnects from the relay server
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
         * Set the ping interval. Ping allows to keep the connection
         * alive, but also inform the player of his current ping.
         * The default is 1000 miliseconds interval. (1 seconds)
         */
        void setPingInterval(int in_intervalMS);

        /**
         * Get the lobby's owner profile Id.
         */
        const std::string& getOwnerProfileId() const;

        /**
         * Returns the profileId associated with a netId.
         */
        const std::string& getProfileIdForNetId(int in_netId) const;

        /**
         * Returns the netId associated with a profileId.
         */
        int getNetIdForProfileId(const std::string& in_profileId) const;

        /**
         * Register callback for relay messages coming from peers.
         *
         * @param callback Called whenever a relay message was received.
         */
        void registerRelayCallback(IRelayCallback* in_callback);
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
        void deregisterSystemCallback();

        /**
         * Send a packet to peer(s)
         *
         * @param data Byte array for the data to send
         * @param size Size of data in bytes
         * @param toNetId The net id to send to, TO_ALL_PLAYERS to relay to all.
         * @param reliable Send this reliable or not.
         * @param ordered Receive this ordered or not.
         * @param channel One of: (CHANNEL_HIGH_PRIORITY_1, CHANNEL_HIGH_PRIORITY_2, CHANNEL_NORMAL_PRIORITY, CHANNEL_LOW_PRIORITY)
         */
        void send(const uint8_t* in_data, int in_size, int in_toNetId, bool in_reliable, bool in_ordered, eRelayChannel in_channel);

	private:
        RelayComms* m_commsLayer;
		BrainCloudClient* m_client;
	};
};

#endif /* _BRAINCLOUDCHAT_H_ */
