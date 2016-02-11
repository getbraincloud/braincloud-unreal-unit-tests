#ifndef _CURLFILEUPLOADER_H_
#define _CURLFILEUPLOADER_H_

#include <stdio.h>
#include <pthread.h>
#include <string>
#include "curl/curl.h"
#include "IFileUploader.h"

namespace BrainCloud
{
	class cURLFileUploader : public IFileUploader
	{

	public:
		cURLFileUploader();
		virtual ~cURLFileUploader();

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

        
	private:
		static void* run(void * in_fileUpload);
		static void uploadFileFromThread(cURLFileUploader * in_fileUploader);
		static int curlXferInfoCallback(void *data, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
		static int curlProgressCallback(void *data, double dltotal, double dlnow, double ultotal, double ulnow);
        static size_t curlWriteCallback(char *ptr, size_t size, size_t nmemb, void *userdata);

		void setStatus(eFileUploaderStatus in_status);
		void setProgress(curl_off_t ultotal, curl_off_t ulnow);

	private:
		static bool             _loggingEnabled;
        
		eFileUploaderStatus     _status;
		CURL *                  _curl;
        int                     _uploadLowTransferRateTimeoutSecs;
        int                     _uploadLowTransferRateThresholdBytesPerSec;

        std::string             _sessionId;
		std::string             _fileUploadId;
		long                    _fileLength;
		std::string             _fileName;
		std::string             _uploadUrl;
        
        int                     _httpStatus;
        int                     _errorReasonCode;
        std::string             _httpInternalResponse;
        std::string             _httpJsonResponse;

		pthread_attr_t          _threadAttributes;
		pthread_t               _threadId;
		pthread_mutex_t         _lock;
		bool                    _threadRunning;
        bool                    _shouldCancelUpload;
		long                    _uploadTotalBytes;
		long                    _uploadTransferredBytes;

	};

}

#endif /* _CURLFILEUPLOADER_H_ */
