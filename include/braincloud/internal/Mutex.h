#ifndef _MUTEX_H_
#define _MUTEX_H_

#if defined(USE_PTHREAD)
#include <memory.h>

// compilers later than vs2010 define the timespec struct
#if defined(WIN32)
#if (_MSC_VER > 1600)
#define HAVE_STRUCT_TIMESPEC 1
#endif
#endif
#include <pthread.h>

namespace BrainCloud
{
    class Mutex
    {
    public:
        Mutex()
        {
            memset(&_mutex, 0, sizeof(_mutex));
            int rc = 0;
            rc = pthread_mutex_init(&_mutex, NULL);
            _isValid = (rc == 0);
        }

        virtual ~Mutex()
        {
            if (isValid())
            {
                pthread_mutex_destroy(&_mutex);
            }
        }

        bool isValid() { return _isValid; }

        void lock()
        {
            pthread_mutex_lock(&_mutex);
        }

        void unlock()
        {
            pthread_mutex_unlock(&_mutex);
        }

    private:
        pthread_mutex_t _mutex;
        bool _isValid;
    };

    class RecursiveMutex
    {
    public:
        RecursiveMutex()
        {
            pthread_mutexattr_t mutexAtts;
            pthread_mutexattr_init(&mutexAtts);
            pthread_mutexattr_settype(&mutexAtts, PTHREAD_MUTEX_RECURSIVE);

            memset(&_mutex, 0, sizeof(_mutex));
            int rc = 0;
            rc = pthread_mutex_init(&_mutex, &mutexAtts);
            _isValid = (rc == 0);

            pthread_mutexattr_destroy(&mutexAtts);
        }

        virtual ~RecursiveMutex()
        {
            if (isValid())
            {
                pthread_mutex_destroy(&_mutex);
            }
        }

        bool isValid() { return _isValid; }

        void lock()
        {
            pthread_mutex_lock(&_mutex);
        }

        void unlock()
        {
            pthread_mutex_unlock(&_mutex);
        }

    private:
        pthread_mutex_t _mutex;
        bool _isValid;
    };
}

#else /* USE_PTHREAD */

#include <mutex>

class Mutex
{
public:
    bool isValid() { return true; }

    void lock()
    {
        _mutex.lock();
    }

    void unlock()
    {
        _mutex.unlock();
    }

private:
    std::mutex _mutex;
};

class RecursiveMutex
{
public:
    bool isValid() { return true; }

    void lock()
    {
        _mutex.lock();
    }

    void unlock()
    {
        _mutex.unlock();
    }

private:
    std::recursive_mutex _mutex;
};

#endif /* USE_PTHREAD */

#endif /* _MUTEX_H_ */
