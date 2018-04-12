//
//  nsURLLoader.mm
//  BrainCloudCpp
//
//  Created by Mario Couture on 2016-04-27.
//  Copyright © 2016 BitHeads Inc. All rights reserved.
//


#include <cctype>

#ifdef HG_PLATFORM_BB
#include <stdio.h>
#include <ctype.h>
#endif

#include "braincloud/internal/apple/nsURLLoader.h"
#include "braincloud/internal/URLRequestMethod.h"
#include "braincloud/http_codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#import <Foundation/Foundation.h>

@interface URLSessionDelegate () {
    BrainCloud::nsURLLoader* _urlLoader;
    NSURLSession *_session;
}
@end
@implementation URLSessionDelegate
- (instancetype)initWithLoader:(BrainCloud::nsURLLoader*) loader
{
    self = [super init];
    if (self) {
        self->_urlLoader = loader;
    }
    return self;
}

-(void) start
{
    //Creates a session with the specified session configuration, delegate, and operation queue. a nil queue autmatically create one.
    _session = [NSURLSession sessionWithConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]
                                             delegate:self
                                        delegateQueue:nil];
    
    NSURL* requestUrl = [NSURL URLWithString:[NSString stringWithCString:_urlLoader->getRequest().getUrl().c_str()
                                                                encoding:NSUTF8StringEncoding]];
    
    NSMutableURLRequest* request = [NSMutableURLRequest requestWithURL:requestUrl];
    
    if ( request != NULL )
    {
        _urlLoader->setThreadRunning(true);
        // Set the headers.
        std::vector<URLRequestHeader> h = _urlLoader->getRequest().getHeaders();
        for ( std::string::size_type i = 0; i < h.size(); i ++ )
        {
            NSString *value = [NSString stringWithCString:h[i].getValue().c_str() encoding:NSUTF8StringEncoding];
            NSString *headerLine = [NSString stringWithCString:h[i].getName().c_str() encoding:NSUTF8StringEncoding];
            
            [request addValue:value forHTTPHeaderField:headerLine];
        }  // end for
        
        
        // Content Type (special header)
        NSString *contentType = [NSString stringWithCString:_urlLoader->getRequest().getContentType().c_str() encoding:NSUTF8StringEncoding];
        [request addValue:contentType forHTTPHeaderField:@"Content-Type"];
        
        // User Agent (special header)
        if ( _urlLoader->getRequest().getUserAgent().length() > 0 )
        {
            NSString *userAgent = [NSString stringWithCString:_urlLoader->getRequest().getUserAgent().c_str() encoding:NSUTF8StringEncoding];
            [request addValue:userAgent forHTTPHeaderField:@"User-Agent"];
        }
        
        // Only set timeout if it's not 0.
        if (_urlLoader->getTimeout() > 0)
        {
            [request setTimeoutInterval:_urlLoader->getTimeout()/1000];
        }
        
        // Determine the type of request being made.
        if ( _urlLoader->getRequest().getMethod() == URLRequestMethod::GET )
        {
            std::string url = _urlLoader->getRequest().getUrl();
            std::string data = _urlLoader->getRequest().getData();
            
            if ( data.length() > 0 )
            {
                // Append the request data to the end of the URL.
                url.append("?");
                url.append(data);
            }
            
            // Replace the URL with a one with all params added
            NSString* urlWithParams = [NSString stringWithCString:url.c_str() encoding:NSUTF8StringEncoding];
            request.URL = [NSURL URLWithString:urlWithParams];
            
            NSURLSessionDataTask* task = [_session dataTaskWithRequest:request];
            [task resume];
        }
        else if ( _urlLoader->getRequest().getMethod() == URLRequestMethod::POST )
        {
            // Create all of the form data.
            [request setHTTPMethod:@"POST"];
            
            [request setHTTPBody:[NSData dataWithBytes:_urlLoader->getRequest().getData().c_str()
                                                length:_urlLoader->getRequest().getData().length()]];
            
            //            rc = curl_easy_perform(curl);
            NSURLSessionDataTask* task = [_session dataTaskWithRequest:request];
            [task resume];
        }
        else if ( _urlLoader->getRequest().getMethod() == URLRequestMethod::PUT )
        {
            // Create all of the form data.
            
            [request setHTTPMethod:@"PUT"];
            
            [request setHTTPBody:[NSData dataWithBytes:_urlLoader->getRequest().getData().c_str()
                                                length:_urlLoader->getRequest().getData().length()]];
            
            NSURLSessionDataTask* task = [_session dataTaskWithRequest:request];
            [task resume];
        }
        else
        {
            // Method type not supported.
            _urlLoader->setThreadRunning(false);
        }
    }
}

-(void) stop
{
   [_session invalidateAndCancel];
    self->_urlLoader = nil;
}

 //   Called after receiving an initial response, to let you examine the status code and headers, and optionally convert the data task into a download task.
