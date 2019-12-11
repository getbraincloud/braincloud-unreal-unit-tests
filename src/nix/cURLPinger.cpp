#include "braincloud/internal/nix/cURLPinger.h"

#include "curl/curl.h"

#include <chrono>

namespace BrainCloud
{
    IPinger* IPinger::create(BrainCloudClient* pClient)
    {
        return new cURLPinger();
    }

    cURLPinger::cURLPinger() {}

    int cURLPinger::ping(const std::string& url)
    {
        CURL *curl;
        CURLcode res = CURLE_OK;
        curl = curl_easy_init();
        if (!curl)
        {
            return 999; 
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 2);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);

        auto startTime = std::chrono::high_resolution_clock::now();
        res = curl_easy_perform(curl);
        auto doneTime = std::chrono::high_resolution_clock::now();

        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
        {
            return 999;
        }

        int pingResult = (int)(std::chrono::duration_cast<std::chrono::milliseconds>(doneTime - startTime).count());
        if (pingResult > 999)
        {
            pingResult = 999;
        }

        return pingResult;
    }
}
