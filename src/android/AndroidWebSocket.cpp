#include "braincloud/internal/android/AndroidWebSocket.h"

namespace BrainCloud
{
    IWebSocket* IWebSocket::create(const std::string& address, int port, const std::map<std::string, std::string>& headers)
    {
        return new AndroidWebSocket(address, port, headers);
    }

    AndroidWebSocket::AndroidWebSocket(const std::string& address, int port, const std::map<std::string, std::string>& headers)
    {
    }

    AndroidWebSocket::~AndroidWebSocket()
    {
    }

    bool AndroidWebSocket::isValid()
    {
        return false;
    }

    void AndroidWebSocket::send(const std::string& message)
    {
    }

    std::string AndroidWebSocket::recv()
    {
        return "";
    }

    void AndroidWebSocket::close()
    {
    }
};
