//
//  URLLoader.cpp
//  GameClientLib
//


#if ( defined(GAMECLIENT_DEBUGLEVEL)  &&  GAMECLIENT_DEBUGLEVEL > 0 )
#   include <iostream>
#endif
#include <cctype>

#ifdef HG_PLATFORM_BB
	#include <stdio.h>
	#include <ctype.h>
#endif

#include "curl/curl.h"
#include "cURLLoader.h"
#include "URLRequestMethod.h"
#include "http_codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool cURLLoader::_initialized = false;
long cURLLoader::_timeoutInterval = 0;

/**
 * Constructor
 *   - NOTE:  If a URLRequest is given, the object will try to contact the
 *            server immediately by calling the load() method.
 */
cURLLoader::cURLLoader( URLLoaderClient * client )
    : URLLoader(client)
    , _threadRunning(false)
{
    memset(&_threadId, 0, sizeof(pthread_t));
    memset(&_threadAttributes, 0, sizeof(_threadAttributes));
}  // end URLLoader::URLLoader

cURLLoader::cURLLoader( cURLLoader const & urlLoader )
    : URLLoader(urlLoader), _threadRunning(false)
{
    memset(&_threadId, 0, sizeof(pthread_t));
    memset(&_threadAttributes, 0, sizeof(_threadAttributes));
}  // end URLLoader::URLLoader

cURLLoader::cURLLoader( URLRequest const & urlRequest )
    : _threadRunning(false)
{
    memset(&_threadId, 0, sizeof(pthread_t));
    memset(&_threadAttributes, 0, sizeof(_threadAttributes));
    load( urlRequest );
}  // end cURLLoader::cURLLoader

cURLLoader::cURLLoader( URLRequest const * urlRequest )
    : _threadRunning(false)
{
    memset(&_threadId, 0, sizeof(pthread_t));
    memset(&_threadAttributes, 0, sizeof(_threadAttributes));
    load( urlRequest );
}  // end URLLoader::URLLoader


/**
 * Destructor
 */
cURLLoader::~cURLLoader( ) {

    close();

}  // end cURLLoader::~cURLLoader


/*
 * Public Methods
 */


/**
 * Close a currently running load operation, if in progress.
 */
void cURLLoader::close() {

    // We can stop loading the page by killing its thread.
    if ( _threadRunning ) {
        pthread_attr_destroy(&_threadAttributes);
        _threadRunning = false;
    }  // end if


}  // end cURLLoader::close


/**
 * Issue an HTTP Request to the remote server, and load the response.
 *
 * @param urlRequest - HTTP Request
 */
void cURLLoader::load( URLRequest const & urlRequest ) {

    // Assume the specified URL in the request is valid.
    setRequest(urlRequest);

    if ( ! _initialized ) {
        // Initialize libcurl before any threads are started.
        curl_global_init(CURL_GLOBAL_ALL);

        _initialized = true;
    }  // end if
    
    // load is sometimes called while prev thread is processing
    // so make sure to cleanup beforehand...
    close();

    // Start up a thread to load the web page.
    // Set up a new thread to handle the request.
    int rc = 0;
    rc = pthread_attr_init(&_threadAttributes);

    if ( rc == 0 ) {
        // Set the thread to detach when launched.
        rc = pthread_attr_setdetachstate(&_threadAttributes,
                                         PTHREAD_CREATE_DETACHED);
        if ( rc == 0 ) {
            // Launch the thread.
            _threadRunning = true;
            rc = pthread_create(&_threadId, &_threadAttributes, &loadThread,
                                this);
            if ( rc == 0 ) {
                // Launched
            } else {
                // Error
                close();
            }  // end if
        } else {
            // Error
            pthread_attr_destroy(&_threadAttributes);
        }  // end if
    } else {
        // Error
    }  // end if


}  // end cURLLoader::load


/*
 * Protected Methods
 */


/*
 * Private Methods
 */


/**
 * This is the writer call back function used by curl
 *
 * @param data - data received from the remote server
 * @param size - size of a character (?)
 * @param nmemb - number of characters
 * @param response - pointer to the object to receive the data
 *
 * @return int - number of characters received (should equal size * nmemb)
 */
