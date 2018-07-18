#include "braincloud/internal/win/XMLHTTPRequestFileUploader.h"
#include "braincloud/internal/IBrainCloudComms.h"

#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"

#include <json/json.h>

#include <algorithm>
#include <codecvt>
#include <condition_variable>
#include <iostream>
#include <thread>

static std::wstring utf8ToUtf16(const std::string& utf8)
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> stringConverter;
    return stringConverter.from_bytes(utf8);
}

namespace BrainCloud
{
    IFileUploader* IFileUploader::create()
    {
        return new XMLHTTPRequestFileUploader();
    }

    bool XMLHTTPRequestFileUploader::_loggingEnabled = false;

    struct UploaderCallback final : public IXMLHTTPRequest2Callback
    {
    public:
        UploaderCallback()
            : _refCount(1)
            , _completed(false)
            , _httpStatus(900)
        {
        }

        ~UploaderCallback()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _completed = true;
            _condition.notify_one();
        }

        HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID riid,
            _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObj) override
        {
            if (!ppvObj)
            {
                return E_INVALIDARG;
            }
            *ppvObj = NULL;
            if (riid == IID_IUnknown || riid == IID_IXMLHTTPRequest2Callback)
            {
                // Increment the reference count and return the pointer.
                *ppvObj = (LPVOID)this;
                AddRef();
                return NOERROR;
            }
            return E_NOINTERFACE;
        }

        ULONG STDMETHODCALLTYPE AddRef(void) override
        {
            InterlockedIncrement(&_refCount);
            return _refCount;
        }

        ULONG STDMETHODCALLTYPE Release(void) override
        {
            // Decrement the object's internal counter.
            ULONG ulRefCount = InterlockedDecrement(&_refCount);
            if (0 == _refCount)
            {
                delete this;
            }
            return ulRefCount;
        }

        HRESULT STDMETHODCALLTYPE OnRedirect(
            /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
            /* [string][in] */ __RPC__in_string const WCHAR *pwszRedirectUrl) override
        {
            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE OnHeadersAvailable(
            /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
            /* [in] */ DWORD dwStatus,
            /* [string][in] */ __RPC__in_string const WCHAR *pwszStatus) override
        {
            _httpStatus = (int)dwStatus;

            if (!pXHR)
            {
                return E_INVALIDARG;
            }

            // We don't care about headers response in the file uploader
            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE OnDataAvailable(
            /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
            /* [in] */ __RPC__in_opt ISequentialStream *pResponseStream) override
        {
            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE OnResponseReceived(
            /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
            /* [in] */ __RPC__in_opt ISequentialStream *pResponseStream) override
        {
            const int READ_BUFFER_MAX = 16 * 1024; // 16k
            char buffer[READ_BUFFER_MAX];
            ULONG byteRead;
            _resultMessage.clear();
            HRESULT hr;

            while (true)
            {
                hr = pResponseStream->Read(buffer, (ULONG)READ_BUFFER_MAX, &byteRead);
                if (FAILED(hr)) break;
                if (byteRead == 0) break;
                _resultMessage.append(buffer, byteRead);
            }

            std::unique_lock<std::mutex> lock(_mutex);
            _completed = true;
            _condition.notify_one();
            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE OnError(
            /* [in] */ __RPC__in_opt IXMLHTTPRequest2 *pXHR,
            /* [in] */ HRESULT hrError) override
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _completed = true;
            _condition.notify_one();
            return S_OK;
        }

        void waitForComplete()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _condition.wait(lock, [this]{ return _completed; });
        }

        int getHttpStatus() const
        {
            return _httpStatus;
        }

        const std::string& getResultMessage() const
        {
            return _resultMessage;
        }

    private:
        ULONG _refCount;
        std::mutex _mutex;
        bool _completed;
        std::condition_variable _condition;
        int _httpStatus;
        std::string _resultMessage;
    };

    class UploaderStream final : public ISequentialStream, public IDispatch
    {
    public:
        UploaderStream(FILE* fp, long size)
            : _refCount(1)
            , _fp(fp)
            , _size((ULONG)size)
            , _read(0)
        {
        }

        ~UploaderStream()
        {
            fclose(_fp);
        }

        HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID riid,
            _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObj) override
        {
            if (!ppvObj)
            {
                return E_INVALIDARG;
            }
            *ppvObj = NULL;
            if (riid == IID_IUnknown || riid == IID_ISequentialStream || riid == IID_IDispatch)
            {
                // Increment the reference count and return the pointer.
                *ppvObj = (LPVOID)this;
                AddRef();
                return NOERROR;
            }
            return E_NOINTERFACE;
        }

        ULONG STDMETHODCALLTYPE AddRef(void) override
        {
            InterlockedIncrement(&_refCount);
            return _refCount;
        }

        ULONG STDMETHODCALLTYPE Release(void) override
        {
            // Decrement the object's internal counter.
            ULONG ulRefCount = InterlockedDecrement(&_refCount);
            if (0 == _refCount)
            {
                delete this;
            }
            return ulRefCount;
        }

        HRESULT STDMETHODCALLTYPE GetTypeInfoCount(
            /* [out] */ __RPC__out UINT *pctinfo) override
        {
            if (pctinfo)
            {
                *pctinfo = 0;
            }
            return E_NOTIMPL;
        }

        HRESULT STDMETHODCALLTYPE GetTypeInfo(
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo) override
        {
            if (ppTInfo)
            {
                *ppTInfo = 0;
            }
            return E_NOTIMPL;
        }

        HRESULT STDMETHODCALLTYPE GetIDsOfNames(
            /* [in] */ __RPC__in REFIID riid,
            /* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
            /* [range][in] */ __RPC__in_range(0, 16384) UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId) override
        {
            return DISP_E_UNKNOWNNAME;
        }

        HRESULT STDMETHODCALLTYPE Invoke(
            /* [annotation][in] */
            _In_  DISPID dispIdMember,
            /* [annotation][in] */
            _In_  REFIID riid,
            /* [annotation][in] */
            _In_  LCID lcid,
            /* [annotation][in] */
            _In_  WORD wFlags,
            /* [annotation][out][in] */
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */
            _Out_opt_  UINT *puArgErr) override
        {
            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE Read(
            _Out_writes_bytes_to_(cb, *pcbRead)  void *pv,
            _In_  ULONG cb,
            _Out_opt_  ULONG *pcbRead) override
        {
            if (pv == nullptr)
            {
                return E_INVALIDARG;
            }

            auto toRead = std::min<ULONG>(_size - _read, cb);
            if (toRead)
            {
                fread(pv, 1, toRead, _fp);
            }
            *pcbRead = toRead;

            _mutex.lock();
            _read += toRead;
            _mutex.unlock();

            if (toRead < cb)
            {
                return S_FALSE;
            }

            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE Write(
            _In_reads_bytes_(cb)  const void *pv,
            _In_  ULONG cb,
            _Out_opt_  ULONG *pcbWritten) override
        {
            return S_OK;
        }

        ULONG getByteRead()
        {
            ULONG ret = 0;
            _mutex.lock();
            ret = _read;
            _mutex.unlock();
            return ret;
        }

    private:
        std::mutex _mutex;
        ULONG _refCount;
        FILE* _fp;
        ULONG _size;
        ULONG _read;
    };

    XMLHTTPRequestFileUploader::XMLHTTPRequestFileUploader()
        : _threadRunning(false)
        , _pRequest(nullptr)
        , _pUploaderStream(nullptr)
    {
    }

    XMLHTTPRequestFileUploader::~XMLHTTPRequestFileUploader()
    {
        close();
    }

    void XMLHTTPRequestFileUploader::close()
    {
        _mutex.lock();
        if (_pRequest)
        {
            _pRequest->Abort();
            _pRequest->Release();
            _pRequest = nullptr;
        }
        if (_pUploaderStream)
        {
            _pUploaderStream->Release();
            _pUploaderStream = nullptr;
        }
        _mutex.unlock();
    }

    void* XMLHTTPRequestFileUploader::run(void* fileUploader)
    {
        if (fileUploader != NULL)
        {
            XMLHTTPRequestFileUploader * theFileUploader = reinterpret_cast<XMLHTTPRequestFileUploader *>(fileUploader);
            uploadFileFromThread(theFileUploader);
        }

        return NULL;
    }

    void XMLHTTPRequestFileUploader::uploadFileFromThread(XMLHTTPRequestFileUploader* fileUploader)
    {
        HRESULT hr;
        IXMLHTTPRequest2* pRequest;

        // Open File
        FILE *fp = NULL;
        fopen_s(&fp, fileUploader->_fileName.c_str(), "rb");
        if (fp == NULL)
        {
            fileUploader->setStatus(UPLOAD_STATUS_COMPLETE_FAILED);
            fileUploader->_threadRunning = false;
            return;
        }

        fileUploader->setStatus(UPLOAD_STATUS_UPLOADING);

        // Create instances
        CoInitializeEx(NULL, COINIT_MULTITHREADED);
        CoCreateInstance(CLSID_FreeThreadedXMLHTTP60,
                         NULL,
                         CLSCTX_INPROC_SERVER,
                         IID_PPV_ARGS(&pRequest));
        UploaderCallback* pCallback = new UploaderCallback();
        UploaderStream* pUploaderStream = new UploaderStream(fp, fileUploader->_fileLength);

        // Open the URL
        std::string uploadUrl = fileUploader->_uploadUrl;
        uploadUrl.append("?sessionId=");
        uploadUrl.append(fileUploader->_sessionId);
        uploadUrl.append("&uploadId=");
        uploadUrl.append(fileUploader->_fileUploadId);
        auto urlw = utf8ToUtf16(uploadUrl);
        hr = pRequest->Open(L"PUT", 
                            urlw.c_str(),
                            pCallback,
                            NULL, NULL, NULL, NULL);

        // Set headers
        hr = pRequest->SetRequestHeader(L"Expect", L"100-continue");
        hr = pRequest->SetRequestHeader(L"Content-Length", std::to_wstring(fileUploader->_fileLength).c_str());
        hr = pRequest->SetRequestHeader(L"Content-Type", L"application/octet-stream");

        // Keep references in the uploader
        fileUploader->_mutex.lock();
        fileUploader->_pUploaderStream = pUploaderStream;
        fileUploader->_pUploaderStream->AddRef();
        fileUploader->_mutex.unlock();
        fileUploader->_mutex.lock();
        fileUploader->_pRequest = pRequest;
        fileUploader->_pRequest->AddRef();
        fileUploader->_mutex.unlock();

        // Send the request
        hr = pRequest->Send(pUploaderStream, (ULONGLONG)fileUploader->_fileLength);

        // Wait for completion
        pCallback->waitForComplete();

        // Get results
        fileUploader->_httpStatus = pCallback->getHttpStatus();
        if (fileUploader->_httpStatus == HTTP_OK)
        {
            fileUploader->_httpJsonResponse = pCallback->getResultMessage();
            fileUploader->setStatus(UPLOAD_STATUS_COMPLETE_SUCCESS);
        }
        else
        {
            // if there's an error, attempt to parse the response into json, otherwise fake it
            Json::Value root;
            Json::Reader reader;
            if (reader.parse(pCallback->getResultMessage(), root))
            {
                fileUploader->_errorReasonCode = root["reason_code"].asInt();
                fileUploader->_httpJsonResponse = pCallback->getResultMessage();
            }
            else
            {
                fileUploader->_mutex.lock();
                auto _pRequest = fileUploader->_pRequest;
                fileUploader->_mutex.unlock();
                if (!_pRequest)
                {
                    fileUploader->_errorReasonCode = CLIENT_UPLOAD_FILE_CANCELLED;
                }
                else
                {
                    fileUploader->_errorReasonCode = CLIENT_UPLOAD_FILE_UNKNOWN;
                }
                IBrainCloudComms::createJsonErrorResponse(fileUploader->_httpStatus,
                    fileUploader->_errorReasonCode,
                    pCallback->getResultMessage(),
                    fileUploader->_httpJsonResponse);
            }
            fileUploader->setStatus(UPLOAD_STATUS_COMPLETE_FAILED);
        }

        // Log
        if (_loggingEnabled)
        {
            Json::Reader reader;
            Json::StyledWriter writer;
            Json::Value root;
            reader.parse(fileUploader->_httpJsonResponse, root);
            std::string jsonOutput = writer.write(root);
            std::cout << "#BCC UPLOADER_INCOMING " << jsonOutput << std::endl;
        }

        // Free
        pRequest->Release();
        pRequest = nullptr;
        pCallback->Release();
        pCallback = nullptr;
        pUploaderStream->Release();
        pUploaderStream = nullptr;

        // We done
        fileUploader->_mutex.lock();
        if (fileUploader->_pRequest)
        {
            fileUploader->_pRequest->Release();
            fileUploader->_pRequest = nullptr;
        }
        if (fileUploader->_pUploaderStream)
        {
            fileUploader->_pUploaderStream->Release();
            fileUploader->_pUploaderStream = nullptr;
        }
        fileUploader->_mutex.unlock();
        fileUploader->_threadRunning = false;
    }

    bool XMLHTTPRequestFileUploader::uploadFile(std::string & in_sessionId,
                                                std::string & in_fileUploadId,
                                                std::string & in_fileName,
                                                int64_t in_fileSize,
                                                std::string & in_uploadUrl)
    {
        // load is sometimes called while prev thread is processing
        // so make sure to cleanup beforehand...
        close();

        _sessionId = in_sessionId;
        _fileUploadId = in_fileUploadId;
        _fileName = in_fileName;
        _uploadUrl = in_uploadUrl;
        _fileLength = static_cast<long>(in_fileSize);

        _threadRunning = true;
        _status = UPLOAD_STATUS_PENDING;
        auto thread = std::thread(run, this);
        thread.detach();

        return true;
    }

    void XMLHTTPRequestFileUploader::setStatus(eFileUploaderStatus in_status)
    {
        _mutex.lock();
        _status = in_status;
        _mutex.unlock();
    }

    void XMLHTTPRequestFileUploader::setUploadLowTransferRateTimeout(int in_timeoutSecs)
    {
    }

    void XMLHTTPRequestFileUploader::setUploadLowTransferRateThreshold(int in_bytesPerSec)
    {
    }

    void XMLHTTPRequestFileUploader::enableLogging(bool in_loggingEnabled)
    {
        _loggingEnabled = in_loggingEnabled;
    }

    IFileUploader::eFileUploaderStatus XMLHTTPRequestFileUploader::getStatus()
    {
        eFileUploaderStatus status;
        _mutex.lock();
        status = _status;
        _mutex.unlock();
        return status;
    }

    bool XMLHTTPRequestFileUploader::isThreadRunning()
    {
        return _threadRunning;
    }

    void XMLHTTPRequestFileUploader::cancelUpload()
    {
        _mutex.lock();
        if (_pRequest)
        {
            _pRequest->Abort();
            _pRequest->Release();
            _pRequest = nullptr;
        }
        if (_pUploaderStream)
        {
            _pUploaderStream->Release();
            _pUploaderStream = nullptr;
        }
        _mutex.unlock();
    }

    int64_t XMLHTTPRequestFileUploader::getBytesTransferred()
    {
        int64_t bytesTransferred = 0;
        _mutex.lock();
        if (_pUploaderStream)
        {
            bytesTransferred = (int64_t)_pUploaderStream->getByteRead();
        }
        _mutex.unlock();
        return bytesTransferred;
    }

    int64_t XMLHTTPRequestFileUploader::getTotalBytesToTransfer()
    {
        return _fileLength;
    }

    double XMLHTTPRequestFileUploader::getProgress()
    {
        return (double)getBytesTransferred() / (double)_fileLength;
    }

    const std::string & XMLHTTPRequestFileUploader::getHttpResponse()
    {
        return _httpJsonResponse;
    }

    int XMLHTTPRequestFileUploader::getHttpStatus()
    {
        return _httpStatus;
    }

    int XMLHTTPRequestFileUploader::getErrorReasonCode()
    {
        return _errorReasonCode;
    }
}
