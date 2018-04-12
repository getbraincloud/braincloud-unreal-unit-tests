//
//  IwHttpLoader.cpp
//  GameClientLib
//

#if defined(IW_SDK)

#define DEFAULT_TIMEOUT_MILLIS 30000

#if ( defined(GAMECLIENT_DEBUGLEVEL)  &&  GAMECLIENT_DEBUGLEVEL > 0 )
#   include <iostream>
#endif
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <IwHTTP.h>
#include <iostream>
#include "braincloud/http_codes.h"
#include "braincloud/internal/URLRequestMethod.h"
#include "braincloud/internal/marmalade/IwHttpLoader.h"

namespace BrainCloud
{
    URLLoader* URLLoader::create()
    {
        return new IwHttpLoader();
    }

    IwHttpLoader::IwHttpLoader()
        : _state(StatusNone)
        , _iwhttp(NULL)
        , _timeoutMillis(DEFAULT_TIMEOUT_MILLIS)
    {
    }

    IwHttpLoader::~IwHttpLoader()
    {
        close();
        if (_iwhttp != NULL)
        {
            delete _iwhttp;
            _iwhttp = NULL;
        }
    }

    void IwHttpLoader::close()
    {
        if (_iwhttp != NULL && _state >= StatusHttpSendingRequest && _state <= StatusHttpReadingResponse)
        {
            setNetworkErrorResponse();
            _iwhttp->Cancel();
            _state = StatusCanceled;
        }
    }

    void IwHttpLoader::load(URLRequest const & urlRequest)
    {
        if (_state != StatusNone)
        {
            return;
        }
        _state = StatusHttpSendingRequest;
        _iwhttp = new CIwHTTP();

        setRequest(urlRequest);

        // add in the headers
        std::vector<URLRequestHeader> headers = urlRequest.getHeaders();
        for (size_t i = 0, isize = headers.size(); i < isize; ++i)
        {
            URLRequestHeader header = headers[i];
            std::string name = header.getName();
            std::string value = header.getValue();
            _iwhttp->SetRequestHeader(name.c_str(), value.c_str());
        }

        // and issue the request
        const char * uri = urlRequest.getUrl().c_str();
        const char * body = urlRequest.getData().c_str();
        int32_t bodyLen = (int32_t)urlRequest.getData().size();
        s3eResult result = S3E_RESULT_ERROR;
        if (urlRequest.getMethod() == URLRequestMethod::GET)
        {
            result = _iwhttp->Get(uri, statusCallback, this);
        }
        else if (urlRequest.getMethod() == URLRequestMethod::POST)
        {
            _iwhttp->SetRequestHeader("Content-Type", "application/json");
            result = _iwhttp->Post(uri, body, bodyLen, statusCallback, this);
        }
        else if (urlRequest.getMethod() == URLRequestMethod::PUT)
        {
            result = _iwhttp->Put(uri, body, bodyLen, statusCallback, this);
        }

        if (result == S3E_RESULT_ERROR)
        {
            if (_loggingEnabled)
            {
                std::cout << "#BCC Failed to start iwhttp request" << std::endl;
            }
            close();
        }
    }

    bool IwHttpLoader::isDone()
    {
        if (_state == StatusHttpReadingResponse)
        {
            // check for read callbacks etc
            if (_iwhttp)
            {
                if (_iwhttp->ContentFinished())
                {
                    _urlResponse.setStatusCode(_iwhttp->GetResponseCode());
                    _state = StatusCompleteSuccess;
                }
            }
        }

        return _state >= StatusCanceled;
    }

    void IwHttpLoader::setNetworkErrorResponse()
    {
        _urlResponse.setStatusCode(HTTP_CUSTOM);
        _urlResponse.setReasonPhrase("Operation timed out");
    }

    int32_t IwHttpLoader::statusCallback(void *systemData, void *userData)
    {
        //If the operation is in progress or has succeeded, S3E_RESULT_SUCCESS is returned.Otherwise S3E_RESULT_ERROR is returned.
        IwHttpLoader * loader = reinterpret_cast<IwHttpLoader*>(userData);
        if (loader == NULL || loader->_iwhttp == NULL)
        {
            return 0;
        }

        s3eResult status = loader->_iwhttp->GetStatus();
        if (loader->_loggingEnabled)
        {
            std::cout << "#BCC loader status callback: " << status << std::endl;
        }

        if (status == S3E_RESULT_ERROR)
        {
            loader->setNetworkErrorResponse();
            loader->_state = StatusCompleteFailed;
        }
        else if (status == S3E_RESULT_SUCCESS)
        {
            loader->_iwhttp->ReadDataAsync(
                loader->_readBuffer,
                (uint32) sizeof(_readBuffer) - 1,
                loader->_timeoutMillis,
                readCallback,
                loader);
            loader->_state = StatusHttpReadingResponse;
        }

        return 0;
    }

    int32_t IwHttpLoader::readCallback(void *systemData, void *userData)
    {
        IwHttpLoader * loader = reinterpret_cast<IwHttpLoader*>(userData);
        if (loader == NULL)
        {
            return 0;
        }

        int32_t bytesRead = (int32_t)(intptr_t)systemData;
        if (loader->_loggingEnabled)
        {
            std::cout << "#BCC loader received " << bytesRead << " in read callback" << std::endl;
        }

        if (bytesRead == 0)
        {
            // we hit the timeout, ditch the request
            loader->setNetworkErrorResponse();
            loader->close();
        }

        if (bytesRead > 0 && loader->_iwhttp)
        {
            loader->_readBuffer[bytesRead] = '\0';
            loader->_urlResponse.addData(loader->_readBuffer);

            if (!loader->_iwhttp->ContentFinished())
            {
                loader->_iwhttp->ReadDataAsync(loader->_readBuffer, sizeof(loader->_readBuffer) - 1, loader->_timeoutMillis, readCallback, loader);
            }
        }

        return bytesRead;
    }
}

#endif //!__ANDROID__
