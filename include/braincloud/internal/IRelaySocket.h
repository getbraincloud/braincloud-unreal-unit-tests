#ifndef _IRELAYSOCKET_H_
#define _IRELAYSOCKET_H_

#include <cinttypes>

namespace BrainCloud
{
    class IRelaySocket
    {
    public:
        virtual ~IRelaySocket() {}

        virtual bool isConnected() = 0;
        virtual bool isValid() = 0;

        virtual void updateConnection() = 0; // Call each frame when !isConnected and isValid

        virtual void send(const uint8_t* pData, int size) = 0;
        virtual const uint8_t* peek(int& size) = 0; // Returns null if nothing to read

        virtual void close() = 0;

    protected:
        IRelaySocket() {}
    };
};

#endif /* _IRELAYSOCKET_H_ */
