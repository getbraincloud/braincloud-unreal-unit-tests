#pragma once

#include "braincloud/internal/IBrainCloudComms.h"

#include <thread>
#include <deque>
#include <mutex>
#include <memory>
#include <condition_variable>

namespace BrainCloud {

    class ServerCall;
    class BrainCloudClient;

    class CppRestBrainCloudComms : virtual public IBrainCloudComms
    {
    public:
        virtual ~CppRestBrainCloudComms();
        virtual void initialize(const char * serverURL, const char * appId, const char * secretKey);
        virtual void registerEventCallback(IEventCallback * in_eventCallback);
        virtual void deregisterEventCallback();
        virtual void registerFileUploadCallback(IFileUploadCallback *in_fileUploadCallback);
        virtual void deregisterFileUploadCallback();
        virtual void registerRewardCallback(IRewardCallback * in_rewardCallback);
        virtual void deregisterRewardCallback();
        virtual void registerGlobalErrorCallback(IGlobalErrorCallback *in_globalErrorCallback);
        virtual void deregisterGlobalErrorCallback();
        virtual void registerNetworkErrorCallback(INetworkErrorCallback *in_networkErrorCallback);
        virtual void deregisterNetworkErrorCallback();

        virtual void cancelUpload(const char * in_fileUploadId);
        virtual double getUploadProgress(const char * in_fileUploadId);
        virtual int64_t getUploadTotalBytesToTransfer(const char * in_fileUploadId);
        virtual int64_t getUploadBytesTransferred(const char * in_fileUploadId);

        virtual void addToQueue(ServerCall *);

        virtual void enableNetworkErrorMessageCaching(bool in_enabled);
        virtual void retryCachedMessages();
        virtual void flushCachedMessages(bool in_sendApiErrorCallbacks);

        virtual void clearSessionId() { _sessionId.clear(); }
        virtual void sendHeartbeat();
        virtual void resetCommunication();
        virtual void shutdown();
        virtual void runCallbacks();

    protected:
        friend class IBrainCloudComms;

        CppRestBrainCloudComms(BrainCloudClient* in_client);

        virtual void startFileUpload(const Json::Value & in_jsonPrepareUploadResponse);

    private:
        void processQueue();
        void fillInProgress();
        bool processMessages();
        bool shouldRetryPacket();
        long getRetryTimeoutMillis(int retry);
        int getMaxSendAttempts();

        void resetErrorCache();
        void handleNoAuth();

        std::string getDataString();
        void reportParseError();
        void reportError(uint32_t statusCode, uint32_t reasonCode, const std::string data);
        void reportResults(Json::Value& root);
        void log(const std::string & s);

        bool _tearDownThread;

        std::thread _processQueue;
        std::mutex _queueMutex;
        std::mutex _inProgressMutex;
        std::recursive_mutex _uploaderMutex;
        std::condition_variable _waitForMessage;
        std::deque<std::shared_ptr < ServerCall > > _messageQueue;
        std::deque<std::shared_ptr < ServerCall > > _inProgressQueue;
        std::vector<ServerCall*> _inProgress;
    };
};
