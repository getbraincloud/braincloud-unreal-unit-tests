#include "cURLFileUploader.h"

#if defined(__APPLE__) && !defined(HG_PLATFORM_BB)
#include "TargetConditionals.h"
#endif

#ifdef HG_PLATFORM_BB
#include <stdio.h>
#include <ctype.h>
#endif

#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include "http_codes.h"
#include "reason_codes.h"
#include "IBrainCloudComms.h"

namespace BrainCloud
{
    bool cURLFileUploader::_loggingEnabled = false;
    
    cURLFileUploader::cURLFileUploader()
    : _status(UPLOAD_STATUS_NONE)
    , _curl(NULL)
    , _uploadLowTransferRateTimeoutSecs(0)
    , _uploadLowTransferRateThresholdBytesPerSec(0)
    , _fileLength(0)
    , _httpStatus(0)
    , _errorReasonCode(0)
    , _threadRunning(false)
    , _shouldCancelUpload(false)
    {
        memset(&_threadId, 0, sizeof(pthread_t));
        memset(&_threadAttributes, 0, sizeof(_threadAttributes));
        memset(&_lock, 0, sizeof(_lock));
        
        int rc = 0;
        rc = pthread_mutex_init(&_lock, NULL);
        if (rc != 0)
        {
            if (_loggingEnabled)
            {
                std::cout << "#BCC Couldn't create mutex, returned " << rc << std::endl;
            }
        }
    }
    
    
    cURLFileUploader::~cURLFileUploader()
    {
        close();
        pthread_mutex_destroy(&_lock);
    }
    
    
    void cURLFileUploader::close()
    {
        if ( _threadRunning )
        {
            pthread_attr_destroy(&_threadAttributes);
            /*
             if (_threadId != 0)
             {
             pthread_join(_threadId, NULL);
             }
             */
            _threadRunning = false;
        }
    }
    
    
    bool cURLFileUploader::uploadFile(std::string & in_sessionId,
                                      std::string & in_fileUploadId,
                                      std::string & in_fileName,
                                      int64_t in_fileSize,
                                      std::string & in_uploadUrl)
    {
        /* don't need to initialize as the other curlloader
         class will handle this for us (and is guaranteed to
         be called first
         if ( ! _initialized )
         {
         curl_global_init(CURL_GLOBAL_ALL);
         _initialized = true;
         }
         */
        
        
        // load is sometimes called while prev thread is processing
        // so make sure to cleanup beforehand...
        close();
        
        _sessionId = in_sessionId;
        _fileUploadId = in_fileUploadId;
        _fileName = in_fileName;
        _uploadUrl = in_uploadUrl;
        _fileLength = in_fileSize;
        
        int rc = 0;
        rc = pthread_attr_init(&_threadAttributes);
        if (rc != 0)
        {
            if (_loggingEnabled)
            {
                std::cout << "#BCC Couldn't initialize pthread attributes for file upload, returned " << rc << std::endl;
            }
            return false;
        }
        
        rc = pthread_attr_setdetachstate(&_threadAttributes, PTHREAD_CREATE_DETACHED);
        if (rc != 0)
        {
            if (_loggingEnabled)
            {
                std::cout << "#BCC Couldn't set detach state on pthread, returned " << rc << std::endl;
            }
            pthread_attr_destroy(&_threadAttributes);
            return false;
        }
        
        _threadRunning = true;
        _status = UPLOAD_STATUS_PENDING;
        rc = pthread_create(&_threadId, &_threadAttributes, &run, this);
        if (rc != 0)
        {
            if (_loggingEnabled)
            {
                std::cout << "#BCC Failed to create pthread, returned " << rc << std::endl;
            }
            close();
            return false;
        }
        
        return true;
    }
    
    void cURLFileUploader::setUploadLowTransferRateTimeout(int in_timeoutSecs)
    {
        _uploadLowTransferRateTimeoutSecs = in_timeoutSecs;
    }
    
    void cURLFileUploader::setUploadLowTransferRateThreshold(int in_bytesPerSec)
    {
        _uploadLowTransferRateThresholdBytesPerSec = in_bytesPerSec;
    }
    
    void * cURLFileUploader::run(void * fileUploader)
    {
        if (fileUploader != NULL)
        {
            cURLFileUploader * theFileUploader = reinterpret_cast<cURLFileUploader *>(fileUploader);
            uploadFileFromThread(theFileUploader);
        }
        
        return NULL;
    }
    
