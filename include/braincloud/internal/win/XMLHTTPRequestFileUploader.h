#ifndef _XMLHTTPREQUESTFILEUPLOADER_H_
#define _XMLHTTPREQUESTFILEUPLOADER_H_

#include "braincloud/internal/IFileUploader.h"

#include <atomic>
#include <mutex>

#include <msxml6.h>

namespace BrainCloud
{
    class UploaderStream;

    class XMLHTTPRequestFileUploader : public IFileUploader
    {

    public:
        virtual ~XMLHTTPRequestFileUploader();

        void close();
        
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

        XMLHTTPRequestFileUploader();
        
    private:
        static void* run(void* in_fileUpload);
        static void uploadFileFromThread(XMLHTTPRequestFileUploader* in_fileUploader);

        void setStatus(eFileUploaderStatus in_status);

        static bool _loggingEnabled;

        std::string             _sessionId;
        std::string             _fileUploadId;
        long                    _fileLength;
        std::string             _fileName;
        std::string             _uploadUrl;

        int                     _httpStatus;
        int                     _errorReasonCode;
        std::string             _httpJsonResponse;

        eFileUploaderStatus     _status;
        std::atomic<bool>       _threadRunning;
        std::mutex              _mutex;
        IXMLHTTPRequest2*       _pRequest = nullptr;
        UploaderStream*         _pUploaderStream = nullptr;
    };
}

#endif /* _XMLHTTPREQUESTFILEUPLOADER_H_ */
