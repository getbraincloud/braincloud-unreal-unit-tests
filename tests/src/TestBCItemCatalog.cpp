#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCItemCatalog.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"


using namespace BrainCloud;

TEST_F(TestBCItemCatalog, GetCatalogItemDefinition)
{
    TestResult tr;
    m_bc->getItemCatalogService()->getCatalogItemDefinition("sword001", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCItemCatalog, GetCatologItemsPage)
{
    std::string context = "{\"test\": \"Testing\"}";
    TestResult tr;
    m_bc->getItemCatalogService()->getCatalogItemsPage(context, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCItemCatalog, GetCatologItemsPageOffset)
{
    std::string context = "eyJzZWFyY2hDcml0ZXJpYSI6eyJnYW1lSWQiOiIyMDAwMSJ9LCJzb3J0Q3JpdGVyaWEiOnt9LCJwYWdpbmF0aW9uIjp7InJvd3NQZXJQYWdlIjoxMDAsInBhZ2VOdW1iZXIiOm51bGwsImRvQ291bnQiOnRydWV9LCJvcHRpb25zIjpudWxsfQ";
    TestResult tr;
    m_bc->getItemCatalogService()->getCatalogItemsPageOffset(context, 1, &tr);
    tr.run(m_bc);
}