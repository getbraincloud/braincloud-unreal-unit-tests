#include "braincloud/internal/win/XMLHTTPRequestCallback.h"
#include "braincloud/internal/win/XMLHTTPRequestPinger.h"

#include <msxml6.h>

#include <condition_variable>
#include <chrono>
#include <codecvt>
#include <mutex>
#include <string>

static std::wstring utf8ToUtf16(const std::string& utf8)
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> stringConverter;
    return stringConverter.from_bytes(utf8);
}

namespace BrainCloud
{
    IPinger* IPinger::create(BrainCloudClient* pClient)
    {
        return new XMLHTTPRequestPinger();
    }

    XMLHTTPRequestPinger::XMLHTTPRequestPinger()
    {
    }

    int XMLHTTPRequestPinger::ping(const std::string& url)
    {
        int pingResult = 999; // 999 is worse ping or didn't reach
        bool success = false;
        bool isCompleted = false;
        std::mutex mutex;
        std::condition_variable condition;

        std::chrono::time_point<std::chrono::high_resolution_clock> doneTime;
        XMLHTTPRequestCallback* pCallback = new XMLHTTPRequestCallback(
            [&](const std::string& in_result, int status) // Success
        {
            std::unique_lock<std::mutex> lock(mutex);
            success = true;
            doneTime = std::chrono::high_resolution_clock::now();
            isCompleted = true;
            condition.notify_all();
        },
            [&](int status) // Error
        {
            std::unique_lock<std::mutex> lock(mutex);
            isCompleted = true;
            condition.notify_all();
        });

        // Converet URL
        auto urlw = utf8ToUtf16(url);

        // Create instance
        IXMLHTTPRequest2* pRequest;
        CoInitializeEx(NULL, COINIT_MULTITHREADED);
        CoCreateInstance(CLSID_FreeThreadedXMLHTTP60, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pRequest));

        // Open the URL
        if (pRequest->Open(L"PING", urlw.c_str(), pCallback, NULL, NULL, NULL, NULL) == S_OK)
        {
            auto startTime = std::chrono::high_resolution_clock::now();
            if (pRequest->Send(NULL, 0) == S_OK)
            {
                // timeout for 2 seconds
                {
                    auto startTimeout = std::chrono::high_resolution_clock::now();
                    auto endTimeout = startTimeout + std::chrono::seconds(2);
                    std::unique_lock<std::mutex> lock(mutex);
                    condition.wait_until(lock, endTimeout, [&]()
                    {
                        return std::chrono::high_resolution_clock::now() >= endTimeout || isCompleted;
                    });
                    if (!isCompleted)
                    {
                        pCallback->clear();
                        pRequest->Abort();
                    }
                }

                if (success)
                {
                    pingResult = (int)(std::chrono::duration_cast<std::chrono::milliseconds>(doneTime - startTime).count());
                    if (pingResult > 999)
                    {
                        pingResult = 999;
                    }
                }
            }
        }

        pRequest->Release();
        pCallback->Release();
        return pingResult;
    }
}
