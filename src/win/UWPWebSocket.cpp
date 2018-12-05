#include "braincloud/internal/win/UWPWebSocket.h"

#include <locale>
#include <codecvt>
#include <string>
#include <iostream>

static Platform::String^ stringToPlatformString(const std::string &inputString)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring intermediateForm = converter.from_bytes(inputString);
    Platform::String^ retVal = ref new Platform::String(intermediateForm.c_str());

    return retVal;
}

static std::string platformStringToString(Platform::String^ inputString)
{
    std::wstring wString = inputString->Data();
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string retVal = converter.to_bytes(wString);

    return retVal;
}

namespace BrainCloud
{
    CXWebSocketListener::CXWebSocketListener(UWPWebSocket *pUWPWebSocket)
        : m_pUWPWebSocket(pUWPWebSocket)
    {
    }

    void CXWebSocketListener::MessageReceived(Windows::Networking::Sockets::MessageWebSocket^ pSocket, Windows::Networking::Sockets::MessageWebSocketMessageReceivedEventArgs^ pArgs)
    {
        std::string message;

        auto messageType = pArgs->MessageType;
        auto pDataReader = pArgs->GetDataReader();
        auto len = pDataReader->UnconsumedBufferLength;
        auto messageCX = pDataReader->ReadString(len);
        message = platformStringToString(messageCX);

        m_pUWPWebSocket->onMessage(message);
    }

    void CXWebSocketListener::OnClosed(Windows::Networking::Sockets::IWebSocket^ pSocket, Windows::Networking::Sockets::WebSocketClosedEventArgs^ pArgs)
    {
        m_pUWPWebSocket->close();
    }

    IWebSocket* IWebSocket::create(const std::string& address, int port, const std::map<std::string, std::string>& headers)
    {
        return new UWPWebSocket(address, port, headers);
    }

    UWPWebSocket::UWPWebSocket(const std::string& address, int port, const std::map<std::string, std::string>& headers)
    {
        m_isConnecting = true;
        m_connected = false;
        m_pConnectingTask = nullptr;

        auto addrStr = address;
        auto pos = std::min<size_t>(address.size(), address.find_first_of('?'));
        auto portStr = ":" + std::to_string(port);
        addrStr.insert(pos, portStr);

        auto uri = ref new Windows::Foundation::Uri(stringToPlatformString(addrStr));

        {
            std::unique_lock<std::mutex> lock(m_mutex);

            m_pCXWebSocketListener = ref new CXWebSocketListener(this);

            m_pMessageWebSocket = ref new Windows::Networking::Sockets::MessageWebSocket();

            // Callbacks
            m_pMessageWebSocket->MessageReceived +=
                ref new Windows::Foundation::TypedEventHandler<
                Windows::Networking::Sockets::MessageWebSocket^,
                Windows::Networking::Sockets::MessageWebSocketMessageReceivedEventArgs^
                >(m_pCXWebSocketListener, &CXWebSocketListener::MessageReceived);
            m_pMessageWebSocket->Closed +=
                ref new Windows::Foundation::TypedEventHandler<
                Windows::Networking::Sockets::IWebSocket^,
                Windows::Networking::Sockets::WebSocketClosedEventArgs^
                >(m_pCXWebSocketListener, &CXWebSocketListener::OnClosed);

            // Set headers
            for (const auto &kv : headers)
            {
                const auto &key = kv.first;
                const auto &val = kv.second;
                m_pMessageWebSocket->SetRequestHeader(stringToPlatformString(key), stringToPlatformString(val));
            }
        }

        // lol
        m_pConnectingTask = new concurrency::task<void>(m_pMessageWebSocket->ConnectAsync(uri));
        m_pConnectingTask->then([this](concurrency::task<void> prevTask)
        {
            try
            {
                prevTask.get();

                std::unique_lock<std::mutex> lock(m_mutex);
                if (m_pConnectingTask)
                {
                    m_connected = true;
                    m_isConnecting = false;
                    m_connectCond.notify_all();
                    std::cout << "Websocket connected" << std::endl;
                    delete m_pConnectingTask;
                    m_pConnectingTask = nullptr;
                }
            }
            catch (...)
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                if (m_pConnectingTask)
                {
                    m_connected = false;
                    m_isConnecting = false;
                    m_connectCond.notify_all();
                    std::cout << "Websocket failed to connect" << std::endl;
                    m_pMessageWebSocket = nullptr;
                    delete m_pConnectingTask;
                    m_pConnectingTask = nullptr;
                }
            }
        });
    }

    UWPWebSocket::~UWPWebSocket()
    {
        close();
    }

    bool UWPWebSocket::isValid()
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        if (m_isConnecting)
        {
            m_connectCond.wait(lock, [this]() { return !m_isConnecting; });
        }

        return m_connected;
    }

    void UWPWebSocket::send(const std::string& message)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_pMessageWebSocket)
        {
            Windows::Storage::Streams::DataWriter^ dataWriter = ref new Windows::Storage::Streams::DataWriter(m_pMessageWebSocket->OutputStream);
            dataWriter->WriteString(stringToPlatformString(message));
            dataWriter->StoreAsync();
            dataWriter->DetachStream();
        }
    }

    void UWPWebSocket::onMessage(const std::string& message)
    {
        std::unique_lock<std::mutex> lock(m_recvMutex);
        m_recvQueue.push(message);
        m_recvCond.notify_all();
    }

    std::string UWPWebSocket::recv()
    {
        std::unique_lock<std::mutex> lock(m_recvMutex);

        if (!m_recvQueue.empty())
        {
            std::string message = m_recvQueue.front();
            m_recvQueue.pop();
            return message;
        }

        m_recvCond.wait(lock, [this]()
        {
            return !m_connected || !m_recvQueue.empty();
        });

        if (m_connected && !m_recvQueue.empty())
        {
            std::string message = m_recvQueue.front();
            m_recvQueue.pop();
            return message;
        }

        return "";
    }

    void UWPWebSocket::close()
    {
        // Delete connecting task
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_pConnectingTask)
            {
                delete m_pConnectingTask;
            }
        }

        // Stop and clean recving
        {
            std::unique_lock<std::mutex> lock(m_recvMutex);
            while (!m_recvQueue.empty()) m_recvQueue.pop();
            m_connected = false;
            m_recvCond.notify_all();
        }

        // Destroy the socket
        {
            if (m_pMessageWebSocket)
            {
                m_pMessageWebSocket->Close(1000, L"Closed by client");
                m_pMessageWebSocket = nullptr;
            }
        }
    }
};
