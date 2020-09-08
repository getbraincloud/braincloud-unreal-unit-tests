//
//  IRelaySystemCallback.h
//  GameClientLib
//
//  Created by David St-Louis on 2020-02-12.
//

#ifndef _IRELAYSYSTEMCALLBACK_H_
#define _IRELAYSYSTEMCALLBACK_H_

#include <string>

namespace BrainCloud
{
    class IRelaySystemCallback
    {
    public:
        virtual ~IRelaySystemCallback() { }

        /**
         * System message from the Relay Service
         *
         * @param jsonResponse - System message in json string.
         */
        virtual void relaySystemCallback(const std::string& jsonResponse) = 0;
    };
};

#endif /* _IRELAYSYSTEMCALLBACK_H_ */
