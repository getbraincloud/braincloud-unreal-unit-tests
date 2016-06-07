#ifndef _NSFILEUPLOADER_H_
#define _NSFILEUPLOADER_H_

#ifdef __APPLE__
#include <string>
#include "braincloud/internal/IFileUploader.h"

/*
@interface ObjcFileUploader : NSObject<NSURLConnectionDataDelegate>
@end

namespace BrainCloud
{
    class NSFileUploader : public IFileUploader
    {
        
    public:
        NSFileUploader();
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
        
    private:
        static bool             _loggingEnabled;
        ObjcFileUploader *      _uploader;
    };
    
}
*/
#endif
#endif
