#ifndef _URLLOADER_H_
#define _URLLOADER_H_

#include "URLLoaderClient.h"
#include "URLRequest.h"

namespace BrainCloud
{
    class URLLoader {

    public:
        static URLLoader* create();

        virtual ~URLLoader();

        virtual void        close() = 0;
        virtual void        load(URLRequest const &) = 0;
        virtual void        load(URLRequest const *) = 0;
        virtual void        setTimeout(int milliseconds) = 0;
        virtual bool        isDone() = 0;

        URLRequest const    getRequest() const { return _urlRequest; }
        URLResponse &       getResponse() { return _urlResponse; }
        void                setRequest(URLRequest const & r) { _urlRequest = r; }
        void                setLoggingEnabled(bool in_enabled) { _loggingEnabled = in_enabled; }

    protected:
        URLLoader();

    protected:
        URLRequest          _urlRequest;
        URLResponse         _urlResponse;
        bool                _loggingEnabled;
    };
}


#endif  // _URLLOADER_H_
