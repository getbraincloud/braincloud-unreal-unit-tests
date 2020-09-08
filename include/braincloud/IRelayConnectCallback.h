//
//  IRelayConnectCallback.h
//  GameClientLib
//
//  Created by David St-Louis on 2020-02-12.
//

#ifndef _IRELAYCONNECTCALLBACK_H_
#define _IRELAYCONNECTCALLBACK_H_

#include <string>

namespace BrainCloud {

    class IRelayConnectCallback
    {
    public:
        virtual ~IRelayConnectCallback() { }

        /**
         * Method called when connection to Relay server was successful
         *
         * @param jsonData - System message with connect success packet
         */
        virtual void relayConnectSuccess(const std::string& jsonResponse) = 0;

        /**
         * Method called when connection to relay failed or got disconnected
         *
         * @param errorMessage - Text message describing the error.
         */
        virtual void relayConnectFailure(const std::string& errorMessage) = 0;
    };

};

#endif /* _IRELAYCONNECTCALLBACK_H_ */
