#ifndef TARGET_OS_WATCH

#ifndef _APPLEWEBSOCKET_H_
#define _APPLEWEBSOCKET_H_

#include "braincloud/internal/IWebSocket.h"

#import <SocketRocket/SocketRocket.h>

#include <condition_variable>
#include <map>
#include <mutex>
#include <queue>
#include <string>

namespace BrainCloud
{
    class IRocketSocketCallback
    {
    public:
        virtual ~IRocketSocketCallback() {}

        virtual void onOpen() = 0;
        virtual void onClose() = 0;
        virtual void onError() = 0;
        virtual void onMessage(const std::string& message) = 0;
    };
};

@interface WebSocket<SRWebSocketDelegate> : NSObject
- (id)initWithAddress:(const std::string&)address
                 port:(int)port
              headers:(const std::map<std::string, std::string>&)headers
             callback:(BrainCloud::IRocketSocketCallback*)callback;
- (void)send:(const std::string&)message;
- (void)close;
@end

namespace BrainCloud
{
    class AppleWebSocket : public IWebSocket, IRocketSocketCallback
    {
    public:
        virtual ~AppleWebSocket();

        virtual bool isValid();

        virtual void send(const std::string& message);
        virtual std::string recv();

        virtual void close();

    protected:
        friend class IWebSocket;

        AppleWebSocket(const std::string& address, int port, const std::map<std::string, std::string>& headers);

    private:
        virtual void onOpen();
        virtual void onClose();
        virtual void onError();
        virtual void onMessage(const std::string& message);
        
        // State
        bool _isValid;
        bool _isConnecting;
        
        // Update and send queue
        std::mutex _mutex;
        
        // Connection
        std::condition_variable _connectionCondition;
        
        // Receiving queue
        std::mutex _recvMutex;
        std::queue<std::string> _recvQueue;
        std::condition_variable _recvCondition;
        
        // Context
        WebSocket* _webSocket;
        std::map<std::string, std::string> _authHeaders;
    };
};

#endif /* _APPLEWEBSOCKET_H_ */

#endif