#pragma once

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCGroup : public TestFixtureBase
{
protected:
    TestBCGroup();

    virtual bool ShouldSkipAuthenticate() {
        return true;
    }

    void CreateGroupAsUserA(bool isOpen = false);
    void DeleteGroupAsUserA();
    void Authenticate(Users user);
    void CreateGroup(bool isOpen = false);
    void CreateGroupWithSummaryData(bool isOpen = false);
    std::string CreateGroupEntity();
    void DeleteGroup();
    std::string CreateContext(int numItemsPerPage, int startPage, std::string searchKey, std::string searchValue);

    const char* _testAcl;
    const char* _testJsonPair;
    const char* _groupType;
    const char* _entityType;
    std::string _groupId;
};

