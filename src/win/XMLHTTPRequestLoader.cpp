#include "braincloud/internal/URLRequestMethod.h"
#include "braincloud/internal/win/XMLHTTPRequestCallback.h"
#include "braincloud/internal/win/XMLHTTPRequestLoader.h"

#include "braincloud/http_codes.h"

#include <condition_variable>
#include <chrono>
#include <codecvt>
#include <mutex>
#include <thread>
#include <future>
#include <iostream>

static std::string utf16ToUtf8(const std::wstring& utf16)
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> stringConverter;
    return stringConverter.to_bytes(utf16);
}

static std::wstring utf8ToUtf16(const std::string& utf8)
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> stringConverter;
    return stringConverter.from_bytes(utf8);
}

namespace BrainCloud
{
    class DataStream final : public ISequentialStream, public IDispatch
    {
    public:
        DataStream(const std::string& data)
            : _refCount(1)
            , _data((const uint8_t*)data.data())
            , _size((ULONG)data.size())
            , _read(0)
        {
        }

        HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID riid,
            _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObj) override
        {
            if (!ppvObj)
            {
                return E_INVALIDARG;
            }
            *ppvObj = NULL;
            if (riid == IID_IUnknown || riid == IID_ISequentialStream || riid == IID_IDispatch)
            {
                // Increment the reference count and return the pointer.
                *ppvObj = (LPVOID)this;
                AddRef();
                return NOERROR;
            }
            return E_NOINTERFACE;
        }

        ULONG STDMETHODCALLTYPE AddRef(void) override
        {
            InterlockedIncrement(&_refCount);
            return _refCount;
        }

        ULONG STDMETHODCALLTYPE Release(void) override
        {
            // Decrement the object's internal counter.
            ULONG ulRefCount = InterlockedDecrement(&_refCount);
            if (0 == _refCount)
            {
                delete this;
            }
            return ulRefCount;
        }

        HRESULT STDMETHODCALLTYPE GetTypeInfoCount(
            /* [out] */ __RPC__out UINT *pctinfo) override
        {
            if (pctinfo)
            {
                *pctinfo = 0;
            }
            return E_NOTIMPL;
        }

        HRESULT STDMETHODCALLTYPE GetTypeInfo(
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo) override
        {
            if (ppTInfo)
            {
                *ppTInfo = 0;
            }
            return E_NOTIMPL;
        }

        HRESULT STDMETHODCALLTYPE GetIDsOfNames(
            /* [in] */ __RPC__in REFIID riid,
            /* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
            /* [range][in] */ __RPC__in_range(0, 16384) UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId) override
        {
            return DISP_E_UNKNOWNNAME;
        }