size_t cURLLoader::parseData( char * data, size_t size, size_t nmemb,
                             URLResponse * response ) {


    // What we will return
    size_t result = 0;

    // Check for a valid response object.
    if ( response != NULL ) {
        // Append the data to the buffer
        response->addData(std::string(data, size * nmemb));

        // How much did we write?
        result = size * nmemb;
    }  // end if



    return result;
}  // end cURLLoader::parseData


/**
 * This static method is called once per HTTP response header line.
 *
 * NOTE:  The initial HTTP status line is also sent to this function.
 *
 * @param line - string containing the header line
 * @param size - size of a character (?)
 * @param nmemb - number of characters
 * @param response - pointer to the object to receive the response
 */
size_t cURLLoader::parseHeader( char * line, size_t size, size_t nmemb,
                               URLResponse * response ) {


    size_t num_processed = 0;   // Number of bytes processed for this header
                                // -1 means terminate URL request with an error

    // Check for a valid response object.
    if ( response != NULL ) {
        // Parse the header line for Header: Value
        std::string headerLine(line, size * nmemb);
        std::string::size_type colon = headerLine.find(':');

        // Make sure the line contains a colon.
        if ( colon != std::string::npos ) {
            // The header name consists of everything up to the colon.
            URLRequestHeader header(headerLine.substr(0, colon));

            // The value starts at the first non-space after the colon.
            for ( colon += 1; colon < headerLine.length(); colon += 1 ) {
                if ( ! isspace(headerLine[colon]) ) {
                    header.setValue(headerLine.substr(colon));
                    break;
                }  // end if
            }  // end for

            // Add the new header to the response.
            response->addHeader(header);
        }  // end if

        // We have processed the entire header message.
        num_processed = size * nmemb;
    }  // end if



    return num_processed;
}  // end cURLLoader::parseHeader


/**
 * This static method is the target of the thread creation.
 * Load up the proper reference to the object, and complete loading the page.
 *
 * @param urlLoader - pointer to the object which is loading the web page
 */
void * cURLLoader::loadThread( void * urlLoader ) {


    // This is the starting point of a new thread.
    // A pointer to the object should have been passed as urlLoader.
    // Verify the pointer.
    if ( urlLoader != NULL ) {
        cURLLoader * loader = reinterpret_cast<cURLLoader *>(urlLoader);

        // We now have a pointer to the actual object loading the remote URL.
        // Make the request.
        loadThreadCurl( loader );
    }  // end if



    return NULL;
}  // end cURLLoader::loadThread

#include <stdio.h>


static
void dump(const char *text,
          FILE *stream, unsigned char *ptr, size_t size)
{
    size_t i;
    size_t c;
    unsigned int width=0x10;
    
    fprintf(stream, "%s, %10.10ld bytes (0x%8.8lx)\n",
            text, (long)size, (long)size);
    
    for(i=0; i<size; i+= width) {
        fprintf(stream, "%4.4lx: ", (long)i);
        
        /* show hex to the left */
        for(c = 0; c < width; c++) {
            if(i+c < size)
                fprintf(stream, "%02x ", ptr[i+c]);
            else
                fputs("   ", stream);
        }
        
        /* show data on the right */
        for(c = 0; (c < width) && (i+c < size); c++)
            fputc((ptr[i+c]>=0x20) && (ptr[i+c]<0x80)?ptr[i+c]:'.', stream);
        
        fputc('\n', stream); /* newline */
    }
}


static
int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
    const char *text;
    (void)handle; /* prevent compiler warning */
    
    switch (type) {
        case CURLINFO_TEXT:
            fprintf(stderr, "== Info: %s", data);
        default: /* in case a new one is introduced to shock us */
            return 0;
            
        case CURLINFO_HEADER_OUT:
            text = "=> Send header";
            break;
        case CURLINFO_DATA_OUT:
            text = "=> Send data";
            break;
        case CURLINFO_SSL_DATA_OUT:
            text = "=> Send SSL data";
            break;
        case CURLINFO_HEADER_IN:
            text = "<= Recv header";
            break;
        case CURLINFO_DATA_IN:
            text = "<= Recv data";
            break;
        case CURLINFO_SSL_DATA_IN:
            text = "<= Recv SSL data";
            break;
    }
    
    dump(text, stderr, (unsigned char *)data, size);
    return 0;
}


