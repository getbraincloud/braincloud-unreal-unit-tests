//
//  XMLHTTPRequestLoader.h
//  GameClientLib
//

#ifndef _XMLHTTPREQUESTLOADER_H_
#define _XMLHTTPREQUESTLOADER_H_

#include "braincloud/internal/URLLoader.h"

#include <atomic>
#include <mutex>

#include <msxml6.h>

namespace BrainCloud
{
    class XMLHTTPRequestLoader : public URLLoader
    {
    public:
        // Destructor
        virtual ~XMLHTTPRequestLoader();

        // Override the pure virtual methods.
        virtual void close();
        virtual void load(URLRequest const &);
        virtual void load(URLRequest const * r) { if (r != NULL) load(*r); }
        virtual bool isDone();

        virtual void setTimeout(int milliseconds) { _timeoutInterval = milliseconds; }

        void onError(int httpCode);
        void onSuccess(const std::string& response, int httpCode);

    protected:
        friend class URLLoader;

        XMLHTTPRequestLoader();

    private:
        static void* loadThread(void*);
        static void loadThreadXMLHTTPRequest(XMLHTTPRequestLoader*);

        static long _timeoutInterval;

        std::atomic<bool> _threadRunning;
        std::mutex _requestMutex;
        IXMLHTTPRequest2* _pRequest;
    };
}

#endif  // _XMLHTTPREQUESTLOADER_H_
