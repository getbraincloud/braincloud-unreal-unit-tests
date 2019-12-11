#include "TestGUID.h"

#include <braincloud/internal/GUID.h>

void validateGUID(const std::string& guid)
{
    int count = 0;
    for (auto c : guid)
    {
        if (c == '-') continue;
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'F') ||
            (c >= 'a' && c <= 'f'))
        {
            count++;
        }
    }
    EXPECT_EQ(count, 32);
}

TEST_F(TestGUID, GenerateGUID)
{
    std::string guid;
    std::string prevGuid;
    
    guid = BrainCloud::GUID::generateGUID();
    std::cout << guid << std::endl;
    validateGUID(guid);
    prevGuid = guid;

    guid = BrainCloud::GUID::generateGUID();
    std::cout << guid << std::endl;
    EXPECT_NE(guid, prevGuid);
    validateGUID(guid);
    prevGuid = guid;

    guid = BrainCloud::GUID::generateGUID();
    std::cout << guid << std::endl;
    EXPECT_NE(guid, prevGuid);
    validateGUID(guid);
    prevGuid = guid;

    guid = BrainCloud::GUID::generateGUID();
    std::cout << guid << std::endl;
    EXPECT_NE(guid, prevGuid);
    validateGUID(guid);
}