/**
 * Use libCurl to load up the web page.
 *
 * @param loader - pointer to the object which is loading the web page
 */
void cURLLoader::loadThreadCurl( cURLLoader * loader ) {
    CURL * curl = curl_easy_init();


    if ( curl != NULL ) {
        CURLcode rc = CURLE_OK;
        char curlError[CURL_ERROR_SIZE];

        // Use an error buffer to store the description of any errors.
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curlError);


        // Set the headers.
        struct curl_slist * headers = NULL;


        std::vector<URLRequestHeader> h = loader->getRequest().getHeaders();
        for ( std::string::size_type i = 0; i < h.size(); i ++ ) {
            std::string headerLine = h[i].getName();
            headerLine.append(": ");
            headerLine.append(h[i].getValue());
            headers = curl_slist_append(headers, headerLine.c_str());
        }  // end for
		

        // Content Type (special header)
        std::string contentType = "Content-Type: ";
        contentType.append(loader->getRequest().getContentType());
        headers = curl_slist_append(headers, contentType.c_str());



        // User Agent (special header)
        if ( loader->getRequest().getUserAgent().length() > 0 ) {
            std::string userAgent = "User-Agent: ";
            userAgent.append(loader->getRequest().getUserAgent());
            headers = curl_slist_append(headers, userAgent.c_str());


        }  // end if

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        URLResponse response;

        // Set up the object to store the content of the response.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parseData);

        // Set up the object to store the response headers.
        curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &response);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, parseHeader);
		
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, (long)0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, (long)0);
        
        //curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, (long)1);
		
		// Only set timeout if it's not 0.
		if (_timeoutInterval)
		{
			curl_easy_setopt(curl, CURLOPT_NOSIGNAL, (long)1);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, _timeoutInterval);
		}
		
        // Determine the type of request being made.
        if ( loader->getRequest().getMethod() == URLRequestMethod::GET ) {


            std::string url = loader->getRequest().getUrl();
            std::string data = loader->getRequest().getData();

            if ( data.length() > 0 ) {
                // Append the request data to the end of the URL.
                url.append("?");
                url.append(data);
            }  // end if

            // Set the URL for the request.
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());


            rc = curl_easy_perform(curl);
        } else if ( loader->getRequest().getMethod() ==
                                                    URLRequestMethod::POST ) {


            // Set the base URL for the request.
            curl_easy_setopt(curl, CURLOPT_URL,
                             loader->getRequest().getUrl().c_str());


            // Create all of the form data.
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE,
                             loader->getRequest().getData().length());

            curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS,
                             loader->getRequest().getData().c_str());


            rc = curl_easy_perform(curl);
        } else if ( loader->getRequest().getMethod() == URLRequestMethod::PUT )
        {


            // Set the base URL for the request.
            curl_easy_setopt(curl, CURLOPT_URL,
                             loader->getRequest().getUrl().c_str());


            // Create all of the form data.
            curl_easy_setopt(curl, CURLOPT_UPLOAD, 1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE,
                             loader->getRequest().getData().length());

            curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS,
                             loader->getRequest().getData().c_str());


            rc = curl_easy_perform(curl);
        } else {
            // Method type not supported.
            rc = CURLE_FAILED_INIT;


        }  // end if

        // Get the HTTP response status code.
		if ( rc == CURLE_OK ) {
            long statusCode;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
            response.setStatusCode(static_cast<unsigned short>(statusCode));
        } else if ( rc == CURLE_OPERATION_TIMEDOUT ) {
        	response.setStatusCode(HTTP_CUSTOM/*408*/);
        	response.setReasonPhrase("Operation timed out");
		}
        else {
            response.setStatusCode(HTTP_CUSTOM);
            response.setReasonPhrase(curlError);
        }

        // Clean up memory.
        if ( headers != NULL ) curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        // We're done.  Fire the appropriate event.
        if ( loader->getClient() != NULL ) {
			loader->getClient()->handleResult(response);
        }  // end if
    } else {
        if ( loader->getClient() != NULL ) {
            URLResponse response;
            response.setStatusCode(503);
            response.setReasonPhrase("cURL Out of Memory");
            loader->getClient()->handleError(response);
        }  // end if
    }  // end if
}  // end cURLLoader::loadThreadCurl
