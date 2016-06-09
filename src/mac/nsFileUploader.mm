//
//  nsFileUploader.m
//  BrainCloudCpp
//
//  Created by Preston Jennings on 2016-06-03.
//  Copyright © 2016 BitHeads Inc. All rights reserved.
//

// The meat of this class was found on stack overflow:
// http://stackoverflow.com/questions/24250475/post-multipart-form-data-with-objective-c

#ifdef __APPLE__

#import <Foundation/Foundation.h>
#include <TargetConditionals.h>
#include "braincloud/internal/mac/nsFileUploader.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "braincloud/internal/IBrainCloudComms.h"


@implementation ObjcFileUploader

- (id) init
{
    if ((self = [super init]))
    {
        _cancelled = false;
        _httpStatus = 0;
        _errorReasonCode = 0;
        _uploadLowTransferRateTimeout = 0;
    }
    return self;
}

- (NSString *)generateBoundaryString
{
    return [NSString stringWithFormat:@"Boundary-%@", [[NSUUID UUID] UUIDString]];
}

- (NSData *)createBodyWithBoundary:(NSString *)boundary
                        parameters:(NSDictionary *)parameters
                             paths:(NSArray *)paths
                         fieldName:(NSString *)fieldName
{
    NSMutableData *httpBody = [NSMutableData data];
    
    // add params (all params are strings)
    
    [parameters enumerateKeysAndObjectsUsingBlock:^(NSString *parameterKey, NSString *parameterValue, BOOL *stop) {
        [httpBody appendData:[[NSString stringWithFormat:@"--%@\r\n", boundary] dataUsingEncoding:NSUTF8StringEncoding]];
        [httpBody appendData:[[NSString stringWithFormat:@"Content-Disposition: form-data; name=\"%@\"\r\n\r\n", parameterKey] dataUsingEncoding:NSUTF8StringEncoding]];
        [httpBody appendData:[[NSString stringWithFormat:@"%@\r\n", parameterValue] dataUsingEncoding:NSUTF8StringEncoding]];
    }];
    
    // add data
    
    for (NSString *path in paths) {
        NSString *filename  = [path lastPathComponent];
        NSData   *data      = [NSData dataWithContentsOfFile:path];
        NSString *mimetype  = @"application/octet-stream"; // deviation from original source to always assume generic type
        
        [httpBody appendData:[[NSString stringWithFormat:@"--%@\r\n", boundary] dataUsingEncoding:NSUTF8StringEncoding]];
        [httpBody appendData:[[NSString stringWithFormat:@"Content-Disposition: form-data; name=\"%@\"; filename=\"%@\"\r\n", fieldName, filename] dataUsingEncoding:NSUTF8StringEncoding]];
        [httpBody appendData:[[NSString stringWithFormat:@"Content-Type: %@\r\n\r\n", mimetype] dataUsingEncoding:NSUTF8StringEncoding]];
        [httpBody appendData:data];
        [httpBody appendData:[@"\r\n" dataUsingEncoding:NSUTF8StringEncoding]];
    }
    
    [httpBody appendData:[[NSString stringWithFormat:@"--%@--\r\n", boundary] dataUsingEncoding:NSUTF8StringEncoding]];
    
    return httpBody;
}

- (void)uploadFileWithSessionId:(NSString*)sessionId
                   fileUploadId:(NSString*)fileUploadId
                       fileName:(NSString*)fileName
                       fileSize:(NSInteger)fileSize
                      uploadUrl:(NSString*)uploadUrl
{
    NSURL *url = [NSURL URLWithString:uploadUrl];
    
    NSDictionary *params = @{@"sessionId"   : sessionId,
                             @"uploadId"    : fileUploadId,
                             @"fileSize"    : [@(fileSize) stringValue]};
    
    NSString *boundary = [self generateBoundaryString];
    
    // configure the request
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:url];
    [request setHTTPMethod:@"POST"];
    
    // set content type
    NSString *contentType = [NSString stringWithFormat:@"multipart/form-data; boundary=%@", boundary];
    [request setValue:contentType forHTTPHeaderField: @"Content-Type"];
    
    // create body
    NSData *httpBody = [self createBodyWithBoundary:boundary parameters:params paths:@[fileName] fieldName:@"uploadFile"];
    
    request.HTTPBody = httpBody;
    
    
    NSURLSessionConfiguration *sessionConfig = [NSURLSessionConfiguration ephemeralSessionConfiguration];
    if (_uploadLowTransferRateTimeout > 0)
    {
        // timeout waiting for next bit of data
        sessionConfig.timeoutIntervalForRequest = _uploadLowTransferRateTimeout;
        
        // overall timeout
        //sessionConfig.timeoutIntervalForResource = 60.0;
    }
    NSURLSession * session = [NSURLSession sessionWithConfiguration:sessionConfig];
    
    NSURLSessionTask *task = [session dataTaskWithRequest:request completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
        if (error) {
            NSLog(@"error = %@", error);
            _httpStatus = HTTP_CLIENT_NETWORK_ERROR;
            _errorReasonCode = _cancelled ? CLIENT_UPLOAD_FILE_CANCELLED : CLIENT_UPLOAD_FILE_UNKNOWN;
            return;
        }
        
        _httpResponse = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        NSHTTPURLResponse * urlResponse = (NSHTTPURLResponse*) response;
        if (urlResponse != nil)
        {
            _httpStatus = urlResponse.statusCode;
        }
        
        Json::Value root;
        Json::Reader reader;
        std::string strHttpResponse = [_httpResponse cStringUsingEncoding:NSUTF8StringEncoding];
        if (reader.parse(strHttpResponse, root))
        {
            _errorReasonCode = root["reason_code"].asInt();
        }
        else
        {
            std::string strHttpJsonResponse;
            _errorReasonCode = CLIENT_UPLOAD_FILE_UNKNOWN;
            BrainCloud::IBrainCloudComms::createJsonErrorResponse(static_cast<int>(_httpStatus),
                                                      static_cast<int>(_errorReasonCode),
                                                      strHttpResponse,
                                                      strHttpJsonResponse);
            _httpResponse = [NSString stringWithCString:strHttpJsonResponse.c_str() encoding:NSUTF8StringEncoding];
        }
    }];
    self.task = task;
    [task resume];
}

