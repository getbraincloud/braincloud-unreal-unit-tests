#include "braincloud/internal/apple/nsPinger.h"

#import <Foundation/Foundation.h>

#include <chrono>
#include <condition_variable>
#include <mutex>

namespace BrainCloud
{
    IPinger* IPinger::create(BrainCloudClient* pClient)
    {
        return new nsPinger();
    }

    nsPinger::nsPinger() {}

    int nsPinger::ping(const std::string& url)
    {
        std::mutex mutex;
        std::condition_variable condition;

        // Create the request
        NSURLSession* pSession = [NSURLSession sessionWithConfiguration:[NSURLSessionConfiguration ephemeralSessionConfiguration]];
        NSURL* requestUrl = [NSURL URLWithString:[NSString stringWithCString:url.c_str() encoding:NSUTF8StringEncoding]];
        NSMutableURLRequest* pRequest = [NSMutableURLRequest requestWithURL:requestUrl];
        if (pRequest == NULL)
        {
            return 999;
        }

        // Set timeout to 2 seconds
        [pRequest setTimeoutInterval:2.0];

        // Set as ping
        [pRequest setHTTPMethod:@"PING"];

        // Perform the request
        std::unique_lock<std::mutex> lock(mutex);
        bool success = false;
        NSURLSessionDataTask* task = [pSession dataTaskWithRequest:pRequest completionHandler:[&mutex, &condition, &success](NSData *data, NSURLResponse *response, NSError *error)
        {
            std::unique_lock<std::mutex> lock(mutex);
            success = error == nil;
            condition.notify_one();
        }];

        // Wait for completion
        auto startTime = std::chrono::high_resolution_clock::now();
        [task resume];
        condition.wait(lock);
        auto doneTime = std::chrono::high_resolution_clock::now();

        // Calculate result ping and return
        int pingResult = (int)(std::chrono::duration_cast<std::chrono::milliseconds>(doneTime - startTime).count());
        if (pingResult > 999 || !success)
        {
            pingResult = 999;
        }
        return pingResult;
    }
}
