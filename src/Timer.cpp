//
//  Timer.cpp
//  BrainCloudLib
//

#if !defined(WINAPI_FAMILY)

#include <iostream>

extern "C" {
#if !defined(WIN32)
	#ifdef HG_PLATFORM_BB
		#include <errno.h>
		#include <sys/time.h>
	#else
		//#include <sys/errno.h>
		#include <sys/time.h>
	#endif
#else

#include <WinSock2.h>
#include <windows.h>
#include <time.h>

// compilers later than vs2010 define the timespec struct
#if (_MSC_VER > 1600)
#define HAVE_STRUCT_TIMESPEC 1
#endif

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
	// Definition of a gettimeofday function
 
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
#include "braincloud/internal/Timer.h"


namespace BrainCloud {


    /**
     * Constructor
     *
     * @param callback
     * @param interval
     * @param userData
     * @param willRepeat
     */
    Timer::Timer( TimerCallback * callback, unsigned long interval,
                 void * userData, bool willRepeat )
        : _callback(callback), _interval(interval), _state(TIMER_PAUSED),
          _userData(userData), _willRepeat(willRepeat) {


        // Initialize the Condition and Mutex.
        pthread_cond_init(&_timerCondition, NULL);
        pthread_mutex_init(&_timerMutex, NULL);

        // Create a thread the for timer.
		pthread_create( &_thread, NULL, &runLoop, (void *)this );

        // Start the timer.
        start( );

    }  // end Timer::Timer


    /**
     * Destructor
     */
    Timer::~Timer( ) {


        stop();


        pthread_join(_thread, NULL);

        // Destroy the Conditional and Mutex.

        pthread_cond_destroy(&_timerCondition);
        pthread_mutex_destroy(&_timerMutex);


    }  // end Timer::~Timer


    /*
     * Public Methods
     */


    /**
     * Stop the Timer.
     */
    void Timer::stop( ) {


        // It is possible the Timer is currently sleeping.
        // Or, it might already be stopped.
        if ( _state == TIMER_RINGING )
        {
            // If the Timer is currently ringing, the mutex is currently locked,
            // but the condition is not set, and the handleAlarm() routine must
            // have called the stop() routine.  It should be safe to change the
            // state.

            _state = TIMER_STOPPED;
        } else if ( _state != TIMER_STOPPED ) {
            // The Timer is not already stopped.
            // It must be waiting on the condition.

            // Get the lock on the Mutex.
            pthread_mutex_lock(&_timerMutex);


            _state = TIMER_STOPPED;

        // Send a signal to the Timer to wake up from sleep.

            pthread_cond_signal(&_timerCondition);

            pthread_mutex_unlock(&_timerMutex);
        }  // end if


    }  // end Timer::stop

    int64_t Timer::getCurrentTimeMillis()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        
        int64_t timeMillis;
        timeMillis = tv.tv_sec;
        timeMillis *= 1000;
        timeMillis += (tv.tv_usec / 1000);
        return timeMillis;
    }

    /*
     * Protected Methods
     */


    /*
     * Private Methods
     */


    /**
     * Sleep for a number of microseconds.
     *
     * @param microSeconds
     */
    void Timer::microSleep( unsigned long microSeconds ) {


		// Use the select() call to implement the sleep.
        struct timeval tv;
        gettimeofday(&tv, NULL);

        struct timespec ts;
        ts.tv_sec = tv.tv_sec + (microSeconds / 1000000);
        ts.tv_nsec = 1000 * (tv.tv_usec + (microSeconds % 1000000));

        // Sleep for the specified time period.
        // However, we need a way to interrupt the sleep.
        // Therefore, use the conditional timed wait pthread call.
        //int rc =
        pthread_cond_timedwait(&_timerCondition, &_timerMutex, &ts);

        //if ( rc != ETIMEDOUT ) {
            // We expect it to time out.
            // If it doesn't time out, it means someone has tried to stop the
            // Timer.
        //}  // end if


    }  // end Timer::microSleep


    /**
     * Run the main loop for the Timer thread.
     *
     * @param theTimer - Timer object
     */
    void * Timer::runLoop( void * theTimer ) {

        void * pointer = NULL;

        // Make sure the timer object has been specified.
        if ( theTimer != NULL ) {
            // Convert the pointer to the proper class.
            Timer * timer = reinterpret_cast<Timer *>(theTimer);

            bool isRunning = true;

            while ( isRunning ) {

                // Get the lock on the mutex.
                // We need to be sure we have the current state of the Timer
                // before entering the switch statement.
                pthread_mutex_lock(&timer->_timerMutex);


                switch( timer->getState() ) {
                    case TIMER_PAUSED:

                        timer->milliSleep(50); // Poll again in 50 milliseconds.
                        break;

                    case TIMER_RUNNING:
                    {

                        timer->_state = TIMER_RINGING;
                        TimerCallback * callback = timer->getCallback();

                        // Let the callback know the alarm has fired.
                        if ( callback != NULL ) {
                            callback->handleAlarm(timer);
                        }  // end if

                        // Check if the Timer is allowed to repeat.
                        if ( timer->willRepeat() ) {
                            // It is possible the user has stopped the Timer
                            // in the handleAlarm() routine.  The Timer should
                            // still be ringing in order to proceed.
                            if ( timer->_state == TIMER_RINGING ) {
                                timer->_state = TIMER_RUNNING;
                                timer->milliSleep(timer->getInterval());
                            }  // end if
                        } else {
                            timer->_state = TIMER_STOPPED;
                        }  // end if
                        break;
                    }  // end case

                    case TIMER_STARTED:

                        // Change the state of the Timer.
                        timer->_state = TIMER_RUNNING;

                        // Sleep the proper amount of time.
                        timer->milliSleep(timer->getInterval());
                        break;

                    case TIMER_STOPPED:

                        isRunning = false;
                        break;

                    default:
                        break;
                }  // end switch

                // Release the lock - if only for a nanosecond.

                pthread_mutex_unlock(&timer->_timerMutex);
            }  // end while

            // The Timer has been stopped and can be destroyed.
            delete timer;
        }  // end if


        return pointer;
    }  // end Timer::runLoop


    /**
     * Set the state of the Timer.
     */
    void Timer::setState( TimerState const & state ) {


        pthread_mutex_lock(&_timerMutex);
        _state = state;
        pthread_mutex_unlock(&_timerMutex);


    }  // end Timer::setState

}  // end namespace

#endif
