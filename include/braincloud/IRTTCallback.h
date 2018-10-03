//
//  IRTTConnectCallback.h
//  GameClientLib
//
//  Created by David St-Louis on 2018-08-09.
//

#ifndef _IRTTCALLBACK_H_
#define _IRTTCALLBACK_H_

#include <string>

#include <json/json.h>

namespace BrainCloud {
    
    class IRTTCallback
    {
    public:
        virtual ~IRTTCallback( )  { }
        
        /**
         * Method called on RTT events
         *
         * @param eventJson - Data for the event.
         */
        virtual void rttCallback(const Json::Value& eventJson) = 0;
    };
    
};

#endif /* _IRTTCALLBACK_H_ */
