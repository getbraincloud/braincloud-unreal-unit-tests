#include <stdlib.h>
#include "TestBCRTTComms.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"
#include "braincloud/IRTTCallback.h"

#include <chrono>
#include <thread>
#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "TestResult.h"
#include "TestBCRelayComms.h"

#include <functional>

using namespace BrainCloud;
using namespace std;
using namespace std::chrono;

class LobbyCallback final : public IRTTCallback
{
public:
    LobbyCallback(const function<void(const Json::Value&)>& in_callback)
        : callback(in_callback)
    {}

private:
    void rttCallback(const string& jsonData) override
    {
        Json::Value json;
        Json::Reader reader;
        reader.parse(jsonData, json);
        callback(json);
    }

    function<void(const Json::Value&)> callback;
};

class RelayConnectCallback final : public IRelayConnectCallback
{
public:
    RelayConnectCallback(const function<void()>& in_callback,
                         const function<void()>& in_failCallback)
        : callback(in_callback)
        , failCallback(in_failCallback)
    {}

private:
    void relayConnectSuccess(const std::string& jsonResponse) override
    {
        callback();
    }

    void relayConnectFailure(const std::string& errorMessage) override
    {
        failCallback();
    }

    function<void()> callback;
    function<void()> failCallback;
};

class RelaySystemCallback final : public IRelaySystemCallback
{
public:
RelaySystemCallback(const function<void(const Json::Value&)>& in_callback)
    : callback(in_callback)
{}

private:
    void relaySystemCallback(const std::string& jsonResponse) override
    {
        Json::Value json;
        Json::Reader reader;
        reader.parse(jsonResponse, json);
        callback(json);
    }

    function<void(const Json::Value&)> callback;
};

class RelayCallback final : public IRelayCallback
{
public:
    RelayCallback(const function<void(int netId, const uint8_t* bytes, int size)>& in_callback)
        : callback(in_callback)
    {}

private:
    void relayCallback(int netId, const uint8_t* bytes, int size) override
    {
        callback(netId, bytes, size);
    }

    function<void(int netId, const uint8_t* bytes, int size)> callback;
};

static void relayFullFlow(BrainCloudClient* bc, eRelayConnectionType connectionType)
{
    bool isRoomReady = false;
    Json::Value connectionInfo;

    // Enable RTT
    {
        TestResult tr;
        bc->getRTTService()->enableRTT(&tr);
        tr.run(bc);
    }

    // Register lobby callback
    LobbyCallback lobbyCallback([&isRoomReady, &connectionInfo](const Json::Value& eventJson)
    {
        ASSERT_TRUE(eventJson["operation"].isString());
        auto op = eventJson["operation"].asString();
        if (op == "DISBANDED")
        {
            ASSERT_TRUE(eventJson["data"]["reason"]["code"].isInt());
            ASSERT_TRUE(eventJson["data"]["reason"]["code"].asInt() == RTT_ROOM_READY);
            isRoomReady = true;
        }
        else if (op == "ROOM_READY")
        {
            ASSERT_TRUE(eventJson["data"].isObject());
            connectionInfo = eventJson["data"];
        }
    });
    bc->getRTTService()->registerRTTLobbyCallback(&lobbyCallback);

    // Find or create lobby
    {
        TestResult tr;
        vector<std::string> otherUserCxIds;
        bc->getLobbyService()->findOrCreateLobby("READY_START", 0, 1, "{\"strategy\":\"ranged-absolute\",\"alignment\":\"center\",\"ranges\":[1000]}", "{}", otherUserCxIds, "{}", true, "{}", "all", &tr);
        tr.run(bc);
    }

    // Wait for lobby to start, or timeout 2mins
    {
        auto timeStart = steady_clock::now();
        while (!isRoomReady)
        {
            bc->runCallbacks();
            this_thread::sleep_for(milliseconds(100));
            ASSERT_TRUE(steady_clock::now() < timeStart + minutes(10));
        }
        auto time = steady_clock::now() - timeStart;
        printf("\nTook: %i:%.02i\n", (int)duration_cast<minutes>(time).count(), (int)duration_cast<seconds>(time).count() % 60);
    }

    // Register relay callback
    bool relayFailed = false;
    auto pData = "Hello World!";
    int size = (int)strlen(pData);
    RelayConnectCallback relayConnectCallback([bc, pData, size]()
    {
        auto netId = bc->getRelayService()->getNetIdForProfileId(bc->getAuthenticationService()->getProfileId());
        bc->getRelayService()->send((uint8_t*)pData, size, netId, true, true, eRelayChannel::HighPriority1);
    },
                                              [&relayFailed]()
    {
        relayFailed = true;
    });
    bool hasReceivedSystemMessage = false;
    RelaySystemCallback relaySystemCallback([&hasReceivedSystemMessage](const Json::Value& eventJson)
    {
        if (eventJson["op"].asString() == "CONNECT")
        {
            hasReceivedSystemMessage = true;
        }
    });
    bool hasReceivedEcho = false;
    RelayCallback relayCallback([&hasReceivedEcho, pData, size](int netId, const uint8_t* bytes, int in_size)
    {
        if (memcmp(pData, bytes, size) == 0)
        {
            hasReceivedEcho = true;
        }
    });
    bc->getRelayService()->registerSystemCallback(&relaySystemCallback);
    bc->getRelayService()->registerRelayCallback(&relayCallback);

    // Relay connect
    {
        auto host = connectionInfo["connectData"]["address"].asString();
        int port = 0;
        switch (connectionType)
        {
            case eRelayConnectionType::TCP: port = connectionInfo["connectData"]["ports"]["tcp"].asInt(); break;
            case eRelayConnectionType::UDP: port = connectionInfo["connectData"]["ports"]["udp"].asInt(); break;
            case eRelayConnectionType::WSS:
            case eRelayConnectionType::WS: port = connectionInfo["connectData"]["ports"]["ws"].asInt(); break;
        }
        auto passcode = connectionInfo["passcode"].asString();
        auto lobbyId = connectionInfo["lobbyId"].asString();
        bc->getRelayService()->connect(connectionType, host, port, passcode, lobbyId, &relayConnectCallback);
    }

    // Wait for 30sec. Enough so connect/echo the message and then see if ping keeps us alive
    {
        auto timeStart = steady_clock::now();
        while (steady_clock::now() < timeStart + seconds(30) && !relayFailed)
        {
            bc->runCallbacks();
            this_thread::sleep_for(milliseconds(100));
        }
        ASSERT_TRUE(bc->getRelayService()->isConnected());
        ASSERT_TRUE(hasReceivedSystemMessage);
        ASSERT_TRUE(hasReceivedEcho);
    }
}

TEST_F(TestBCRelayComms, FullFlowTCP)
{
    relayFullFlow(m_bc, eRelayConnectionType::TCP);
}

TEST_F(TestBCRelayComms, FullFlowUDP)
{
    relayFullFlow(m_bc, eRelayConnectionType::UDP);
}

//TEST_F(TestBCRelayComms, FullFlowWS)
//{
//    relayFullFlow(m_bc, eRelayConnectionType::WS);
//}
//
//TEST_F(TestBCRelayComms, FullFlowWSS)
//{
//    relayFullFlow(m_bc, eRelayConnectionType::WSS);
//}