-(void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask didReceiveResponse:(NSURLResponse *)response completionHandler:(void (^)(NSURLSessionResponseDisposition))completionHandler
{
    if (_urlLoader == nil) {
        completionHandler(NSURLSessionResponseCancel);
        return;
    };
    
    if ([response isKindOfClass:[NSHTTPURLResponse class]]) {
        NSHTTPURLResponse * httpResponse = (NSHTTPURLResponse * ) response;
        for (NSString* key in httpResponse.allHeaderFields.allKeys) {
            std::string h([key cStringUsingEncoding:NSUTF8StringEncoding]);
            URLRequestHeader header(h);
            std::string v([httpResponse.allHeaderFields[key] cStringUsingEncoding:NSUTF8StringEncoding]);
            header.setValue(v);
            _urlLoader->getResponse().addHeader(header);
            
        }
    }
    completionHandler(NSURLSessionResponseAllow);
}

// Tells the delegate that the data task has received some of the expected data. may get called multiple times.
-(void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask didReceiveData:(NSData *)data
{
    if (_urlLoader == nil) {
        return;
    };

    if (_urlLoader != NULL) {
        // Append the data to the buffer
        [data enumerateByteRangesUsingBlock:^(const void * _Nonnull bytes, NSRange byteRange, BOOL * _Nonnull stop) {
            _urlLoader->getResponse().addData(std::string((char *)bytes, byteRange.length));
        }];
    }
}

//Asks the delegate whether the data (or upload) task should store the response in the cache.
-(void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask willCacheResponse:(NSCachedURLResponse *)proposedResponse completionHandler:(void (^)(NSCachedURLResponse * _Nullable))completionHandler
{
    // Pass nil to refuse caching.
    completionHandler(nil);
}

// Tells the delegate that the task finished transferring data.
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didCompleteWithError:(NSError *)error
{
    if (_urlLoader == nil) {
        return;
    }
    
    if (error) {
        // Here additional error could be trapped, but to keep parity with cURLLoader only these where added.
        if (error.code == NSURLErrorTimedOut) {
            _urlLoader->getResponse().setStatusCode(HTTP_CLIENT_NETWORK_ERROR/*408*/);
            _urlLoader->getResponse().setReasonPhrase("Operation timed out");
        } else if (error.code == NSURLErrorCancelled) {
            // aborted by caller.
            _urlLoader->getResponse().setStatusCode(HTTP_CLIENT_NETWORK_ERROR);
            _urlLoader->getResponse().setReasonPhrase(std::string([error.localizedDescription cStringUsingEncoding:NSUTF8StringEncoding]));
        } else {
            _urlLoader->getResponse().setStatusCode(HTTP_CLIENT_NETWORK_ERROR);
            _urlLoader->getResponse().setReasonPhrase(std::string([error.localizedDescription cStringUsingEncoding:NSUTF8StringEncoding]));
        }
        
    } else if ([task.response isKindOfClass:[NSHTTPURLResponse class]]) {
        NSHTTPURLResponse * httpResponse = (NSHTTPURLResponse * ) task.response;
        
        if (task.error == nil)
        {
            // All worked fine return the status received.
            _urlLoader->getResponse().setStatusCode(static_cast<unsigned short>(httpResponse.statusCode));
        }
        else
        {
            _urlLoader->getResponse().setStatusCode(HTTP_CLIENT_NETWORK_ERROR);
            _urlLoader->getResponse().setReasonPhrase(std::string([task.error.localizedDescription cStringUsingEncoding:NSUTF8StringEncoding]));
        }
        
    }
    
    _urlLoader->setThreadRunning(false);
}

#ifdef DISABLE_SSL_CHECK
- (void)URLSession:(NSURLSession *)session didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition, NSURLCredential *))completionHandler{
    if([challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodServerTrust]){
        NSURLCredential *credential = [NSURLCredential credentialForTrust:challenge.protectionSpace.serverTrust];
        completionHandler(NSURLSessionAuthChallengeUseCredential,credential);
    }
}
#endif
@end


namespace BrainCloud
{
	URLLoader* URLLoader::create()
	{
		return new nsURLLoader();
	}

    bool nsURLLoader::_initialized = false;
    long nsURLLoader::_timeoutInterval = 0;

	/**
	 * Constructor
	 *   - NOTE:  If a URLRequest is given, the object will try to contact the
	 *            server immediately by calling the load() method.
	 */

	nsURLLoader::nsURLLoader()
	: _threadRunning(false)
	{
	}

	nsURLLoader::~nsURLLoader( )
	{
		// Regardless of _threadRunning stop any URLSession and release it.
		[_sessionDelegate stop];
		_sessionDelegate = nil;
	}

	/**
	 * Close a currently running load operation, if in progress.
	 */
	void nsURLLoader::close()
	{
		// We can stop loading the page by killing its thread.
		if (_threadRunning)
		{
			[_sessionDelegate stop];
			_sessionDelegate = nil;
		}
	}


	/**
	 * Issue an HTTP Request to the remote server, and load the response.
	 *
	 * @param urlRequest - HTTP Request
	 */
	void nsURLLoader::load( URLRequest const & urlRequest )
	{
		// Assume the specified URL in the request is valid.
		setRequest(urlRequest);
    
		_sessionDelegate = [[URLSessionDelegate alloc] initWithLoader:this];
		if (_sessionDelegate) {
			[_sessionDelegate start];
			_initialized = true;
			_threadRunning = true;
		} else {
			URLResponse response;
			this->getResponse().setStatusCode(503);
			this->getResponse().setReasonPhrase("URL Session Out of Memory");
		}

	}

	bool nsURLLoader::isDone()
	{
		return !_threadRunning;
	}
}
