//
//  IFileUploader.h
//  GameClientLib
//
//  Created by brainCloud Team on 2016-01-13.
//
//

#ifndef _IFILEUPLOADER_H_
#define _IFILEUPLOADER_H_

#include "braincloud/BrainCloudTypes.h"
#include <string>

namespace BrainCloud
{
    class IFileUploader
    {
    public:
        enum eFileUploaderStatus
        {
            UPLOAD_STATUS_NONE = 0,
            UPLOAD_STATUS_PENDING = 1,
            UPLOAD_STATUS_UPLOADING = 2,
            UPLOAD_STATUS_COMPLETE_FAILED = 3,
            UPLOAD_STATUS_COMPLETE_SUCCESS = 4
        };

        // Factory method
        static IFileUploader* create();

        virtual ~IFileUploader() {};

        virtual void enableLogging(bool in_loggingEnabled) = 0;

        virtual bool uploadFile(std::string & in_sessionId,
            std::string & in_fileUploadId,
            std::string & in_fileName,
            int64_t in_fileSize,
            std::string & in_uploadUrl) = 0;

        virtual void setUploadLowTransferRateTimeout(int in_timeoutSecs) = 0;
        virtual void setUploadLowTransferRateThreshold(int in_bytesPerSec) = 0;
        
        virtual void cancelUpload() = 0;
        virtual int64_t getBytesTransferred() = 0;
        virtual int64_t getTotalBytesToTransfer() = 0;
        virtual double getProgress() = 0;

        virtual eFileUploaderStatus getStatus() = 0;
        virtual const std::string & getHttpResponse() = 0;
        virtual int getHttpStatus() = 0;
        virtual int getErrorReasonCode() = 0;

        virtual bool isThreadRunning() = 0;

    protected:
        IFileUploader() {}
    };
}

#endif /* _IFILEUPLOADER_H_ */