    void cURLFileUploader::enableLogging(bool in_loggingEnabled)
    {
        _loggingEnabled = in_loggingEnabled;
    }
    
    IFileUploader::eFileUploaderStatus cURLFileUploader::getStatus()
    {
        eFileUploaderStatus status;
        pthread_mutex_lock(&_lock);
        status = _status;
        pthread_mutex_unlock(&_lock);
        return _status;
    }
    
    bool cURLFileUploader::isThreadRunning()
    {
        return _threadRunning;
    }
    
    void cURLFileUploader::cancelUpload()
    {
        pthread_mutex_lock(&_lock);
        if (_curl != NULL)
        {
            _shouldCancelUpload = true;
        }
        pthread_mutex_unlock(&_lock);
    }
    
    int64_t cURLFileUploader::getBytesTransferred()
    {
        int64_t bytesTransferred = 0;
        pthread_mutex_lock(&_lock);
        if (_curl != NULL)
        {
            bytesTransferred = _uploadTransferredBytes;
        }
        pthread_mutex_unlock(&_lock);
        return bytesTransferred;
    }
    
    int64_t cURLFileUploader::getTotalBytesToTransfer()
    {
        return _fileLength;
    }
    
    double cURLFileUploader::getProgress()
    {
        double result = 0;
        pthread_mutex_lock(&_lock);
        if (_curl != NULL && _uploadTotalBytes > 0)
        {
            result = _uploadTransferredBytes / (double) _uploadTotalBytes;
        }
        pthread_mutex_unlock(&_lock);
        return result;
    }
    
    void cURLFileUploader::setProgress(curl_off_t ultotal, curl_off_t ulnow)
    {
        pthread_mutex_lock(&_lock);
        _uploadTotalBytes = ultotal;
        _uploadTransferredBytes = ulnow;
        pthread_mutex_unlock(&_lock);
    }
    
    // curl ver 7.32 (aug 2013) support xferinfo cb
    int cURLFileUploader::curlXferInfoCallback(void *data, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
    {
        cURLFileUploader * fileUploader = reinterpret_cast<cURLFileUploader*>(data);
        fileUploader->setProgress(ultotal, ulnow);
        
        if (fileUploader->_shouldCancelUpload)
        {
            return 1; // causes CURLE_ABORTED_BY_CALLBACK to be returned from perform
        }
        return CURLE_OK;
    }
    
    // previous curl versions use this function
    int cURLFileUploader::curlProgressCallback(void *data, double dltotal, double dlnow, double ultotal, double ulnow)
    {
        cURLFileUploader * fileUploader = reinterpret_cast<cURLFileUploader*>(data);
        fileUploader->setProgress((curl_off_t) ultotal, (curl_off_t) ulnow);
        
        if (fileUploader->_shouldCancelUpload)
        {
            return 1; // causes CURLE_ABORTED_BY_CALLBACK to be returned from perform
        }
        return CURLE_OK;
    }

    
    size_t cURLFileUploader::curlWriteCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
    {
        cURLFileUploader * fileUploader = reinterpret_cast<cURLFileUploader*>(userdata);
        size_t writeSize = size * nmemb;
        char * buf = new char[writeSize + sizeof(char)];
        memcpy(buf, ptr, writeSize);
        buf[writeSize] = '\0';
        fileUploader->_httpInternalResponse.append(buf);
        return writeSize;
    }
    
    void cURLFileUploader::setStatus(eFileUploaderStatus in_status)
    {
        pthread_mutex_lock(&_lock);
        _status = in_status;
        pthread_mutex_unlock(&_lock);
    }
    
    // these are only safe to call when thread running is false
    const std::string & cURLFileUploader::getHttpResponse()
    {
        return _httpJsonResponse;
    }
    
    // these are only safe to call when thread running is false
    int cURLFileUploader::getHttpStatus()
    {
        return _httpStatus;
    }
    
    // these are only safe to call when thread running is false
    int cURLFileUploader::getErrorReasonCode()
    {
        return _errorReasonCode;
    }
    
    /*
    int debug_callback(CURL *handle,
                       curl_infotype type,
                       char *data,
                       size_t size,
                       void *userptr)
    {
        if (type == CURLINFO_HEADER_IN
            || type == CURLINFO_HEADER_OUT)
        {
            printf("--%s", data);
        }
    }
     */
    
    /**
     * Use libCurl to upload the file
     *
     * @param loader - pointer to the object which is loading the web page
     */
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
            fileUploader->_httpStatus = HTTP_CUSTOM;
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
}
