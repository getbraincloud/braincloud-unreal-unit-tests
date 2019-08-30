#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCUserInventoryManagement.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"


using namespace BrainCloud;

TEST_F(TestBCUserInventoryManagement, AwardUserItem)
{
    TestResult tr;
    m_bc->getUserInventoryManagementService()->awardUserItem("sword001", 5, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCUserInventoryManagement, DropUserItem)
{
    TestResult tr;
    m_bc->getUserInventoryManagementService()->dropUserItem("invalidForNow", 1, true, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserInventoryManagement, GetUserInventory)
{
    std::string criteria = "{\"itemData.bonus\": \"1\"}";
    TestResult tr;
    m_bc->getUserInventoryManagementService()->getUserInventory(criteria, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCUserInventoryManagement, GetUserInventoryPage)
{
    std::string context = "{\"test\": \"Testing\"}";
    TestResult tr;
    m_bc->getUserInventoryManagementService()->getUserInventoryPage(context, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCUserInventoryManagement, GetUserInventoryPageOffset)
{
    std::string context = "eyJzZWFyY2hDcml0ZXJpYSI6eyJnYW1lSWQiOiIyMDAwMSIsInBsYXllcklkIjoiYzU1YzIzY2UtMGU2Yi00OWQzLTlmZjYtYWUyNDYwNWVhOWM5IiwiZ2lmdGVkVG8iOm51bGx9LCJzb3J0Q3JpdGVyaWEiOnt9LCJwYWdpbmF0aW9uIjp7InJvd3NQZXJQYWdlIjoxMDAsInBhZ2VOdW1iZXIiOm51bGwsImRvQ291bnQiOnRydWV9LCJvcHRpb25zIjpudWxsfQ";
    TestResult tr;
    m_bc->getUserInventoryManagementService()->getUserInventoryPageOffset(context, 1, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCUserInventoryManagement, GetUserItem)
{
    TestResult tr;
    m_bc->getUserInventoryManagementService()->getUserItem("invalidForNow", true, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserInventoryManagement, GiveUserItemTo)
{
    TestResult tr;
    m_bc->getUserInventoryManagementService()->giveUserItemTo(GetUser(UserA)->m_profileId, "invalidForNow", 1, true, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, CANNOT_GIVE_ITEM_TO_SELF);
}


TEST_F(TestBCUserInventoryManagement, PurchaseUserItem)
{
    TestResult tr;
    m_bc->getUserInventoryManagementService()->purchaseUserItem("sword001", 1, "", true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCUserInventoryManagement, ReceiveUserItemFrom)
{
    TestResult tr;
    m_bc->getUserInventoryManagementService()->receiveUserItemFrom(GetUser(UserB)->m_profileId, "invalidForNow", &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserInventoryManagement, SellUserItem)
{
    TestResult tr;
    m_bc->getUserInventoryManagementService()->sellUserItem("invalidForNow", 1, 1, "", true, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserInventoryManagement, UpdateUserItemData)
{
    std::string newItemData = "{\"test\": \"Testing\"}";
    TestResult tr;
    m_bc->getUserInventoryManagementService()->updateUserItemData("invalidForNow", 1, newItemData, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserInventoryManagement, UseUserItem)
{
    std::string newItemData = "{\"test\": \"Testing\"}";
    TestResult tr;
    m_bc->getUserInventoryManagementService()->useUserItem("invalidForNow", 1, newItemData, true, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserInventoryManagement, PublishUserItemToBlockchain)
{
    TestResult tr;
    m_bc->getUserInventoryManagementService()->publishUserItemToBlockchain("invalidForNow", 1, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, ITEM_NOT_FOUND);
}

TEST_F(TestBCUserInventoryManagement, RefreshBlockchainUserItems)
{
    TestResult tr;
    m_bc->getUserInventoryManagementService()->refreshBlockchainUserItems(&tr);
    tr.run(m_bc);
}