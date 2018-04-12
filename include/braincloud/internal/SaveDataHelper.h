#ifndef _SAVEDATAHELPER_H_
#define _SAVEDATAHELPER_H_

#include <string>

namespace BrainCloud
{
    class SaveDataHelper
    {
    public:
        static SaveDataHelper* getInstance();

        virtual void initialize(const char* companyName, const char* appName, const char* wrapperName = "") = 0;

        virtual void saveData(const char* key, const char* data) = 0;
        virtual std::string readData(const char* key) = 0;
        virtual void deleteData(const char* key) = 0;

    protected:
        SaveDataHelper();

    private:
        static SaveDataHelper* create();

        static SaveDataHelper* s_instance;

        std::string m_savePath;
    };
}

#endif
