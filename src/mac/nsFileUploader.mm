//
//  nsFileUploader.m
//  BrainCloudCpp
//
//  Created by Preston Jennings on 2016-06-03.
//  Copyright © 2016 BitHeads Inc. All rights reserved.
//
#ifdef __APPLE__
//#if (TARGET_OS_WATCH != 1) // necessary as cocoapods doesn't allow per platform source files

#import <Foundation/Foundation.h>
#include <TargetConditionals.h>
#include "braincloud/internal/mac/nsFileUploader.h"
/*
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
*/
/*
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "braincloud/internal/IBrainCloudComms.h"

@interface ObjcFileUploader() {
    
    //eFileUploaderStatus     _status;
    int             _uploadLowTransferRateTimeoutSecs;
    int             _uploadLowTransferRateThresholdBytesPerSec;
    
    NSString *      _sessionId;
    NSString *      _fileUploadId;
    long            _fileLength;
    NSString *      _fileName;
 //   NSString *      _uploadUrl;
    
    int             _httpStatus;
    int             _errorReasonCode;
    NSString *      _httpInternalResponse;
    NSString *      _httpJsonResponse;
    
    bool            _shouldCancelUpload;
    long            _uploadTotalBytes;
    long            _uploadTransferredBytes;
}
@end


@implementation ObjcFileUploader

- (void)connection:(NSURLConnection *)connection
didReceiveResponse:(NSURLResponse *)response
{
    
}

- (void)connection:(NSURLConnection *)connection
    didReceiveData:(NSData *)data
{
    
}

- (void)connection:(NSURLConnection *)connection
   didSendBodyData:(NSInteger)bytesWritten
 totalBytesWritten:(NSInteger)totalBytesWritten
totalBytesExpectedToWrite:(NSInteger)totalBytesExpectedToWrite
{
    
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    
    
}


- (NSCachedURLResponse *)connection:(NSURLConnection *)connection
                  willCacheResponse:(NSCachedURLResponse *)cachedResponse
{
    // never cache upload response
    return nil;
}

- (void)uploadFileWithSessionId:(NSString*)sessionId
                   fileUploadId:(NSString*)fileUploadId
                       fileName:(NSString*)fileName
                       fileSize:(NSInteger)fileSize
                      uploadUrl:(NSString*)uploadUrl
{
    _sessionId = sessionId;
    _fileUploadId = fileUploadId;
    _fileName = fileName;
    //_fileSize = fileSize;
//    _uploadUrl = uploadUrl;
    
    // do it
    
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
    [request setURL:[NSURL URLWithString:uploadUrl]];
    [request setHTTPMethod:@"PUT"];
    */
    /*
     add some header info now
     we always need a boundary when we post a file
     also we need to set the content type
     
     You might want to generate a random boundary.. this is just the same
     as my output from wireshark on a valid html post
     */
