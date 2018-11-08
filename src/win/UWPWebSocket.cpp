#include "braincloud/internal/win/UWPWebSocket.h"

namespace BrainCloud
{
    IWebSocket* IWebSocket::create(const std::string& address, int port, const std::map<std::string, std::string>& headers)
    {
        return new UWPWebSocket(address, port, headers);
    }

    UWPWebSocket::UWPWebSocket(const std::string& address, int port, const std::map<std::string, std::string>& headers)
    {
    }

    UWPWebSocket::~UWPWebSocket()
    {
    }

    bool UWPWebSocket::isValid()
    {
        return false;
    }

    void UWPWebSocket::send(const std::string& message)
    {
    }

    std::string UWPWebSocket::recv()
    {
        return "";
    }

    void UWPWebSocket::close()
    {
    }
};
