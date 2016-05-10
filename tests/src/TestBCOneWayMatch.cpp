#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCOneWayMatch.h"

using namespace BrainCloud;

TEST_F(TestBCOneWayMatch, StartMatch)
{
    StartMatch();
    CancelMatch();
}

TEST_F(TestBCOneWayMatch, CancelMatch)
{
    StartMatch();
    CancelMatch();
}

TEST_F(TestBCOneWayMatch, CompleteMatch)
{
    StartMatch();
    TestResult tr;
    m_bc->getOneWayMatchService()->completeMatch(m_streamId.c_str(), &tr);
    tr.run(m_bc);
}

void TestBCOneWayMatch::StartMatch()
{
    TestResult tr;
    m_bc->getOneWayMatchService()->startMatch(GetUser(UserB)->m_profileId, 100, &tr);
    tr.run(m_bc);
    tr.reset();
    
    m_bc->getPlaybackStreamService()->getStreamSummariesForTargetPlayer(GetUser(UserB)->m_profileId, &tr);
    tr.run(m_bc);
    
    Json::Value streams = tr.m_response["data"]["streams"];
    
    m_streamId = streams[0u]["playbackStreamId"].asString();
}

void TestBCOneWayMatch::CancelMatch()
{
    TestResult tr;
    m_bc->getOneWayMatchService()->cancelMatch(m_streamId.c_str(), &tr);
    tr.run(m_bc);
}