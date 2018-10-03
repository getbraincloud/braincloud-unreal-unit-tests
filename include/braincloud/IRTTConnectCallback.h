//
//  IRTTConnectCallback.h
//  GameClientLib
//
//  Created by David St-Louis on 2018-08-09.
//

#ifndef _IRTTCONNECTCALLBACK_H_
#define _IRTTCONNECTCALLBACK_H_

#include <string>

namespace BrainCloud {
    
    class IRTTConnectCallback
    {
    public:
        virtual ~IRTTConnectCallback( )  { }
        
        /**
         * Method called when connection to RTT was successful
         */
        virtual void rttConnectSuccess() = 0;
        
        /**
         * Method called when connection to RTT failed
         *
         * @param errorMessage - Text message describing the error.
         */
        virtual void rttConnectFailure(const std::string& errorMessage) = 0;
    };
    
};

#endif /* _IRTTCONNECTCALLBACK_H_ */