        HRESULT STDMETHODCALLTYPE Invoke(
            /* [annotation][in] */
            _In_  DISPID dispIdMember,
            /* [annotation][in] */
            _In_  REFIID riid,
            /* [annotation][in] */
            _In_  LCID lcid,
            /* [annotation][in] */
            _In_  WORD wFlags,
            /* [annotation][out][in] */
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */
            _Out_opt_  UINT *puArgErr) override
        {
            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE Read(
            _Out_writes_bytes_to_(cb, *pcbRead)  void *pv,
            _In_  ULONG cb,
            _Out_opt_  ULONG *pcbRead) override
        {
            if (pv == nullptr)
            {
                return E_INVALIDARG;
            }

            auto toRead = std::min<ULONG>(_size - _read, cb);
            if (toRead)
            {
                memcpy(pv, _data, toRead);
                _data += toRead;
            }
            *pcbRead = toRead;

            _mutex.lock();
            _read += toRead;
            _mutex.unlock();

            if (toRead < cb)
            {
                return S_FALSE;
            }

            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE Write(
            _In_reads_bytes_(cb)  const void *pv,
            _In_  ULONG cb,
            _Out_opt_  ULONG *pcbWritten) override
        {
            return S_OK;
        }

        ULONG getByteRead()
        {
            ULONG ret = 0;
            _mutex.lock();
            ret = _read;
            _mutex.unlock();
            return ret;
        }

    private:
        std::mutex _mutex;
        ULONG _refCount;
        const uint8_t* _data;
        ULONG _size;
        ULONG _read;
    };

    URLLoader* URLLoader::create()
    {
        return new XMLHTTPRequestLoader();
    }

    long XMLHTTPRequestLoader::_timeoutInterval = 0;

    XMLHTTPRequestLoader::XMLHTTPRequestLoader()
        : _pRequest(nullptr)
    {
    }

    XMLHTTPRequestLoader::~XMLHTTPRequestLoader()
    {
        close();
    }

    void XMLHTTPRequestLoader::close()
    {
        _requestMutex.lock();
        if (_pRequest)
        {
            _pRequest->Abort();
            _pRequest = NULL;
        }
        _requestMutex.unlock();
    }

    /**
    * This static method is the target of the thread creation.
    * Load up the proper reference to the object, and complete loading the page.
    *
    * @param urlLoader - pointer to the object which is loading the web page
    */
    void* XMLHTTPRequestLoader::loadThread(void *urlLoader)
    {
        // This is the starting point of a new thread.
        // A pointer to the object should have been passed as urlLoader.
        // Verify the pointer.
        if (urlLoader != NULL)
        {
            XMLHTTPRequestLoader *pLoader = reinterpret_cast<XMLHTTPRequestLoader *>(urlLoader);
            loadThreadXMLHTTPRequest(pLoader);
        }

        return NULL;
    }

    static void setXMLHTTPRequestHeaders(XMLHTTPRequestLoader* pLoader, IXMLHTTPRequest2* request)
    {
        // Set the headers
        std::vector<URLRequestHeader> h = pLoader->getRequest().getHeaders();
        for (std::string::size_type i = 0; i < h.size(); i++)
        {
            auto headerName = utf8ToUtf16(h[i].getName());
            auto headerValue = utf8ToUtf16(h[i].getValue());

            request->SetRequestHeader(headerName.c_str(), headerValue.c_str());
        }

        // Content Type (special header)
        request->SetRequestHeader(
            L"Content-type",
            utf8ToUtf16(pLoader->getRequest().getContentType()).c_str());

        // User Agent (special header)
        if (pLoader->getRequest().getUserAgent().length() > 0)
        {
            request->SetRequestHeader(
                L"User-Agent",
                utf8ToUtf16(pLoader->getRequest().getUserAgent()).c_str());
        }
    }

    void XMLHTTPRequestLoader::loadThreadXMLHTTPRequest(XMLHTTPRequestLoader* pLoader)
    {
        HRESULT hr;

        auto urlRequest = pLoader->getRequest();
        auto url = urlRequest.getUrl();
        const auto& data = urlRequest.getData();
        const auto& method = urlRequest.getMethod();
        bool hasTimeout = _timeoutInterval > 0;

        bool isCompleted = false;
        std::string result;
        int httpStatus = HTTP_CLIENT_NETWORK_ERROR;
        std::mutex mutex;
        std::condition_variable cv;

        XMLHTTPRequestCallback* pCallback = new XMLHTTPRequestCallback(
            [&](const std::string& in_result, int status) // Success
        {
            std::unique_lock<std::mutex> lock(mutex);
            isCompleted = true;
            result = in_result;
            httpStatus = status;
            cv.notify_all();
        },
            [&](int status) // Error
        {
            std::unique_lock<std::mutex> lock(mutex);
            isCompleted = true;
            httpStatus = status;
            cv.notify_all();
        });

        DataStream* pStream = new DataStream(data);
        IXMLHTTPRequest2* pRequest;

        // Create the request - We only support POST
        if (method == URLRequestMethod::POST)
        {
            // Create iunstances
            CoInitializeEx(NULL, COINIT_MULTITHREADED);
            CoCreateInstance(CLSID_FreeThreadedXMLHTTP60,
                             NULL,
                             CLSCTX_INPROC_SERVER,
                             IID_PPV_ARGS(&pRequest));

            pLoader->_requestMutex.lock();
            pLoader->_pRequest = pRequest;
            pLoader->_requestMutex.unlock();

            // Open the URL
            auto urlw = utf8ToUtf16(url);
            hr = pRequest->Open(L"POST",
                                urlw.c_str(),
                                pCallback,
                                NULL, NULL, NULL, NULL);

            // Set Headers
            setXMLHTTPRequestHeaders(pLoader, pRequest);

            // Set post data
            pRequest->SetRequestHeader(
                L"Content-length",
                std::to_wstring(data.size()).c_str());

            // Send
            hr = pRequest->Send(pStream, data.size());
            if (hr != S_OK)
            {
                pLoader->_urlResponse.setStatusCode(HTTP_CLIENT_NETWORK_ERROR);
                pLoader->_urlResponse.setReasonPhrase("Failed to send request");
                pLoader->_threadRunning = false;
                pLoader->_requestMutex.lock();
                pLoader->_pRequest->Release();
                pLoader->_pRequest = NULL;
                pLoader->_requestMutex.unlock();
                pCallback->Release();
                pStream->Release();
                return;
            }
        }
        else
        {
            // Method type not supported.
            pLoader->_urlResponse.setStatusCode(HTTP_CLIENT_NETWORK_ERROR);
            pLoader->_urlResponse.setReasonPhrase("Method type not supported: " + pLoader->getRequest().getMethod());
            pLoader->_threadRunning = false;
            pLoader->_requestMutex.lock();
            pLoader->_pRequest = NULL;
            pLoader->_requestMutex.unlock();
            pCallback->Release();
            pStream->Release();
            return;
        }

        // We wait until the async request is done
        auto startTime = std::chrono::steady_clock::now();
        auto endTime = startTime + std::chrono::milliseconds(_timeoutInterval);
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_until(lock, endTime, [&]()
        {
            return std::chrono::steady_clock::now() >= endTime || isCompleted;
        });

        // Check if we timed out
        if (!isCompleted)
        {
            // Timeout
            printf("#BCC TIMEOUT\n");

            isCompleted = true;
            pLoader->_urlResponse.setStatusCode(HTTP_CLIENT_NETWORK_ERROR);
            pLoader->_threadRunning = false;

            // Abort the request in a thread
            pCallback->clear();
            pLoader->_requestMutex.lock();
            std::thread requestStopThread([=]
            {
                if (pRequest)
                {
                    pRequest->Abort();
                    pRequest->Release();
                    pCallback->Release();
                    pStream->Release();
                }
            });
            requestStopThread.detach();

            pLoader->_pRequest = NULL;
            pLoader->_requestMutex.unlock();
            return;
        }

        // Set results
        pLoader->_urlResponse.setStatusCode((unsigned short)httpStatus);
        pLoader->_urlResponse.addData(result);

        // We done
        pLoader->_requestMutex.lock();
        pLoader->_pRequest = NULL;
        pLoader->_requestMutex.unlock();
        pLoader->_threadRunning = false;

        // Clean up
        pRequest->Release();
        pCallback->Release();
        pStream->Release();
    }

    void XMLHTTPRequestLoader::load(URLRequest const & urlRequest)
    {
        // Assume the specified URL in the request is valid.
        setRequest(urlRequest);

        // Start the load thread
        _threadRunning = true;
        auto thread = std::thread(loadThread, this);
        thread.detach();
    }

    bool XMLHTTPRequestLoader::isDone()
    {
        return !_threadRunning;
    }

    void XMLHTTPRequestLoader::onError(int httpCode)
    {
    }

    void XMLHTTPRequestLoader::onSuccess(const std::string& response, int httpCode)
    {
    }
}
