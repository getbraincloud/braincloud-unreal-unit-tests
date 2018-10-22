#include "braincloud/internal/win/XMLHTTPRequestCallback.h"
#include "braincloud/internal/win/XMLHTTPRequestLoader.h"

#include <iostream>
#include <string>

namespace BrainCloud
{
    XMLHTTPRequestCallback::XMLHTTPRequestCallback(
        const std::function<void(const std::string&, int)>& onSuccess,
        const std::function<void(int)>& onError)
        : _refCount(1)
        , _httpStatus(900)
        , _onSuccess(onSuccess)
        , _onError(onError)
    {
    }

    XMLHTTPRequestCallback::~XMLHTTPRequestCallback()
    {
    }

    HRESULT STDMETHODCALLTYPE XMLHTTPRequestCallback::QueryInterface(
        REFIID riid,
        _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObj)
    {
        if (!ppvObj)
        {
            return E_INVALIDARG;
        }
        *ppvObj = NULL;
        if (riid == IID_IUnknown || riid == IID_IXMLHTTPRequest2Callback)
        {
            // Increment the reference count and return the pointer.
            *ppvObj = (LPVOID)this;
            AddRef();
            return NOERROR;
        }
        return E_NOINTERFACE;
    }

    ULONG STDMETHODCALLTYPE XMLHTTPRequestCallback::AddRef(void)
    {
        InterlockedIncrement(&_refCount);
        return _refCount;
    }

    ULONG STDMETHODCALLTYPE XMLHTTPRequestCallback::Release(void)
    {
        // Decrement the object's internal counter.
        ULONG ulRefCount = InterlockedDecrement(&_refCount);
        if (0 == _refCount)
        {
            delete this;
        }
        return ulRefCount;
    }

    HRESULT STDMETHODCALLTYPE XMLHTTPRequestCallback::OnRedirect(
        /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
        /* [string][in] */ __RPC__in_string const WCHAR *pwszRedirectUrl)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE XMLHTTPRequestCallback::OnHeadersAvailable(
        /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
        /* [in] */ DWORD dwStatus,
        /* [string][in] */ __RPC__in_string const WCHAR *pwszStatus)
    {
        _httpStatus = (int)dwStatus;

        if (!pXHR)
        {
            return E_INVALIDARG;
        }

        // We don't care about headers response in the file uploader
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE XMLHTTPRequestCallback::OnDataAvailable(
        /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
        /* [in] */ __RPC__in_opt ISequentialStream *pResponseStream)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE XMLHTTPRequestCallback::OnResponseReceived(
        /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
        /* [in] */ __RPC__in_opt ISequentialStream *pResponseStream)
    {
        const int READ_BUFFER_MAX = 16 * 1024; // 16k
        char buffer[READ_BUFFER_MAX];
        ULONG byteRead;
        std::string resultMessage;
        HRESULT hr;

        while (true)
        {
            hr = pResponseStream->Read(buffer, (ULONG)READ_BUFFER_MAX, &byteRead);
            if (FAILED(hr)) break;
            if (byteRead == 0) break;
            resultMessage.append(buffer, byteRead);
        }

        if (_onSuccess)
        {
            _onSuccess(resultMessage, _httpStatus);
        }
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE XMLHTTPRequestCallback::OnError(
        /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
        /* [in] */ HRESULT hrError)
    {
        if (_onError)
        {
            _onError(_httpStatus);
        }
        return S_OK;
    }
};

