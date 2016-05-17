//
//  Timer.h
//  BrainCloudLib
//


#ifndef _TIMER_H_
#define _TIMER_H_


#include <pthread.h>
#include "TimerCallback.h"
#include "braincloud/BrainCloudTypes.h"


namespace BrainCloud {


class Timer {
public:
    typedef enum
    {
        TIMER_PAUSED,   // Default setting until the Timer gets started.
        TIMER_RINGING,  // Timer is ringing the alarm.
        TIMER_RUNNING,  // Waiting for an interval to complete.
        TIMER_STARTED,  // Timer has been started, but interval not applied yet.
        TIMER_STOPPED   // Finished with the Timer - safe to destroy.
    } TimerState;

    Timer( TimerCallback *, unsigned long, void *, bool = false );

    TimerCallback   * getCallback( ) const  { return _callback; }
    unsigned long   getInterval( ) const    { return _interval; }
    TimerState      getState( ) const       { return _state; }
    void            * getUserData( ) const  { return _userData; }
    bool            willRepeat( ) const     { return _willRepeat; }

    void    pause( )    { setState(TIMER_PAUSED); }
    void    resume( )   { setState(TIMER_RUNNING); }
    void    stop( );    // Destroys Timer object
    virtual ~Timer( );
    
    static int64_t getCurrentTimeMillis();
protected:

private:
    

    void            microSleep( unsigned long );
    void            milliSleep( unsigned long s )   { microSleep(s * 1000); }
    static void     * runLoop( void * );

    void            setState( TimerState const & );
    void            start( )    { setState(TIMER_STARTED); }

    TimerCallback   * _callback;
    unsigned long   _interval;
    TimerState      _state;
    pthread_t       _thread;
    pthread_cond_t  _timerCondition;
    pthread_mutex_t _timerMutex;
    void            * _userData;
    bool            _willRepeat;

};  // end class


}  // end namespace


#endif  // _TIMER_H_
