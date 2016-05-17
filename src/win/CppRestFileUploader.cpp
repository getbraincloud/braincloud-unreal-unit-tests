#ifndef __ANDROID__

#include "braincloud/internal/win/CppRestFileUploader.h"

#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "braincloud/internal/IBrainCloudComms.h"

using namespace web::http;

namespace BrainCloud
{
    bool CppRestFileUploader::_loggingEnabled = false;

    CppRestFileUploader::CppRestFileUploader()
        : _status(IFileUploader::UPLOAD_STATUS_NONE)
        , _isThreadRunning(false)
        , _uploadLowTransferRateTimeoutSecs(0)
        , _uploadLowTransferRateThresholdBytesPerSec(0)
        , _fileLength(0)
        , _uploadTotalBytes(0)
        , _uploadTransferredBytes(0)
        , _shouldCancelUpload(false)
        , _httpStatus(0)
        , _errorReasonCode(0)
    {
    }

    CppRestFileUploader::~CppRestFileUploader()
    {
    }

    void CppRestFileUploader::enableLogging(bool in_loggingEnabled)
    {
        _loggingEnabled = in_loggingEnabled;
    }

    bool CppRestFileUploader::uploadFile(
        std::string & in_sessionId,
        std::string & in_fileUploadId,
        std::string & in_fileName,
        int64_t in_fileSize,
        std::string & in_uploadUrl)
    {
        if (_isThreadRunning)
        {
            return false; // this class is not re-entrant
        }
        _sessionId = in_sessionId;
        _fileUploadId = in_fileUploadId;
        _fileName = in_fileName;
        _fileLength = in_fileSize;
        _uploadUrl = in_uploadUrl;

        // this is an underestimation which is later improved upon by the actual http request body size
        _uploadTotalBytes = _fileLength;

        _isThreadRunning = true;
        _status = UPLOAD_STATUS_PENDING;
        _thread = std::thread(&CppRestFileUploader::run, this);
        _thread.detach();

        return true;
    }

    void CppRestFileUploader::setUploadLowTransferRateTimeout(int in_timeoutSecs)
    {
        _uploadLowTransferRateTimeoutSecs = in_timeoutSecs;
    }

    void CppRestFileUploader::setUploadLowTransferRateThreshold(int in_bytesPerSec)
    {
        _uploadLowTransferRateThresholdBytesPerSec = in_bytesPerSec;
    }

    void CppRestFileUploader::cancelUpload()
    {
        std::unique_lock<std::recursive_mutex> lock(_mutex);
        _shouldCancelUpload = true;
        if (_status == UPLOAD_STATUS_UPLOADING)
        {
            _cancelTokenSource.cancel();
        }
    }

    int64_t CppRestFileUploader::getBytesTransferred()
    {
        std::unique_lock<std::recursive_mutex> lock(_mutex);
        return _uploadTransferredBytes;
    }

    int64_t CppRestFileUploader::getTotalBytesToTransfer()
    {
        std::unique_lock<std::recursive_mutex> lock(_mutex);
        return _uploadTotalBytes;
    }

    double CppRestFileUploader::getProgress()
    {
        std::unique_lock<std::recursive_mutex> lock(_mutex);
        double progress = 0;
        if (_uploadTotalBytes > 0)
        {
            progress = _uploadTransferredBytes / (double)_uploadTotalBytes;
        }
        if (progress > 1.0)
        {
            progress = 1.0;
        }
        return progress;
    }

    IFileUploader::eFileUploaderStatus CppRestFileUploader::getStatus()
    {
        std::unique_lock<std::recursive_mutex> lock(_mutex);
        return _status;
    }

    const std::string & CppRestFileUploader::getHttpResponse()
    {
        return _httpJsonResponse;
    }

    int CppRestFileUploader::getHttpStatus()
    {
        return _httpStatus;
    }

    int CppRestFileUploader::getErrorReasonCode()
    {
        return _errorReasonCode;
    }

    bool CppRestFileUploader::isThreadRunning()
    {
        return _isThreadRunning;
    }

