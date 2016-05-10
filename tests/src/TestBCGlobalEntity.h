#ifndef _TESTBCGLOBALENTITY_H_
#define _TESTBCGLOBALENTITY_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCGlobalEntity: public TestFixtureBase
{
public:
    TestBCGlobalEntity();
protected:
    std::string m_entityType;
    std::string m_indexedId;
    std::string m_entityId;
    
    std::string m_entityDataJson;
    std::string m_entityAclJson;
    
    void CreateDefaultGlobalEntity(std::string indexedId = "");
    void GenerateDefaultEntites(int numToGenerate);
};

#endif
