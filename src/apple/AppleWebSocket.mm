#if (TARGET_OS_WATCH != 1)

#include "braincloud/internal/apple/AppleWebSocket.h"

#include <algorithm>

@interface WebSocket() <SRWebSocketDelegate>
{
    SRWebSocket* _webSocket;
    BrainCloud::IRocketSocketCallback* _callback;
}
@end

@implementation WebSocket

-(void)dealloc
{
}

- (id)initWithAddress:(const std::string&)address
                 port:(int)port
              headers:(const std::map<std::string, std::string>&)headers
             callback:(BrainCloud::IRocketSocketCallback*)callback
{
    _callback = callback;

    NSString* url = [NSString stringWithUTF8String:address.c_str()];
    auto pos = address.find_first_of(':', 6);
    if (pos == std::string::npos)
    {
        pos = std::min<size_t>(address.size(), address.find_first_of('?'));
        url = [NSString stringWithFormat:@"%s:%i%s", address.substr(0, pos).c_str(), port, address.substr(pos).c_str()];
    }
    
    _webSocket = [[SRWebSocket alloc] initWithURL:[NSURL URLWithString:url]];
    _webSocket.delegate = self;
    
    [_webSocket open];
    
    return [super init];
}

- (void)send:(const std::string&)message
{
    [_webSocket send:[NSString stringWithUTF8String:message.c_str()]];
}

- (void)close
{
    if (_webSocket)
    {
        [_webSocket close];
        _webSocket = nil;
    }
}

///--------------------------------------
#pragma mark - SRWebSocketDelegate
///--------------------------------------

- (void)webSocketDidOpen:(SRWebSocket *)webSocket
{
    NSLog(@"Websocket Connected");
    _callback->onOpen();
}

- (void)webSocket:(SRWebSocket *)webSocket didFailWithError:(NSError *)error
{
    NSLog(@":( Websocket Failed With Error %@", error);
    _webSocket = nil;
    _callback->onError();
}

- (void)webSocket:(SRWebSocket *)webSocket didReceiveMessageWithString:(nonnull NSString *)string
{
    NSLog(@"didReceiveMessageWithString \"%@\"", string);
    _callback->onMessage([string UTF8String]);
}

- (void)webSocket:(SRWebSocket *)webSocket didCloseWithCode:(NSInteger)code reason:(NSString *)reason wasClean:(BOOL)wasClean
{
    NSLog(@"WebSocket closed");
    _webSocket = nil;
    _callback->onClose();
}

- (void)webSocket:(SRWebSocket *)webSocket didReceivePong:(NSData *)pongPayload
{
    NSLog(@"WebSocket received pong");
}

- (void)webSocket:(SRWebSocket *)webSocket didReceiveMessage:(id)message
{
    if ([message isKindOfClass:[NSString class]])
    {
        NSLog(@"didReceiveMessage as String: %@", (NSString*)message);
        _callback->onMessage([(NSString*)message UTF8String]);
    }
    else if ([message isKindOfClass:[NSData class]])
    {
        NSData* data = (NSData*)message;
        std::string messageStr((char*)data.bytes, (size_t)data.length);
        NSLog(@"didReceiveMessage as Data: %s", messageStr.c_str());
        _callback->onMessage(messageStr);
    }
}

@end

namespace BrainCloud
{
    IWebSocket* IWebSocket::create(const std::string& address, int port, const std::map<std::string, std::string>& headers)
    {
        return new AppleWebSocket(address, port, headers);
    }

    AppleWebSocket::AppleWebSocket(const std::string& address, int port, const std::map<std::string, std::string>& headers)
        : _isValid(false)
        , _isConnecting(true)
        , _authHeaders(headers)
        , _webSocket(NULL)
    {
        _webSocket = [[WebSocket alloc] initWithAddress:address port:port headers:headers callback:this];
    }

    AppleWebSocket::~AppleWebSocket()
    {
        close();
    }

    bool AppleWebSocket::isValid()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        
        if (_isConnecting)
        {
            _connectionCondition.wait(lock, [this]() { return !_isConnecting; });
        }
        
        return _isValid;
    }

    void AppleWebSocket::send(const std::string& message)
    {
        if (_webSocket)
        {
            [_webSocket send:message];
        }
    }

    std::string AppleWebSocket::recv()
    {
        std::unique_lock<std::mutex> lock(_recvMutex);

        if (!_recvQueue.empty())
        {
            std::string message = _recvQueue.front();
            _recvQueue.pop();
            return message;
        }

        _recvCondition.wait(lock, [this]()
        {
            return !_isValid || !_recvQueue.empty();
        });

        if (_isValid && !_recvQueue.empty())
        {
            std::string message = _recvQueue.front();
            _recvQueue.pop();
            return message;
        }

        return "";
    }

    void AppleWebSocket::close()
    {
        // Invalidate
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _isValid = false;
            _isConnecting = false;
            _connectionCondition.notify_all();
        }

        // Stop and clean recving
        {
            std::unique_lock<std::mutex> lock(_recvMutex);
            while (!_recvQueue.empty()) _recvQueue.pop();
            _recvCondition.notify_all();
        }

        // Close websocket
        std::unique_lock<std::mutex> lock(_mutex);
        if (_webSocket)
        {
            [_webSocket close];
            _webSocket = nil;
        }
    }

    void AppleWebSocket::onOpen()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _isValid = true;
        _isConnecting = false;
        _connectionCondition.notify_all();
    }

    void AppleWebSocket::onClose()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _isValid = false;
        _isConnecting = false;
        _connectionCondition.notify_all();
        _webSocket = nil; // This is now invalid
    }

    void AppleWebSocket::onError()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _isValid = false;
        _isConnecting = false;
        _connectionCondition.notify_all();
        _webSocket = nil; // This is now invalid
    }

    void AppleWebSocket::onMessage(const std::string& message)
    {
        std::unique_lock<std::mutex> lock(_recvMutex);
        _recvQueue.push(message);
        _recvCondition.notify_all();
    }
};

#endif