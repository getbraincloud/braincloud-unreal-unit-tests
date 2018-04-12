#include "braincloud/internal/DefaultSaveDataHelper.h"

namespace BrainCloud
{
    SaveDataHelper* SaveDataHelper::create()
    {
        return new DefaultSaveDataHelper();
    }

    DefaultSaveDataHelper::DefaultSaveDataHelper()
    {
    }

    void DefaultSaveDataHelper::initialize(const char * companyName, const char * appName, const char * wrapperName)
    {
    }

    void DefaultSaveDataHelper::saveData(const char * key, const char * data)
    {
    }

    std::string DefaultSaveDataHelper::readData(const char * key)
    {
        std::string sdata;
        return sdata;
    }

    void DefaultSaveDataHelper::deleteData(const char * key)
    {
    }
}
