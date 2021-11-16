// Copyright 2021 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <cinttypes>

namespace BrainCloud
{
    class IRelaySocket
    {
    public:
        virtual ~IRelaySocket() {}

        virtual bool isConnected() = 0;
        virtual bool isValid() = 0;

        virtual void update() = 0; // Run every frame
        virtual void updateConnection() = 0; // Call each frame when !isConnected and isValid

        virtual void send(const uint8* pData, int size) = 0;
        virtual const uint8* peek(int& size) = 0; // Returns null if nothing to read

        virtual void close() = 0;

    protected:
        IRelaySocket() {}
    };
};
