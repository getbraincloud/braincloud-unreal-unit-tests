//
//  TimeUtil.h
//  BrainCloudLib
//


#ifndef _TIMEUTIL_H_
#define _TIMEUTIL_H_

#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud {

    class TimeUtil
    {
    public:
        static int64_t getCurrentTimeMillis();
        static void sleepMillis(int millis);
    };

}

#endif
