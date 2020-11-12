#include <stdlib.h>
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"


#if __cplusplus < 201103L

#ifdef WIN32
#include <WinBase.h>
#else
#include <unistd.h>
#endif

#else
#include <chrono>
#include <thread>
#endif

#define MAX_WAIT_SECS 60

TestResult::TestResult()
{
    m_maxWaitMillis = 0;
    reset();
}


void TestResult::reset()
{
    m_done = false;
    m_result = false;
    m_apiCountExpected = 0;

    m_response = Json::Value();

    m_statusCode = 0;
    m_reasonCode = 0;
    m_statusMessage.clear();

    m_networkErrorCount = 0;
    m_globalErrorCount = 0;
}

void TestResult::sleep(int millis)
{
#if __cplusplus >= 201103L
    auto sleep = std::chrono::milliseconds(millis);
    std::this_thread::sleep_for(sleep);
#else
#ifdef WIN32
    Sleep(millis);
#else
    usleep(millis * 1000);
#endif
#endif
}

void TestResult::sleepAndUpdate(BrainCloudClient * in_bc)
{
    long maxWaitMs = m_maxWaitMillis > 0 ? m_maxWaitMillis : MAX_WAIT_SECS * 1000;
    long sleepSliceMs = 50;
    while (!m_done && maxWaitMs > 0)
    {
        in_bc->runCallbacks();
        sleep(sleepSliceMs);
        maxWaitMs -= sleepSliceMs;
    }
}

bool TestResult::run(BrainCloudClient * in_bc, bool in_noAssert)
{
    return runExpectCount(in_bc, 1, in_noAssert);
}

bool TestResult::runExpectCount(BrainCloudClient * in_bc, int in_apiCountExpected, bool in_noAssert)
{
    reset(); //reset before run
    m_apiCountExpected = in_apiCountExpected;
    sleepAndUpdate(in_bc);

    if (!m_done)
    {
        // we timed out so try to reset the comms and throw the error
        if (!in_noAssert) EXPECT_TRUE(m_done);
        in_bc->resetCommunication();
        m_result = false;
        m_statusCode = 999;
        m_reasonCode = 999;
        m_statusMessage = "TEST TIMEOUT EXCEEDED";
    }
    else
    {
        if (!in_noAssert) EXPECT_TRUE(m_result);
        if (!m_result)
        {
            if (!in_noAssert) EXPECT_EQ(200, m_statusCode);
            if (!in_noAssert) EXPECT_EQ(0, m_reasonCode);
            if (!in_noAssert) EXPECT_EQ("", m_statusMessage);
        }
    }

    return m_result;
}


bool TestResult::runExpectFail(BrainCloudClient * in_bc, int expectedStatus, int expectedReasonCode)
{
    reset(); //reset before run
    sleepAndUpdate(in_bc);

    if (!m_done)
    {
        // bc lib should have sent a timeout
        EXPECT_TRUE(m_done);
        return false;
    }
    bool ret = true;
    EXPECT_FALSE(m_result);
    if (expectedStatus != -1)
    {
        EXPECT_EQ(expectedStatus, m_statusCode);
        if (m_statusCode != expectedStatus)
        {
            ret = false;
        }
    }
    if (expectedReasonCode != -1)
    {
        EXPECT_EQ(expectedReasonCode, m_reasonCode);
        if (m_reasonCode != expectedReasonCode)
        {
            ret = false;
        }
    }
    if (!ret)
    {
        // to log the status message
        EXPECT_EQ("", m_statusMessage);
    }

    return ret;
}

void TestResult::rttConnectSuccess()
{
    m_response.clear();
    m_result = true;
    --m_apiCountExpected;
    if (m_apiCountExpected <= 0)
    {
        m_done = true;
    }
}

void TestResult::rttConnectFailure(const std::string& errorMessage)
{
    m_statusMessage = errorMessage;

    m_result = false;
    --m_apiCountExpected;
    if (m_apiCountExpected <= 0)
    {
        m_done = true;
    }
}

void TestResult::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const & jsonData)
{
    Json::Value value;
    Json::Reader reader;
    m_response.clear();
    reader.parse(jsonData, m_response);

    m_result = true;
    --m_apiCountExpected;
    if (m_apiCountExpected <= 0)
    {
        m_done = true;
    }
}

void TestResult::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, const std::string & statusMessage)
{
    m_statusCode = statusCode;
    m_reasonCode = reasonCode;
    m_statusMessage = statusMessage;

    m_result = false;
    --m_apiCountExpected;
    if (m_apiCountExpected <= 0)
    {
        m_done = true;
    }
}

void TestResult::globalError(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, const std::string & jsonError)
{
    m_statusCode = statusCode;
    m_reasonCode = reasonCode;
    m_statusMessage = jsonError;

    m_result = false;
    --m_apiCountExpected;
    if (m_apiCountExpected <= 0)
    {
        m_done = true;
    }
    ++m_globalErrorCount;
}

void TestResult::networkError()
{
    m_statusCode = HTTP_CLIENT_NETWORK_ERROR;
    m_reasonCode = CLIENT_NETWORK_ERROR_TIMEOUT;
    m_statusMessage = "Network Error";

    m_result = false;
    --m_apiCountExpected;
    if (m_apiCountExpected <= 0)
    {
        m_done = true;
    }
    ++m_networkErrorCount;
}

void TestResult::setMaxWaitSecs(int secs)
{
    m_maxWaitMillis = secs * 1000;
}
