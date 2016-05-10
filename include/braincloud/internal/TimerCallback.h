//
//  TimerCallback.h
//  BrainCloudLib
//


#ifndef _TIMERCALLBACK_H_
#define _TIMERCALLBACK_H_


namespace BrainCloud {


    class Timer;    // Forward Declaration


    class TimerCallback {

    public:
        virtual ~TimerCallback( )   { }

        virtual void handleAlarm( Timer * ) = 0;

    protected:

    private:

    };  // end class


}  // end namespace


#endif  // _TIMERCALLBACK_H_
