#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCPlaybackStream.h"

using namespace BrainCloud;


TEST_F(TestBCPlaybackStream, StartStream)
{
    StartStream();
    EndStream();
}

TEST_F(TestBCPlaybackStream, EndSream)
{
    StartStream();
    EndStream();
}

TEST_F(TestBCPlaybackStream, DeleteStream)
{
    StartStream();
    TestResult tr;
    m_bc->getPlaybackStreamService()->deleteStream(m_streamId.c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlaybackStream, AddEvent)
{
    StartStream();
    TestResult tr;
    Json::FastWriter fw;
    Json::Value testData;
    testData["testKey"] = "testValue";
    m_bc->getPlaybackStreamService()->addEvent(m_streamId.c_str(), fw.write(testData).c_str(), fw.write(testData).c_str(), &tr);
    EndStream();
}

TEST_F(TestBCPlaybackStream, GetStreamSummariesForTargetPlayer)
{
    StartStream();
    TestResult tr;
    m_bc->getPlaybackStreamService()->getStreamSummariesForTargetPlayer(GetUser(UserB)->m_profileId, &tr);
    tr.run(m_bc);
    EndStream();
}

TEST_F(TestBCPlaybackStream, GetStreamSummariesForInitiatingPlayer)
{
    StartStream();
    TestResult tr;
    m_bc->getPlaybackStreamService()->getStreamSummariesForInitiatingPlayer(GetUser(UserA)->m_profileId, &tr);
    tr.run(m_bc);
    EndStream();
}

TEST_F(TestBCPlaybackStream, GetRecentStreamsForTargetPlayer)
{
    StartStream();
    TestResult tr;
    int maxNumStreams = 10;
    m_bc->getPlaybackStreamService()->getRecentStreamsForTargetPlayer(GetUser(UserB)->m_profileId, maxNumStreams, &tr);
    tr.run(m_bc);
    EndStream();
}

TEST_F(TestBCPlaybackStream, GetRecentStreamsForInitiatingPlayer)
{
    StartStream();
    TestResult tr;
    int maxNumStreams = 10;
    m_bc->getPlaybackStreamService()->getRecentStreamsForInitiatingPlayer(GetUser(UserA)->m_profileId, maxNumStreams, &tr);
    tr.run(m_bc);
    EndStream();
}

TEST_F(TestBCPlaybackStream, ReadStream)
{
    StartStream();
    TestResult tr;
    m_bc->getPlaybackStreamService()->readStream(m_streamId.c_str(), &tr);
    tr.run(m_bc);
    EndStream();
}

void TestBCPlaybackStream::StartStream()
{
    TestResult tr;
    m_bc->getPlaybackStreamService()->startStream(GetUser(UserB)->m_profileId, true, &tr);
    tr.run(m_bc);
    tr.reset();
    
    m_bc->getPlaybackStreamService()->getStreamSummariesForTargetPlayer(GetUser(UserB)->m_profileId, &tr);
    tr.run(m_bc);
    
    Json::Value streams = tr.m_response["data"]["streams"];
    m_streamId = streams[0u]["playbackStreamId"].asString();
}

void TestBCPlaybackStream::EndStream()
{
    TestResult tr;
    m_bc->getPlaybackStreamService()->endStream(m_streamId.c_str(), &tr);
    tr.run(m_bc);
}