#ifndef _NSFILEUPLOADER_H_
#define _NSFILEUPLOADER_H_

#ifdef __APPLE__
#include <string>
#include "braincloud/internal/IFileUploader.h"


#if defined (__OBJC__)
#import <Foundation/Foundation.h>
@interface ObjcFileUploader : NSObject

@property (nonatomic, strong) NSURLSessionTask* task;
@property (nonatomic, strong) NSString* httpResponse;
@property (nonatomic, readonly) BOOL cancelled;
@property (nonatomic, readonly) NSInteger httpStatus;
@property (nonatomic, readonly) NSInteger errorReasonCode;
@property (nonatomic) NSInteger uploadLowTransferRateTimeout;

- (BOOL) isThreadRunning;
- (void) cancelUpload;
- (NSInteger) getBytesTransferred;
- (NSInteger) getTotalBytesToTransfer;
@end
#else
class ObjcFileUploader;
#endif


namespace BrainCloud
{
    class NSFileUploader : public IFileUploader
    {
        
    public:
        virtual ~NSFileUploader();
        
        virtual bool uploadFile(std::string & in_sessionId,
                                std::string & in_fileUploadId,
                                std::string & in_fileName,
                                int64_t in_fileSize,
                                std::string & in_uploadUrl);
        
        virtual void setUploadLowTransferRateTimeout(int in_timeoutSecs);
        virtual void setUploadLowTransferRateThreshold(int in_bytesPerSec);
        
        virtual void enableLogging(bool in_loggingEnabled);
        
        virtual eFileUploaderStatus getStatus();
        virtual bool isThreadRunning();
        
        virtual void cancelUpload();
        virtual int64_t getBytesTransferred();
        virtual int64_t getTotalBytesToTransfer();
        virtual double getProgress();
        virtual const std::string & getHttpResponse();
        virtual int getHttpStatus();
        virtual int getErrorReasonCode();

    protected:
        friend class IFileUploader;

        NSFileUploader();
        
    private:
        static bool             _loggingEnabled;
        ObjcFileUploader *              _uploader;
        
        // to cache the http response as "getHttpResponse" fn uses a reference
        std::string             _httpResponse;
    };
    
}
#endif
#endif
