//
//  IRelayCallback.h
//  GameClientLib
//
//  Created by David St-Louis on 2020-02-12.
//

#ifndef _IRELAYCALLBACK_H_
#define _IRELAYCALLBACK_H_

#include <cinttypes>

namespace BrainCloud
{
    class IRelayCallback
    {
    public:
        virtual ~IRelayCallback() { }

        /**
         * Relay message from the Relay Service
         *
         * @param netId - Net Id of the member this message is from.
         * @param bytes - Data received
         * @param size - Size of data in bytes
         */
        virtual void relayCallback(int netId, const uint8_t* bytes, int size) = 0;
    };
};

#endif /* _IRELAYCALLBACK_H_ */
