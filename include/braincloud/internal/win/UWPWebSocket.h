#ifndef _UWPWEBSOCKER_H_
#define _UWPWEBSOCKER_H_

#include "braincloud/internal/IWebSocket.h"

#include <Windows.h>
#include <ppltasks.h>

#include <atomic>
#include <condition_variable>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

namespace BrainCloud
{
    class UWPWebSocket;

    public ref class CXWebSocketListener sealed
    {
    private:
        friend class UWPWebSocket;

        CXWebSocketListener(UWPWebSocket *pUWPWebSocket); // Can't make this public because CX doesn't like native

        void MessageReceived(Windows::Networking::Sockets::MessageWebSocket^, Windows::Networking::Sockets::MessageWebSocketMessageReceivedEventArgs^);
        void OnClosed(Windows::Networking::Sockets::IWebSocket^, Windows::Networking::Sockets::WebSocketClosedEventArgs^);

        UWPWebSocket *m_pUWPWebSocket;
    };

    class UWPWebSocket : public IWebSocket
    {
    public:
        virtual ~UWPWebSocket();

        virtual bool isValid();

        virtual void send(const std::string& message);
        virtual std::string recv();

        virtual void close();

    protected:
        friend class IWebSocket;

        UWPWebSocket(const std::string& address, int port, const std::map<std::string, std::string>& headers);

    private:
        friend ref class CXWebSocketListener;

        void onMessage(const std::string& message);

        CXWebSocketListener^ m_pCXWebSocketListener;
        Windows::Networking::Sockets::MessageWebSocket^ m_pMessageWebSocket;
        Windows::Storage::Streams::DataWriter^ m_pMessageWriter;
        concurrency::task<void> *m_pConnectingTask;

        bool m_isConnecting;
        bool m_connected;
        std::mutex m_mutex;
        std::condition_variable m_connectCond;
        std::mutex m_recvMutex;
        std::condition_variable m_recvCond;
        std::queue<std::string> m_recvQueue;
    };
};

#endif /* _UWPWEBSOCKER_H_ */
