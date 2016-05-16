//
//  TimeUtil.cpp
//  BrainCloudLib
//

#include <iostream>

#if __cplusplus >= 201103L && !defined(__ANDROID__)
#include <iostream>
#include <chrono>
#include <thread>
#endif

extern "C" {

#if !defined(WIN32) && !defined(WINAPI_FAMILY)
    #ifdef HG_PLATFORM_BB
        #include <errno.h>
        #include <sys/time.h>
    #else
        #include <sys/time.h>
    #endif
    #include <unistd.h>
#else

#include <time.h>
#include <WinSock2.h>
#include <windows.h>


#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

int gettimeofday(struct timeval *tv, char* NULLPTR)
{
// Define a structure to receive the current Windows filetime
  FILETIME ft;
 
// Initialize the present time to 0 and the timezone to UTC
  unsigned __int64 tmpres = 0;
  static int tzflag = 0;
 
  if (NULL != tv)
  {
    GetSystemTimeAsFileTime(&ft);
 
// The GetSystemTimeAsFileTime returns the number of 100 nanosecond 
// intervals since Jan 1, 1601 in a structure. Copy the high bits to 
// the 64 bit tmpres, shift it left by 32 then or in the low 32 bits.
    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;
 
// Convert to microseconds by dividing by 10
    tmpres /= 10;
 
// The Unix epoch starts on Jan 1 1970.  Need to subtract the difference 
// in seconds from Jan 1 1601.
    tmpres -= DELTA_EPOCH_IN_MICROSECS;
 
// Finally change microseconds to seconds and place in the seconds value. 
// The modulus picks up the microseconds.
    tv->tv_sec = (long)(tmpres / 1000000UL);
    tv->tv_usec = (long)(tmpres % 1000000UL);
  }
 
  return 0;
}

#endif
}

#include "braincloud/internal/TimeUtil.h"


namespace BrainCloud
{
    int64_t TimeUtil::getCurrentTimeMillis()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        
        int64_t timeMillis;
        timeMillis = tv.tv_sec;
        timeMillis *= 1000;
        timeMillis += (tv.tv_usec / 1000);
        return timeMillis;
    }


    void TimeUtil::sleepMillis(int millis)
    {
#if __cplusplus >= 201103L && !defined(__ANDROID__)
        auto sleep = std::chrono::milliseconds(millis);
        std::this_thread::sleep_for(sleep);
#elif defined(WP8)
        // sadly Sleep n/a on windows phone 8.0
        WaitForSingleObjectEx(GetCurrentThread(), millis, TRUE);
#elif defined (WIN32) || defined(WINAPI_FAMILY)
        Sleep(millis);
#else
        usleep(millis * 1000);
#endif
    }
}

