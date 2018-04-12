#ifndef _WINDOWSSAVEDATAHELPER_H_
#define _WINDOWSSAVEDATAHELPER_H_

#include "braincloud/internal/SaveDataHelper.h"

namespace BrainCloud
{
    class WindowsSaveDataHelper : public SaveDataHelper
    {
    public:
        virtual void initialize(const char * companyName, const char * appName, const char * wrapperName = "");

        virtual void saveData(const char * key, const char * data);
        virtual std::string readData(const char * key);
        virtual void deleteData(const char * key);

    protected:
        friend class SaveDataHelper;

        WindowsSaveDataHelper();

    private:
        std::string m_savePath;
    };
}

#endif
