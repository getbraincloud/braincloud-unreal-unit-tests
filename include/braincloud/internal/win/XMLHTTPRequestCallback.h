#ifndef _XMLHTTPREQUESTCALLBACK_H_
#define _XMLHTTPREQUESTCALLBACK_H_

#include <functional>
#include <mutex>

#include <msxml6.h>

namespace BrainCloud
{
    class XMLHTTPRequestCallback : public IXMLHTTPRequest2Callback
    {
    public:
        XMLHTTPRequestCallback(
            const std::function<void(const std::string&, int)>& onSuccess,
            const std::function<void(int)>& onError);
        virtual ~XMLHTTPRequestCallback();

        HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID riid,
            _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObj) override;

        ULONG STDMETHODCALLTYPE AddRef(void) override;

        ULONG STDMETHODCALLTYPE Release(void) override;

        HRESULT STDMETHODCALLTYPE OnRedirect(
            /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
            /* [string][in] */ __RPC__in_string const WCHAR *pwszRedirectUrl) override;

        HRESULT STDMETHODCALLTYPE OnHeadersAvailable(
            /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
            /* [in] */ DWORD dwStatus,
            /* [string][in] */ __RPC__in_string const WCHAR *pwszStatus) override;

        HRESULT STDMETHODCALLTYPE OnDataAvailable(
            /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
            /* [in] */ __RPC__in_opt ISequentialStream *pResponseStream) override;

        HRESULT STDMETHODCALLTYPE OnResponseReceived(
            /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
            /* [in] */ __RPC__in_opt ISequentialStream *pResponseStream) override;

        HRESULT STDMETHODCALLTYPE OnError(
            /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
            /* [in] */ HRESULT hrError) override;

        void clear();

    private:
        LONG _refCount;
        int _httpStatus;

        std::mutex _callbacksMutex;
        std::function<void(const std::string&, int)> _onSuccess;
        std::function<void(int)> _onError;
    };
};

#endif /* _XMLHTTPREQUESTCALLBACK_H_ */
