#ifndef _TESTBCENTITY_H_
#define _TESTBCENTITY_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCEntity : public TestFixtureBase
{
protected:
    std::string m_entityId;
    const char* m_entityType;
    
    void CreateDefaultEntity();
    void DeleteEntity(std::string entityId = "");
    void GenerateDefaultEntites(int numToGenerate);
    void DeleteAllDefaultEntities();
    
public:
    TestBCEntity()
    {
        m_entityType = "Test";
    }
};

#endif
