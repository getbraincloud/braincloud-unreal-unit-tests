#ifndef __ANDROID__

#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include "cpprest/http_client.h"
#include "braincloud/internal/IFileUploader.h"


namespace BrainCloud
{
    class CppRestFileUploader : public IFileUploader
    {
    public:
        CppRestFileUploader();
        virtual ~CppRestFileUploader();

        virtual void enableLogging(bool in_loggingEnabled);

        virtual bool uploadFile(std::string & in_sessionId,
            std::string & in_fileUploadId,
            std::string & in_fileName,
            int64_t in_fileSize,
            std::string & in_uploadUrl);
        
        virtual void setUploadLowTransferRateTimeout(int in_timeoutSecs);
        virtual void setUploadLowTransferRateThreshold(int in_bytesPerSec);

        virtual void cancelUpload();
        virtual int64_t getBytesTransferred();
        virtual int64_t getTotalBytesToTransfer();
        virtual double getProgress();

        virtual eFileUploaderStatus getStatus();
        virtual const std::string & getHttpResponse();
        virtual int getHttpStatus();
        virtual int getErrorReasonCode();

        virtual bool isThreadRunning();

    private:
        static void run(void * in_data);
        bool buildHttpBody(const std::string & in_boundary, std::vector<unsigned char> & out_body);
        void progressHandler(web::http::message_direction::direction in_direction, utility::size64_t in_bytesTransferred);

    private:
        static bool _loggingEnabled;

        eFileUploaderStatus _status;
        std::thread _thread;
        std::recursive_mutex _mutex;
        bool _isThreadRunning;

        int _uploadLowTransferRateTimeoutSecs;
        int _uploadLowTransferRateThresholdBytesPerSec;

        std::string _sessionId;
        std::string _fileUploadId;
        std::string _fileName;
        std::string _uploadUrl;
        long _fileLength;
        int64_t _uploadTotalBytes;
        int64_t _uploadTransferredBytes;

        bool _shouldCancelUpload;
        int _httpStatus;
        int _errorReasonCode;
        std::string _httpInternalResponse;
        std::string _httpJsonResponse;
        pplx::cancellation_token_source _cancelTokenSource;
    };
}

#endif //__ANDROID__
