#include "TestGUID.h"

#include <braincloud/internal/GUID.h>

void validateGUID(const std::string& guid)
{
    EXPECT_EQ(guid.size(), 36);
    for (int i = 0; i < 36; ++i)
    {
        char c = guid[i];
        if (i == 8 ||
            i == 13 ||
            i == 18 ||
            i == 23)
        {
            EXPECT_EQ('-', c);
        }
        else
        {
            EXPECT_TRUE((c >= 'a' && c <= 'f') || (c >= '0' && c <= '9'));
        }
    }
}

TEST_F(TestGUID, GenerateGUID)
{
    std::string guid;
    std::string prevGuid;
    
    guid = BrainCloud::GUID::generateGUID();
    validateGUID(guid);
    prevGuid = guid;

    guid = BrainCloud::GUID::generateGUID();
    EXPECT_NE(guid, prevGuid);
    validateGUID(guid);
    prevGuid = guid;

    guid = BrainCloud::GUID::generateGUID();
    EXPECT_NE(guid, prevGuid);
    validateGUID(guid);
    prevGuid = guid;

    guid = BrainCloud::GUID::generateGUID();
    EXPECT_NE(guid, prevGuid);
    validateGUID(guid);
}
