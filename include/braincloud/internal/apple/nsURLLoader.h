//
//  watchOSURLLoader.hpp
//  BrainCloudCpp
//
//  Created by Mario Couture on 2016-04-27.
//  Copyright © 2016 BitHeads Inc. All rights reserved.
//

#ifndef _NSURLLOADER_H_
#define _NSURLLOADER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <pthread.h>
#include <string>

#include "braincloud/internal/URLLoader.h"

#if defined (__OBJC__)
#import <Foundation/Foundation.h>
@interface URLSessionDelegate : NSObject<NSURLSessionDataDelegate>
@end
#else
class URLSessionDelegate;
#endif

namespace BrainCloud
{
    class nsURLLoader : virtual public URLLoader
    {
    public:
        // Destructor
        virtual ~nsURLLoader();

        // Override the pure virtual methods.
        virtual void    close();
        virtual void    load(URLRequest const &);
        virtual void    load(URLRequest const * r) { if (r != NULL) load(*r); }
        virtual bool    isDone();

        /*
         Time in milliseconds that you allow the libcurl transfer operation to take.
         Normally, name lookups can take a considerable time and limiting operations to less than a few minutes
         risk aborting perfectly normal operations. This option will cause curl to use the SIGALRM to enable time-outing
         system calls.

         If libcurl is built to use the standard system name resolver,
         that portion of the transfer will still use full-second resolution for timeouts with a minimum timeout
         allowed of one second. (Added in 7.16.2)
         */
        virtual void setTimeout(int milliseconds) { _timeoutInterval = milliseconds; }
        virtual int  getTimeout() { return static_cast<int>(_timeoutInterval); }
        //FIXME: Maybe this should be obfuscated.
        void setThreadRunning(bool running) { _threadRunning = running; }

    protected:
        friend class URLLoader;

        // Constructors
        nsURLLoader();

    private:

        URLSessionDelegate * _sessionDelegate;

        static bool     _initialized;
        static long     _timeoutInterval;

        bool            _threadRunning;
    };
}


#endif /* _NSURLLOADER_H_ */