- (BOOL) isThreadRunning
{
    if (self.task == nil)
    {
        return false;
    }
    return !(self.task.state == NSURLSessionTaskStateCompleted);
}

- (void) cancelUpload
{
    if (self.task != nil)
    {
        [self.task cancel];
        _cancelled = YES;
    }
}

- (NSInteger) getBytesTransferred
{
    if (self.task == nil)
    {
        return 0;
    }
    
    return static_cast<NSInteger>([self.task countOfBytesSent]);
}

- (NSInteger) getTotalBytesToTransfer
{
    if (self.task == nil)
    {
        return 0;
    }
    return static_cast<NSInteger>([self.task countOfBytesExpectedToSend]);
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
        _uploader = nil;
    }
    
    bool NSFileUploader::uploadFile(std::string & in_sessionId,
                                      std::string & in_fileUploadId,
                                      std::string & in_fileName,
                                      int64_t in_fileSize,
                                      std::string & in_uploadUrl)
    {
        NSString * sessionId = [NSString stringWithCString:in_sessionId.c_str() encoding:NSUTF8StringEncoding];
        NSString * fileUploadId = [NSString stringWithCString:in_fileUploadId.c_str() encoding:NSUTF8StringEncoding];
        NSString * fileName = [NSString stringWithCString:in_fileName.c_str() encoding:NSUTF8StringEncoding];
        NSInteger fileSize = static_cast<NSInteger> (in_fileSize);
        NSString * uploadUrl = [NSString stringWithCString:in_uploadUrl.c_str() encoding:NSUTF8StringEncoding];
        
        [_uploader uploadFileWithSessionId:sessionId fileUploadId:fileUploadId fileName:fileName fileSize:fileSize uploadUrl:uploadUrl];
        return true;
    }
    
    void NSFileUploader::setUploadLowTransferRateTimeout(int in_timeoutSecs)
    {
        _uploader.uploadLowTransferRateTimeout = in_timeoutSecs;
    }
    
    void NSFileUploader::setUploadLowTransferRateThreshold(int in_bytesPerSec)
    {
        // does nothing
    }
    
    void NSFileUploader::enableLogging(bool in_loggingEnabled)
    {
        _loggingEnabled = in_loggingEnabled;
    }
    
    IFileUploader::eFileUploaderStatus NSFileUploader::getStatus()
    {
        if (_uploader.task == nil)
        {
            return UPLOAD_STATUS_NONE;
        }
        
        if (_uploader.task.state == NSURLSessionTaskStateSuspended)
        {
            return UPLOAD_STATUS_PENDING;
        }
        else if (_uploader.task.state == NSURLSessionTaskStateCompleted)
        {
            return (_uploader.httpStatus == HTTP_OK) ? UPLOAD_STATUS_COMPLETE_SUCCESS : UPLOAD_STATUS_COMPLETE_FAILED;
        }
        
        return UPLOAD_STATUS_UPLOADING;
    }
    
    bool NSFileUploader::isThreadRunning()
    {
        return [_uploader isThreadRunning];
    }
    
    void NSFileUploader::cancelUpload()
    {
        [_uploader cancelUpload];
    }
    
    int64_t NSFileUploader::getBytesTransferred()
    {
        return [_uploader getBytesTransferred];
    }
    
    int64_t NSFileUploader::getTotalBytesToTransfer()
    {
        return [_uploader getTotalBytesToTransfer];
    }
    
    double NSFileUploader::getProgress()
    {
        return getBytesTransferred() / (double) getTotalBytesToTransfer();
    }
    
    // these are only safe to call when thread running is false
    const std::string & NSFileUploader::getHttpResponse()
    {
        NSString * nsHttpResponse = [_uploader httpResponse];
        if (nsHttpResponse != nil)
        {
            _httpResponse = [nsHttpResponse cStringUsingEncoding:NSUTF8StringEncoding];
        }
        return _httpResponse;
    }
    
    // these are only safe to call when thread running is false
    int NSFileUploader::getHttpStatus()
    {
        return static_cast<int>([_uploader httpStatus]);
    }
    
    // these are only safe to call when thread running is false
    int NSFileUploader::getErrorReasonCode()
    {
        return static_cast<int>([_uploader errorReasonCode]);
    }
}

#endif