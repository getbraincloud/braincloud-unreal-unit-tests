//
//  cURLLoader.h
//  GameClientLib
//


#ifndef _CURLLOADER_H_
#define _CURLLOADER_H_


#include <pthread.h>
#include <string>
#include "URLLoader.h"


class cURLLoader : virtual public URLLoader {

public:
    // Constructors
	cURLLoader( URLLoaderClient * = NULL );
    cURLLoader( cURLLoader const & );
    cURLLoader( URLRequest const & );
    cURLLoader( URLRequest const * );

    // Destructor
    virtual ~cURLLoader( );

    // Override the pure virtual methods.
    virtual void    close();
    virtual void    load( URLRequest const & );
    virtual void    load( URLRequest const * r )        { if ( r != NULL ) load(*r); }
	
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

    static size_t   parseData( char *, size_t, size_t, URLResponse * );
    static size_t   parseHeader( char *, size_t, size_t, URLResponse * );

    static bool     _initialized;
	static long     _timeoutInterval;

	// CThread _thread;
	
    pthread_attr_t  _threadAttributes;
    pthread_t       _threadId;
	
    bool            _threadRunning;

};  // end class


#endif  // _CURLLOADER_H_