    bool CppRestFileUploader::buildHttpBody(const std::string & in_boundary, std::vector<unsigned char> & out_body)
    {
        out_body.clear();
        std::stringstream ss;
        std::string httpLineEnd = "\r\n";

        std::string endBoundary = "--";
        endBoundary += in_boundary;

        ss << httpLineEnd << endBoundary << httpLineEnd;
        ss << "Content-Disposition: form-data; name=\"sessionId\"" << httpLineEnd << httpLineEnd;
        ss << _sessionId << httpLineEnd << endBoundary << httpLineEnd;

        ss << "Content-Disposition: form-data; name=\"uploadId\"" << httpLineEnd << httpLineEnd;
        ss << _fileUploadId << httpLineEnd << endBoundary << httpLineEnd;

        ss << "Content-Disposition: form-data; name=\"fileSize\"" << httpLineEnd << httpLineEnd;
        ss << _fileLength << httpLineEnd << endBoundary << httpLineEnd;

        ss << "Content-Disposition: form-data; name=\"uploadFile\"; filename=\"" << _fileName << "\"" << httpLineEnd;
        ss << "Content-Type: application/octet-stream" << httpLineEnd << httpLineEnd;

        std::string preFileBody = ss.str();

        ss.str("");
        ss.clear();
        ss << httpLineEnd << endBoundary << "--";
        std::string postFileBody = ss.str();

        size_t preFileBodyLen = preFileBody.length();
        size_t postFileBodyLen = postFileBody.length();
        size_t bodyLength = preFileBodyLen + _fileLength + postFileBodyLen;
        out_body.resize(bodyLength);

        if (_loggingEnabled)
        {
            //std::cout << preFileBody << "XXXXXXXX" << postFileBody << std::endl;
        }

        size_t written = 0;
        for (size_t i = 0; i < preFileBodyLen; ++i, ++written)
        {
            out_body[written] = preFileBody[i];
        }

        FILE * fp = NULL;
        fopen_s(&fp, _fileName.c_str(), "rb");
        if (fp == NULL)
        {
            if (_loggingEnabled)
            {
                std::cout << "#BCC Cannot open file: " << _fileName << std::endl;
            }
            return false;
        }

        int byteRead = 0;
        for (size_t i = 0; i < (size_t) _fileLength; ++i, ++written)
        {
            byteRead = fgetc(fp);
            if (byteRead == EOF)
            {
                if (_loggingEnabled)
                {
                    std::cout << "#BCC Unexpected EOF while reading file:" << _fileName << std::endl;
                }
                fclose(fp);
                fp = NULL;
                return false;
            }
            out_body[written] = byteRead;
        }
        fclose(fp);
        fp = NULL;

        for (size_t i = 0; i < postFileBodyLen; ++i, ++written)
        {
            out_body[written] = postFileBody[i];
        }
        _uploadTotalBytes = out_body.size();

        return true;
    }

    void CppRestFileUploader::progressHandler(web::http::message_direction::direction in_direction, utility::size64_t in_bytesTransferred)
    {
        // they say not to lock in this function so I'm being loose

        if (in_direction == web::http::message_direction::upload)
        {
            _uploadTransferredBytes = in_bytesTransferred;
        }
    }

