#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCVirtualCurrency.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"


using namespace BrainCloud;


TEST_F(TestBCVirtualCurrency, GetCurrency)
{
    TestResult tr;
    m_bc->getVirtualCurrencyService()->getCurrency("_valid_id_", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCVirtualCurrency, GetParentCurrency)
{
    TestResult tr;
    m_bc->getVirtualCurrencyService()->getParentCurrency("_valid_id_", "_invalid_level_", &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, MISSING_PLAYER_PARENT);
}

TEST_F(TestBCVirtualCurrency, GetPeerCurrency)
{
    TestResult tr;
    m_bc->getVirtualCurrencyService()->getPeerCurrency("_valid_id_", "_invalid_peer_code_", &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, PROFILE_PEER_NOT_FOUND);
}
