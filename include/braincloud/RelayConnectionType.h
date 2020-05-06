// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#ifndef _RELAYCONNECTIONTYPE_H_
#define _RELAYCONNECTIONTYPE_H_

namespace BrainCloud
{
    /*
     * Connection protocol to use when connected to a relay server.
     *
     * UDP - For real time games where speed is crutial
     * TCP - When latency is not crutial, but everything needs to be guaranteed and 
     *       in order like a chat app, monitoring system, turn based games, etc.
     * WS  - Perfect for web based games. The slowest option, but the only one for browers.
     * WSS - Won't connect with current servers (4.4.1)
     *
     * Note that all protocols can coexist between different users connected to the
     * same Relay Server. Meaning someone could play on PC using UDP, and be in the
     * same match as someone else playing on browser with WS.
     */
    enum class eRelayConnectionType : int
    {
        UDP = 0, /* User Datagram Protocol */
        TCP = 1, /* Transmission Control Protocol */
        WS  = 2, /* WebSocket */
        WSS = 3  /* WebSocket Secure */
    };
};

#endif /* _RELAYCONNECTIONTYPE_H_ */
