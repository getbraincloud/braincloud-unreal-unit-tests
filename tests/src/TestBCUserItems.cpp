#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCUserItems.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"


using namespace BrainCloud;

TEST_F(TestBCUserItems, AwardUserItem)
{
    TestResult tr;
    m_bc->getUserItemsService()->awardUserItem("sword001", 5, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCUserItems, DropUserItem)
{
    TestResult tr;
    m_bc->getUserItemsService()->dropUserItem("invalidForNow", 1, true, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserItems, GetUserItemsPage)
{
    std::string context = "{\"test\": \"Testing\"}";
    TestResult tr;
    m_bc->getUserItemsService()->getUserItemsPage(context, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCUserItems, GetUserItemsPageOffset)
{
    std::string context = "eyJzZWFyY2hDcml0ZXJpYSI6eyJnYW1lSWQiOiIyMDAwMSIsInBsYXllcklkIjoiYzU1YzIzY2UtMGU2Yi00OWQzLTlmZjYtYWUyNDYwNWVhOWM5IiwiZ2lmdGVkVG8iOm51bGx9LCJzb3J0Q3JpdGVyaWEiOnt9LCJwYWdpbmF0aW9uIjp7InJvd3NQZXJQYWdlIjoxMDAsInBhZ2VOdW1iZXIiOm51bGwsImRvQ291bnQiOnRydWV9LCJvcHRpb25zIjpudWxsfQ";
    TestResult tr;
    m_bc->getUserItemsService()->getUserItemsPageOffset(context, 1, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCUserItems, GetUserItem)
{
    TestResult tr;
    m_bc->getUserItemsService()->getUserItem("invalidForNow", true, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserItems, GiveUserItemTo)
{
    TestResult tr;
    m_bc->getUserItemsService()->giveUserItemTo(GetUser(UserA)->m_profileId, "invalidForNow", 1, 1, true, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, CANNOT_GIVE_ITEM_TO_SELF);
}

TEST_F(TestBCUserItems, PurchaseUserItem)
{
    TestResult tr;
    m_bc->getUserItemsService()->purchaseUserItem("sword001", 1, "", true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCUserItems, ReceiveUserItemFrom)
{
    TestResult tr;
    m_bc->getUserItemsService()->receiveUserItemFrom(GetUser(UserB)->m_profileId, "invalidForNow", &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserItems, SellUserItem)
{
    TestResult tr;
    m_bc->getUserItemsService()->sellUserItem("invalidForNow", 1, 1, "", true, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserItems, UpdateUserItemData)
{
    std::string newItemData = "{\"test\": \"Testing\"}";
    TestResult tr;
    m_bc->getUserItemsService()->updateUserItemData("invalidForNow", 1, newItemData, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserItems, UseUserItem)
{
    std::string newItemData = "{\"test\": \"Testing\"}";
    TestResult tr;
    m_bc->getUserItemsService()->useUserItem("invalidForNow", 1, newItemData, true, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserItems, PublishUserItemToBlockchain)
{
    TestResult tr;
    m_bc->getUserItemsService()->publishUserItemToBlockchain("invalidForNow", 1, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserItems, RefreshBlockchainUserItems)
{
    TestResult tr;
    m_bc->getUserItemsService()->refreshBlockchainUserItems(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCUserItems, removeUserItemFromBlockchain)
{
    TestResult tr;
    m_bc->getUserItemsService()->removeUserItemFromBlockchain("invalidForNow", 1, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}