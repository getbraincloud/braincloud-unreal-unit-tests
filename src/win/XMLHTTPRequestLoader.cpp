#include "braincloud/internal/URLRequestMethod.h"
#include "braincloud/internal/win/XMLHTTPEventSink.h"
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

namespace BrainCloud
{
    URLLoader* URLLoader::create()
    {
        return new XMLHTTPRequestLoader();
    }

    long XMLHTTPRequestLoader::_timeoutInterval = 0;

    XMLHTTPRequestLoader::XMLHTTPRequestLoader()
    {
    }

    XMLHTTPRequestLoader::~XMLHTTPRequestLoader()
    {
        close();
    }

    void XMLHTTPRequestLoader::close()
    {
        _requestMutex.lock();
        if (_request)
        {
            _request->abort();
            _request = NULL;
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

    static void setXMLHTTPRequestHeaders(XMLHTTPRequestLoader* pLoader, CComPtr<IXMLHTTPRequest>& request)
    {
        // Set the headers
        std::vector<URLRequestHeader> h = pLoader->getRequest().getHeaders();
        for (std::string::size_type i = 0; i < h.size(); i++)
        {
            const std::string& headerName = h[i].getName();
            const std::string& headerValue = h[i].getValue();

            request->setRequestHeader(_bstr_t(headerName.c_str()), _bstr_t(headerValue.c_str()));
        }

        // Content Type (special header)
        request->setRequestHeader(_bstr_t("Content-type"), _bstr_t(pLoader->getRequest().getContentType().c_str()));

        // User Agent (special header)
        if (pLoader->getRequest().getUserAgent().length() > 0)
        {
            request->setRequestHeader(_bstr_t("User-Agent"), _bstr_t(pLoader->getRequest().getUserAgent().c_str()));
        }
    }

    void XMLHTTPRequestLoader::loadThreadXMLHTTPRequest(XMLHTTPRequestLoader* pLoader)
    {
        HRESULT hr;
        CComPtr<IXMLHTTPRequest> request;

        CoInitializeEx(NULL, COINIT_MULTITHREADED);

        auto urlRequest = pLoader->getRequest();
        auto url = urlRequest.getUrl();
        const auto& data = urlRequest.getData();
        const auto& method = urlRequest.getMethod();
        bool hasTimeout = _timeoutInterval > 0;

        bool isCompleted = false;
        std::mutex mutex;
        std::condition_variable cv;
        IDispatch *pSink;

        // Create the request
        if (method == URLRequestMethod::GET)
        {
            if (data.length() > 0)
            {
                // Append the request data to the end of the URL.
                url.append("?");
                url.append(data);
            }

            hr = request.CoCreateInstance(CLSID_XMLHTTP60);

            pLoader->_requestMutex.lock();
            pLoader->_request = request;
            pLoader->_requestMutex.unlock();

            hr = request->open(_bstr_t("GET"),
                               _bstr_t(url.c_str()), 
                               _variant_t(VARIANT_TRUE),
                               _variant_t(),
                               _variant_t());

            setXMLHTTPRequestHeaders(pLoader, request);

            // Hook up the onreadystatechange event handler
            pSink = new XMLHTTPEventSink(request, [&]
            {
                // onCompleted
                std::unique_lock<std::mutex> lock(mutex);
                isCompleted = true;
                cv.notify_all();
            });
            request->put_onreadystatechange(pSink);

            // Send
            hr = request->send(_variant_t());
            if (hr != S_OK)
            {
                pLoader->_urlResponse.setStatusCode(HTTP_CLIENT_NETWORK_ERROR);
                pLoader->_urlResponse.setReasonPhrase("Failed to send request");
                pLoader->_threadRunning = false;
                pLoader->_requestMutex.lock();
                pLoader->_request = NULL;
                pLoader->_requestMutex.unlock();
                return;
            }
        }
        else if (method == URLRequestMethod::POST)
        {
            hr = request.CoCreateInstance(CLSID_XMLHTTP60);

            pLoader->_requestMutex.lock();
            pLoader->_request = request;
            pLoader->_requestMutex.unlock();

            hr = request->open(_bstr_t("POST"),
                               _bstr_t(url.c_str()), 
                               _variant_t(VARIANT_TRUE),
                               _variant_t(),
                               _variant_t());

            setXMLHTTPRequestHeaders(pLoader, request);

            // Set post data
            request->setRequestHeader(_bstr_t("Content-length"), _bstr_t(std::to_string(data.size()).c_str()));

            _variant_t var;
            var.vt = VT_ARRAY | VT_UI1;

            SAFEARRAYBOUND rgsabound[1];
            rgsabound[0].cElements = (ULONG)data.size();
            rgsabound[0].lLbound = 0;

            var.parray = SafeArrayCreate(VT_UI1, 1, rgsabound); // This is cleaned up internally

            void* pArrayData = NULL;
            SafeArrayAccessData(var.parray, &pArrayData);
            memcpy(pArrayData, data.data(), data.size());
            SafeArrayUnaccessData(var.parray);

            // Hook up the onreadystatechange event handler
            pSink = new XMLHTTPEventSink(request, [&]
            {
                // onCompleted
                std::unique_lock<std::mutex> lock(mutex);
                isCompleted = true;
                cv.notify_all();
            });
            request->put_onreadystatechange(pSink);

            // Send
            hr = request->send(var);
            if (hr != S_OK)
            {
                pLoader->_urlResponse.setStatusCode(HTTP_CLIENT_NETWORK_ERROR);
                pLoader->_urlResponse.setReasonPhrase("Failed to send request");
                pLoader->_threadRunning = false;
                pLoader->_requestMutex.lock();
                pLoader->_request = NULL;
                pLoader->_requestMutex.unlock();
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
            pLoader->_request = NULL;
            pLoader->_requestMutex.unlock();
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

        pSink->Release();

        // Check if we timed out
        if (!isCompleted)
        {
            // Timeout
            printf("#BCC TIMEOUT\n");

            isCompleted = true;
            pLoader->_urlResponse.setStatusCode(HTTP_CLIENT_NETWORK_ERROR);
            pLoader->_threadRunning = false;

            // Abort the request in a thread
            pLoader->_requestMutex.lock();
            auto requestStopThread = std::thread([](CComPtr<IXMLHTTPRequest> request)
            {
				if (request)
				{
                	request->abort();
				}
            }, pLoader->_request);
            requestStopThread.detach();

            pLoader->_request = NULL;
            pLoader->_requestMutex.unlock();
            return;
        }

        // get status
        long status;
        hr = request->get_status(&status);
        if (hr != S_OK)
        {
            pLoader->_urlResponse.setStatusCode(HTTP_CLIENT_NETWORK_ERROR);
            pLoader->_urlResponse.setReasonPhrase("Failed to get HTTP status");
            pLoader->_threadRunning = false;
            pLoader->_requestMutex.lock();
            pLoader->_request = NULL;
            pLoader->_requestMutex.unlock();
            return;
        }
        pLoader->_urlResponse.setStatusCode((unsigned short)status);

        // Get response body
        if (status == 200)
        {
            VARIANT body;
            request->get_responseBody(&body);
            auto pData = (const uint8_t*)body.parray->pvData;
            auto size = (size_t)(body.parray->rgsabound[0].cElements);
            pLoader->_urlResponse.addData(std::string((char*)pData, size));
        }
        else
        {
            BSTR bstrResponse = NULL;
            request->get_responseText(&bstrResponse);
            std::wstring wret = L"";
            if (bstrResponse)
            {
                wret = bstrResponse;
                SysFreeString(bstrResponse);
            }
            pLoader->_urlResponse.setReasonPhrase(utf16ToUtf8(wret));
        }

        // We done
        pLoader->_requestMutex.lock();
        pLoader->_request = NULL;
        pLoader->_requestMutex.unlock();
        pLoader->_threadRunning = false;
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
}
