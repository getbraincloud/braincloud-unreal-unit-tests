//
//  BrainCloudComms.h
//  BrainCloudLib
//


#ifndef _BRAINCLOUDMANAGER_H_
#define _BRAINCLOUDMANAGER_H_

#include <string>
#include <vector>
#include <list>
#include <queue>

#include "json/json.h"
#include "Timer.h"
#include "IBrainCloudComms.h"
#include "TimerCallback.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "BrainCloudClient.h"

#include "HTTP/URLLoader.h"
#include "HTTP/URLRequest.h"
#include "HTTP/URLResponse.h"

namespace BrainCloud
{
	class BrainCloudComms :
        virtual public IBrainCloudComms,
        virtual public TimerCallback,
        virtual public URLLoaderClient
    {
        
	public:
		BrainCloudComms( );
		virtual ~BrainCloudComms( );

        // from IBrainCloudComms
		virtual void initialize(const char * serverURL, const char * gameId, const char * secretKey);
		
		virtual void addToQueue( ServerCall * );
        
		virtual void heartbeat( );
		virtual void resetCommunication();
		virtual void runCallbacks();
        virtual void registerEventCallback(IEventCallback *in_eventCallback);
        virtual void deregisterEventCallback();
        virtual void registerFileUploadCallback(IFileUploadCallback *in_fileUploadCallback);
        virtual void deregisterFileUploadCallback();
        virtual void registerRewardCallback(IRewardCallback *in_rewardCallback);
        virtual void deregisterRewardCallback();
        
        virtual void cancelUpload(const char * in_fileUploadId);
        virtual double getUploadProgress(const char * in_fileUploadId);
        virtual int64_t getUploadTotalBytesToTransfer(const char * in_fileUploadId);
        virtual int64_t getUploadBytesTransferred(const char * in_fileUploadId);

        // from URLLoaderClient
		virtual void handleResult( URLResponse const & );
		virtual void cacheResult( URLResponse const & );

        // from TimerCallback
		virtual void handleAlarm( Timer * );
        
    protected:
        virtual void startFileUpload(const Json::Value & in_jsonPrepareUploadResponse);
        
	private:
		Timer * _heartbeatTimer;
		URLLoader * _loader;
		URLRequest  * _request;
		Timer * _retryTimer;
        
		std::vector<ServerCall*> _queue;
		std::queue<BrainCloudCallbackEvent *>  _apiCallbackQueue;
        std::list<std::string> _eventCallbackQueue;
        std::list<std::string> _rewardCallbackQueue;
		std::list<URLResponse> _responses;
		std::vector<ServerCall*> _inProgress;
        
		pthread_mutex_t _loaderMutex;
		pthread_mutex_t _queueMutex;
		pthread_mutex_t _mutex;

        void handleResponseBundle(Json::Value & root);
		void handleError( URLResponse const & );
		void processEvents( Json::Value *, bool = true );
        bool shouldRetryPacket();
        long getRetryTimeoutMillis(int retry);
        int getMaxSendAttempts();
        
		void resend();
		bool startLoader();
		bool cleanQueueHead();
        
        void resetErrorCache();
        void handleNoAuth();
	};

};

#endif
