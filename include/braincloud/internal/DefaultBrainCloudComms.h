//
//  DefaultBrainCloudComms.h
//  BrainCloudLib
//

#ifndef _BRAINCLOUDMANAGER_H_
#define _BRAINCLOUDMANAGER_H_

#include <string>
#include <vector>
#include <list>
#include <queue>

#if defined(WIN32) && defined(USE_CURL)
#include <WinSock2.h>
#include <Windows.h>
#endif
#include "braincloud/internal/Mutex.h"

#include "json/json.h"
#include "braincloud/internal/IBrainCloudComms.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"

#include "braincloud/internal/URLLoader.h"
#include "braincloud/internal/URLRequest.h"
#include "braincloud/internal/URLResponse.h"

#define RETRY_TIME_NOT_RETRYING 0

namespace BrainCloud
{
    class BrainCloudClient;

    class DefaultBrainCloudComms : public IBrainCloudComms
    {
    public:
        virtual ~DefaultBrainCloudComms();

        // from IBrainCloudComms
        virtual void initialize(const char * serverURL, const char * appId, const char * secretKey);

        virtual void addToQueue( ServerCall * );

        virtual void enableNetworkErrorMessageCaching(bool in_enabled);
        virtual void retryCachedMessages();
        virtual void flushCachedMessages(bool in_sendApiErrorCallbacks);

        virtual void sendHeartbeat();
        virtual void resetCommunication();
        virtual void shutdown();
        virtual void runCallbacks();
        virtual void registerEventCallback(IEventCallback *in_eventCallback);
        virtual void deregisterEventCallback();
        virtual void registerFileUploadCallback(IFileUploadCallback *in_fileUploadCallback);
        virtual void deregisterFileUploadCallback();
        virtual void registerRewardCallback(IRewardCallback *in_rewardCallback);
        virtual void deregisterRewardCallback();
        virtual void registerGlobalErrorCallback(IGlobalErrorCallback *in_globalErrorCallback);
        virtual void deregisterGlobalErrorCallback();
        virtual void registerNetworkErrorCallback(INetworkErrorCallback * in_networkErrorCallback);
        virtual void deregisterNetworkErrorCallback();

        virtual void cancelUpload(const char * in_fileUploadId);
        virtual double getUploadProgress(const char * in_fileUploadId);
        virtual int64_t getUploadTotalBytesToTransfer(const char * in_fileUploadId);
        virtual int64_t getUploadBytesTransferred(const char * in_fileUploadId);

        // returns true if packet requires a retry
        bool handleResult( URLResponse const & );

    protected:
        friend class IBrainCloudComms;

        DefaultBrainCloudComms(BrainCloudClient* in_client);

        virtual void startFileUpload(const Json::Value & in_jsonPrepareUploadResponse);

    private:
        URLLoader * _loader;
        URLRequest  * _request;

        std::vector<ServerCall*> _queue;
        std::queue<BrainCloudCallbackEvent *>  _apiCallbackQueue;
        std::list<std::string> _eventCallbackQueue;
        std::list<std::string> _rewardCallbackQueue;
        std::list<URLResponse> _responses;
        std::vector<ServerCall*> _inProgress;

        long receivedPacketIdChecker = 0;

        RecursiveMutex _loaderMutex;
        RecursiveMutex _queueMutex;
        RecursiveMutex _mutex;

        int64_t _retryTimeMillis;

        void handleResponseBundle(Json::Value & root);
        void handleError( URLResponse const & );
        void triggerCommsError(int statusCode, int responseCode, const std::string & in_error, const std::string & in_severity);
        void processEvents( Json::Value *, bool = true );
        bool shouldRetryPacket();
        long getRetryTimeoutMillis(int retry);
        int getMaxSendAttempts();

        void resend();
        void createAndSendBundle();
        void startHttpRequest();

        void resetErrorCache();
        void fakeErrorResponse(int32_t statusCode, int32_t reasonCode, const std::string & statusMessage);

		void updateKillSwitch(const std::string & service, const std::string & operation, int32_t statusCode);
		void resetKillSwitch();
    };
};

#endif
