//
//  cURLLoader.h
//  GameClientLib
//


#ifndef _CURLLOADER_H_
#define _CURLLOADER_H_

#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#else
#include <WinSock2.h>
#include <Windows.h>
// compilers later than vs2010 define the timespec struct
#if (_MSC_VER > 1600)
#define HAVE_STRUCT_TIMESPEC 1
#endif
#endif

#include <pthread.h>
#include <string>

#include "braincloud/internal/URLLoader.h"
#include "curl/curl.h"


class cURLLoader : virtual public URLLoader
{
public:
    // Constructors
    cURLLoader();

    // Destructor
    virtual ~cURLLoader( );

    // Override the pure virtual methods.
    virtual void    close();
    virtual void    load( URLRequest const & );
    virtual void    load( URLRequest const * r )        { if ( r != NULL ) load(*r); }
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

protected:

private:
    static void     * loadThread( void * );

    static void     loadThreadCurl( cURLLoader * );

    static curl_socket_t openSocket(void *data, curlsocktype purpose, struct curl_sockaddr *addr);
    static size_t   readData(char *, size_t, size_t, void *);
    static size_t   writeData( char *, size_t, size_t, void * );
    static size_t   writeHeader( char *, size_t, size_t, void * );

    static bool     _initialized;
    static long     _timeoutInterval;
        
    pthread_attr_t  _threadAttributes;
    pthread_t       _threadId;
    
    bool            _threadRunning;

#ifndef WIN32
    int             _socket;
#else
    SOCKET          _socket;
#endif
};


#endif  // _CURLLOADER_H_
