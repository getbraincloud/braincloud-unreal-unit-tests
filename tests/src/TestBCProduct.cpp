#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCProduct.h"

using namespace BrainCloud;


TEST_F(TestBCProduct, AwardCurrency)
{
    TestResult tr;
    m_bc->getProductService()->awardCurrency(m_currencyType, 1000, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCProduct, ConsumeCurrency)
{
    TestResult tr;
    m_bc->getProductService()->consumeCurrency(m_currencyType, 1000, &tr);
    tr.run(m_bc);
}

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

TEST_F(TestBCProduct, ResetCurrency)
{
    TestResult tr;
    m_bc->getProductService()->resetCurrency(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCProduct, AwardParentCurrency)
{
    GoToChildProfile();
    TestResult tr;
    m_bc->getProductService()->awardParentCurrency(m_currencyType, 1000, m_parentLevelName.c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCProduct, ConsumeParentCurrency)
{
    GoToChildProfile();
    TestResult tr;
    m_bc->getProductService()->awardParentCurrency(m_currencyType, 100, m_parentLevelName.c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCProduct, GetParentCurrency)
{
    GoToChildProfile();
    TestResult tr;
    m_bc->getProductService()->getParentCurrency(m_currencyType, m_parentLevelName.c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCProduct, ResetParentCurrency)
{
    GoToChildProfile();
    TestResult tr;
    m_bc->getProductService()->resetParentCurrency(m_parentLevelName.c_str(), &tr);
    tr.run(m_bc);
}