/*
    NSString *boundary = [NSString stringWithString:@"---------------------------14737809831466499882746641449"];
    NSString *contentType = [NSString stringWithFormat:@"multipart/form-data; boundary=%@",boundary];
    [request addValue:contentType forHTTPHeaderField: @"Content-Type"];
    
    //  now lets create the body of the post

    NSMutableData *body = [NSMutableData data];
    [body appendData:[[NSString stringWithFormat:@"rn--%@rn",boundary] dataUsingEncoding:NSUTF8StringEncoding]];
    [body appendData:[[NSString stringWithString:@"Content-Disposition: form-data; name="userfile"; filename="ipodfile.jpg"rn"] dataUsingEncoding:NSUTF8StringEncoding]];
    [body appendData:[[NSString stringWithString:@"Content-Type: application/octet-streamrnrn"] dataUsingEncoding:NSUTF8StringEncoding]];
    [body appendData:[NSData dataWithData:imageData]];
    [body appendData:[[NSString stringWithFormat:@"rn--%@--rn",boundary] dataUsingEncoding:NSUTF8StringEncoding]];
    // setting the body of the post to the reqeust
    [request setHTTPBody:body];
    
    // now lets make the connection to the web
    NSData *returnData = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];
    NSString *returnString = [[NSString alloc] initWithData:returnData encoding:NSUTF8StringEncoding];
    
    NSLog(returnString);
}

@end


namespace BrainCloud
{
    bool NSFileUploader::_loggingEnabled = false;
    
    NSFileUploader::NSFileUploader()
    {
        _uploader = [[ObjcFileUploader alloc] init];
    }
    
    NSFileUploader::~NSFileUploader()
    {
    }
    */
    /*
    bool NSFileUploader::uploadFile(std::string & in_sessionId,
                                      std::string & in_fileUploadId,
                                      std::string & in_fileName,
                                      int64_t in_fileSize,
                                      std::string & in_uploadUrl)
    {
        _sessionId = in_sessionId;
        _fileUploadId = in_fileUploadId;
        _fileName = in_fileName;
        _uploadUrl = in_uploadUrl;
        _fileLength = static_cast<long>(in_fileSize);
       
        
        _threadRunning = true;
        _status = UPLOAD_STATUS_PENDING;
        
        return true;
    }
    
    void NSFileUploader::setUploadLowTransferRateTimeout(int in_timeoutSecs)
    {
        _uploadLowTransferRateTimeoutSecs = in_timeoutSecs;
    }
    
    void NSFileUploader::setUploadLowTransferRateThreshold(int in_bytesPerSec)
    {
        _uploadLowTransferRateThresholdBytesPerSec = in_bytesPerSec;
    }
    
    void NSFileUploader::enableLogging(bool in_loggingEnabled)
    {
        _loggingEnabled = in_loggingEnabled;
    }
    
    IFileUploader::eFileUploaderStatus NSFileUploader::getStatus()
    {
        return _status;
    }
    
    bool NSFileUploader::isThreadRunning()
    {
        return _threadRunning;
    }
    
    void NSFileUploader::cancelUpload()
    {
        _shouldCancelUpload = true;
    }
    
    int64_t NSFileUploader::getBytesTransferred()
    {
        return _uploadTransferredBytes;
    }
    
    int64_t NSFileUploader::getTotalBytesToTransfer()
    {
        return _fileLength;
    }
    
    double NSFileUploader::getProgress()
    {
        return _uploadTransferredBytes / (double) _uploadTotalBytes;
    }
    
    void NSFileUploader::setStatus(eFileUploaderStatus in_status)
    {
        _status = in_status;
    }
    
    // these are only safe to call when thread running is false
    const std::string & NSFileUploader::getHttpResponse()
    {
        return _httpJsonResponse;
    }
    
    // these are only safe to call when thread running is false
    int NSFileUploader::getHttpStatus()
    {
        return _httpStatus;
    }
    
    // these are only safe to call when thread running is false
    int NSFileUploader::getErrorReasonCode()
    {
        return _errorReasonCode;
    }
   */
    
    /**
     * Use libCurl to upload the file
     *
     * @param loader - pointer to the object which is loading the web page
    void cURLFileUploader::uploadFileFromThread(cURLFileUploader * fileUploader)
    {
        FILE *fp = NULL;
        struct curl_slist *slist = NULL;
        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;
        
        bool useMultipart = true;
        if (!useMultipart)
        {
            fp = fopen(fileUploader->_fileName.c_str(), "rb");
            if (fp == NULL)
            {
                fileUploader->setStatus(UPLOAD_STATUS_COMPLETE_FAILED);
                fileUploader->_threadRunning = false;
                return;
            }
        }
        
        CURL * curl = curl_easy_init();
        if (curl == NULL)
        {
            fileUploader->setStatus(UPLOAD_STATUS_COMPLETE_FAILED);
            fileUploader->_threadRunning = false;
            return;
        }
        
        fileUploader->setStatus(UPLOAD_STATUS_UPLOADING);
        
        CURLcode rc = CURLE_OK;
        char curlError[CURL_ERROR_SIZE];
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, _loggingEnabled ? 1L : 0L);
        //curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, debug_callback);
        
#if defined(CURLOPT_XFERINFODATA)
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, curlXferInfoCallback);
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, fileUploader);
#else
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, curlProgressCallback);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, fileUploader);
#endif
        
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curlError);
        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fileUploader);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
        
        // TODO: preston - this is present in the curl loader as well
        // We should definitely be doing a more valid SSL check!
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, (long)0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, (long)0);
        
        // if set, configure low transfer rate timeout
        if (fileUploader->_uploadLowTransferRateTimeoutSecs > 0)
        {
            curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, fileUploader->_uploadLowTransferRateThresholdBytesPerSec);
            curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, fileUploader->_uploadLowTransferRateTimeoutSecs);
        }
        
        // if set, configure the overall transfer timeout
        //if (fileUploader->_uploadOverallTimeoutSecs > 0)
        //{
        //     curl_easy_setopt(curl, CURLOPT_NOSIGNAL, (long)1);
        //    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, fileUploader->_uploadOverallTimeoutSecs * 1000);
        // }
        
        if (useMultipart)
        {
            std::string uploadUrl = fileUploader->_uploadUrl;
            curl_easy_setopt(curl, CURLOPT_URL, uploadUrl.c_str());
            
            curl_formadd(&formpost,
                         &lastptr,
                         CURLFORM_COPYNAME, "sessionId",
                         CURLFORM_COPYCONTENTS, fileUploader->_sessionId.c_str(),
                         CURLFORM_END);
            
            curl_formadd(&formpost,
                         &lastptr,
                         CURLFORM_COPYNAME, "uploadId",
                         CURLFORM_COPYCONTENTS, fileUploader->_fileUploadId.c_str(),
                         CURLFORM_END);
            
            std::stringstream ss;
            ss << fileUploader->_fileLength;
            std::string fileSize = ss.str();
            curl_formadd(&formpost,
                         &lastptr,
                         CURLFORM_COPYNAME, "fileSize",
                         CURLFORM_COPYCONTENTS, fileSize.c_str(),
                         CURLFORM_END);
            
            curl_formadd(&formpost,
                         &lastptr,
                         CURLFORM_COPYNAME, "uploadFile",
                         CURLFORM_FILE, fileUploader->_fileName.c_str(),
                         CURLFORM_END);
            
            curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        }
        else
        {
            std::string uploadUrl = fileUploader->_uploadUrl;
            uploadUrl.append("?sessionId=");
            uploadUrl.append(fileUploader->_sessionId);
            uploadUrl.append("&uploadId=");
            uploadUrl.append(fileUploader->_fileUploadId);
            curl_easy_setopt(curl, CURLOPT_URL, uploadUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
            
            // NOTE: on windows if you use libcurl dll you need to set a READFUNCTION too.
            // We currently use a static lib so we're ok
            curl_easy_setopt(curl, CURLOPT_READDATA, fp);
            curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t) fileUploader->_fileLength);
            
            slist = curl_slist_append(slist, "Content-Type: application/octet-stream");
            std::stringstream ss;
            ss << "Content-Length: " << fileUploader->_fileLength;
            std::string contentLength = ss.str();
            slist = curl_slist_append(slist, contentLength.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
        }
        
        fileUploader->_curl = curl;
        
        rc = curl_easy_perform(curl);
        if (rc == CURLE_OK)
        {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &fileUploader->_httpStatus);
            
            if (fileUploader->_httpStatus == HTTP_OK)
            {
                fileUploader->_httpJsonResponse = fileUploader->_httpInternalResponse;
            }
            else
            {
                // if there's an error, attempt to parse the response into json, otherwise fake it
                Json::Value root;
                Json::Reader reader;
                if (reader.parse(fileUploader->_httpInternalResponse, root))
                {
                    fileUploader->_errorReasonCode = root["reason_code"].asInt();
                    fileUploader->_httpJsonResponse = fileUploader->_httpInternalResponse;
                }
                else
                {
                    fileUploader->_errorReasonCode = CLIENT_UPLOAD_FILE_UNKNOWN;
                    IBrainCloudComms::createJsonErrorResponse(fileUploader->_httpStatus,
                                                              fileUploader->_errorReasonCode,
                                                              fileUploader->_httpInternalResponse,
                                                              fileUploader->_httpJsonResponse);
                }
            }
        }
        else
        {
            fileUploader->_httpStatus = HTTP_CLIENT_NETWORK_ERROR;
            fileUploader->_errorReasonCode = 0;
            std::string statusMessage;
            if (rc == CURLE_OPERATION_TIMEDOUT)
            {
                statusMessage = "Upload timed out";
                fileUploader->_errorReasonCode = CLIENT_UPLOAD_FILE_TIMED_OUT;
            }
            else if (rc == CURLE_ABORTED_BY_CALLBACK)
            {
                statusMessage = "Upload cancelled by user";
                fileUploader->_errorReasonCode = CLIENT_UPLOAD_FILE_CANCELLED;
            }
            else
            {
                statusMessage = curlError;
                fileUploader->_errorReasonCode = CLIENT_UPLOAD_FILE_UNKNOWN;
            }
            IBrainCloudComms::createJsonErrorResponse(fileUploader->_httpStatus,
                                                      fileUploader->_errorReasonCode,
                                                      statusMessage,
                                                      fileUploader->_httpJsonResponse);
        }
        
        if (useMultipart)
        {
            curl_formfree(formpost);
        }
        else
        {
            curl_slist_free_all(slist);
        }
        
        curl_easy_cleanup(curl);
        
        if (fileUploader->_httpStatus == HTTP_OK)
        {
            fileUploader->setStatus(UPLOAD_STATUS_COMPLETE_SUCCESS);
        }
        else
        {
            fileUploader->setStatus(UPLOAD_STATUS_COMPLETE_FAILED);
        }
        
        if (_loggingEnabled)
        {
            Json::Reader reader;
            Json::StyledWriter writer;
            Json::Value root;
            reader.parse(fileUploader->_httpJsonResponse, root);
            std::string jsonOutput = writer.write(root);
            std::cout << "#BCC UPLOADER_INCOMING " << jsonOutput << std::endl;
        }
        fileUploader->_threadRunning = false;
    }
     */
//}

#endif