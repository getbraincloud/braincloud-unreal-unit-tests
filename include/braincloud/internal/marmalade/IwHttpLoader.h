//
//  IwHttpLoader.h
//

#if defined(IW_SDK)

#ifndef _IWHTTPLOADER_H_
#define _IWHTTPLOADER_H_

#include <pthread.h>
#include <string>

#include "braincloud/internal/URLLoader.h"

#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#else
#include <WinSock2.h>
#endif

class CIwHTTP;
namespace BrainCloud
{

    class IwHttpLoader : virtual public URLLoader
    {
    public:
        virtual ~IwHttpLoader();

        virtual void    close();
        virtual void    load(URLRequest const &);
        virtual void    load(URLRequest const * r) { if (r != NULL) load(*r); }
        virtual bool    isDone();
        virtual void    setTimeout(int milliseconds) { _timeoutMillis = milliseconds; }

    protected:
        friend class URLLoader;

        IwHttpLoader();

    private:
        enum eIwHttpLoaderState
        {
            StatusNone = 0,
            StatusHttpSendingRequest,
            StatusHttpReadingResponse,
            StatusCanceled, // this number or higher, isDone() returns true
            StatusCompleteFailed,
            StatusCompleteSuccess
        };

        static int32_t  statusCallback(void *systemData, void *userData);
        static int32_t  readCallback(void *systemData, void *userData);

        void            setNetworkErrorResponse();

        eIwHttpLoaderState  _state;
        CIwHTTP             *_iwhttp;
        int                 _timeoutMillis;
        char                _readBuffer[2048];
    };

}
#endif  // _IWHTTPLOADER_H_

#endif //!__ANDROID__