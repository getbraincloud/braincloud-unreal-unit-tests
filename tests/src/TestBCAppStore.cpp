#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCAppStore.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"

using namespace BrainCloud;

TEST_F(TestBCAppStore, VerifyPurchase)
{
    TestResult tr;
    m_bc->getAppStoreService()->verifyPurchase("_invalid_store_id_", "{}", &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INVALID_STORE_ID);
}

TEST_F(TestBCAppStore, GetEligiblePromotions)
{
    TestResult tr;
    m_bc->getAppStoreService()->getEligiblePromotions(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCAppStore, GetSalesInventory)
{
    TestResult tr;
    m_bc->getAppStoreService()->getSalesInventory("_invalid_store_id_", "_invalid_user_currency_", &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INVALID_STORE_ID);
}

TEST_F(TestBCAppStore, GetSalesInventoryByCategory)
{
    TestResult tr;
    m_bc->getAppStoreService()->getSalesInventoryByCategory("_invalid_store_id_", "_invalid_user_currency_", "_invalid_category_", &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INVALID_STORE_ID);
}

TEST_F(TestBCAppStore, StartPurchase)
{
    TestResult tr;
    m_bc->getAppStoreService()->startPurchase("_invalid_store_id_", "{}", &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INVALID_STORE_ID);
}

TEST_F(TestBCAppStore, FinalizePurchase)
{
    TestResult tr;
    m_bc->getAppStoreService()->finalizePurchase("_invalid_store_id_", "_invalid_transaction_id_", "{}", &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INVALID_STORE_ID);
}