    void CppRestFileUploader::run(void * in_data)
    {
        CppRestFileUploader * fileUploader = reinterpret_cast<CppRestFileUploader*>(in_data);

        {
            std::unique_lock<std::recursive_mutex> lock(fileUploader->_mutex);
            fileUploader->_status = UPLOAD_STATUS_UPLOADING;
        }

        std::string boundary = "UploaderBoundary";
        boundary += fileUploader->_fileUploadId;

        std::vector<unsigned char> body;
        if (!fileUploader->buildHttpBody(boundary, body))
        {
            std::unique_lock<std::recursive_mutex> lock(fileUploader->_mutex);
            fileUploader->_status = UPLOAD_STATUS_COMPLETE_FAILED;
            fileUploader->_httpStatus = HTTP_CUSTOM;
            fileUploader->_errorReasonCode = CLIENT_UPLOAD_FILE_UNKNOWN;
            IBrainCloudComms::createJsonErrorResponse(
                fileUploader->_httpStatus,
                fileUploader->_errorReasonCode,
                "Creating HTTP body failed",
                fileUploader->_httpJsonResponse);
            
            fileUploader->_isThreadRunning = false;
            return;
        }

        utility::string_t url = utility::conversions::to_string_t(fileUploader->_uploadUrl);
        web::http::client::http_client_config cfg;
        // the default timeout is 30 seconds. If _uploadOverallTimeoutSecs is default (0)
        // then this call will set the timeout to be indefinite, otherwise the timeout
        // will be user-defined
        if (fileUploader->_uploadLowTransferRateTimeoutSecs > 0)
        {
            cfg.set_timeout(utility::seconds(fileUploader->_uploadLowTransferRateTimeoutSecs));
        }

        web::http::client::http_client client(url, cfg);
        web::http::http_request request;
        request.set_method(methods::POST);

        std::string contentType = "multipart/form-data; boundary=";
        contentType += boundary;
        utility::string_t utContentType = utility::conversions::to_string_t(contentType);
        request.headers().add(web::http::header_names::content_type, utContentType);

        std::stringstream ss;
        ss << body.size();
        std::string contentLength = ss.str();
        utility::string_t utContentLength = utility::conversions::to_string_t(contentLength);
        request.headers().add(web::http::header_names::content_length, utContentLength);

        request.set_body(body);

        // brutal code to create a progress callback to a member fn
        std::function<void(web::http::message_direction::direction in_direction, utility::size64_t in_bytesTransferred)> progressHandler =
            std::bind(&CppRestFileUploader::progressHandler, fileUploader, std::placeholders::_1, std::placeholders::_2);
        request.set_progress_handler(progressHandler);

        pplx::cancellation_token_source cts;
        pplx::task<web::http::http_response> httpTask = client.request(request, cts.get_token());

        {
            std::unique_lock<std::recursive_mutex> lock(fileUploader->_mutex);
            fileUploader->_cancelTokenSource = cts;
            fileUploader->_status = UPLOAD_STATUS_UPLOADING;
        }

        pplx::task_status taskStatus = pplx::task_status::canceled;
        bool requestTimedOut = false;
        if (!fileUploader->_shouldCancelUpload)
        {
            try
            {
                taskStatus = httpTask.wait(); // blocks
            }
            catch (web::http::http_exception e)
            {
                const char * err = e.what();
                int errCode = e.error_code().value();
                if (errCode == 12002 // timeout
                    || errCode == 12030 // server terminated connection abnormally
                    )
                {
                    requestTimedOut = true;
                }
                else
                {
                    if (fileUploader->_loggingEnabled)
                    {
                        // not sure what this error is
                    }
                }
            }
            catch (...)
            {
                // oh well... assume it was cancelled
            }
        }

        if (taskStatus == pplx::task_status::canceled)
        {
            std::unique_lock<std::recursive_mutex> lock(fileUploader->_mutex);
            fileUploader->_status = UPLOAD_STATUS_COMPLETE_FAILED;
            fileUploader->_httpStatus = HTTP_CUSTOM;
            if (requestTimedOut)
            {
                fileUploader->_errorReasonCode = CLIENT_UPLOAD_FILE_TIMED_OUT;
                IBrainCloudComms::createJsonErrorResponse(
                    fileUploader->_httpStatus,
                    fileUploader->_errorReasonCode,
                    "Upload timed out",
                    fileUploader->_httpJsonResponse);
            }
            else
            {
                fileUploader->_errorReasonCode = CLIENT_UPLOAD_FILE_CANCELLED;
                IBrainCloudComms::createJsonErrorResponse(
                    fileUploader->_httpStatus,
                    fileUploader->_errorReasonCode,
                    "Upload cancelled by user",
                    fileUploader->_httpJsonResponse);
            }
        }
        else if (taskStatus == pplx::task_status::completed)
        {
            web::http::http_response response = httpTask.get();

            pplx::task<utility::string_t> extractTask = response.extract_string();
            utility::string_t responseBody = extractTask.get();
            fileUploader->_httpInternalResponse = utility::conversions::to_utf8string(responseBody);
            web::http::status_code httpStatusCode = response.status_code();
            fileUploader->_httpStatus = httpStatusCode;

            std::unique_lock<std::recursive_mutex> lock(fileUploader->_mutex);

            if (httpStatusCode != web::http::status_codes::OK)
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

                //if (httpStatusCode == web::http::status_codes::RequestTimeout
                //    || httpStatusCode == web::http::status_codes::ServiceUnavailable)
                //{
                //}
                fileUploader->_status = UPLOAD_STATUS_COMPLETE_FAILED;
            }
            else
            {
                fileUploader->_status = UPLOAD_STATUS_COMPLETE_SUCCESS;
                fileUploader->_httpJsonResponse = fileUploader->_httpInternalResponse;
            }
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

        fileUploader->_isThreadRunning = false;
    }
}

#endif //__ANDROID__
