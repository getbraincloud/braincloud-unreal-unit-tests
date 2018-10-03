#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCProduct.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"


using namespace BrainCloud;


TEST_F(TestBCProduct, GetCurrency)
{
    TestResult tr;
    m_bc->getProductService()->getCurrency(m_currencyType, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCProduct, GetEligiblePromotions)
{
    TestResult tr;
    m_bc->getProductService()->getEligiblePromotions(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCProduct, GetSalesInventory)
{
    TestResult tr;
    m_bc->getProductService()->getSalesInventory(m_platform, m_currencyType, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCProduct, GetSalesInventoryByCategory)
{
    TestResult tr;
    m_bc->getProductService()->getSalesInventoryByCategory(m_platform, m_currencyType, m_productCategory, &tr);
    tr.run(m_bc);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
TEST_F(TestBCProduct, AwardCurrency)
{
    TestResult tr;
    m_bc->getProductService()->awardCurrency(m_currencyType, 1000, &tr);
    tr.run(m_bc);
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
TEST_F(TestBCProduct, ConsumeCurrency)
{
    TestResult tr;
    m_bc->getProductService()->consumeCurrency(m_currencyType, 1000, &tr);
    tr.run(m_bc);
}
#pragma clang diagnostic pop
 
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
TEST_F(TestBCProduct, ResetCurrency)
{
    TestResult tr;
    m_bc->getProductService()->resetCurrency(&tr);
    tr.run(m_bc);
}
#pragma clang diagnostic pop