#ifndef __SAVE_DATA_HELPER__
#define __SAVE_DATA_HELPER__

#include <string>

class SaveDataHelper
{
public:
    static SaveDataHelper * getInstance();

    void initialize(const char * companyName, const char * appName);

    void saveData(const char * key, const char * data);
    std::string readData(const char * key);
    void deleteData(const char * key);

private:
    SaveDataHelper();

    std::string m_savePath;

    static SaveDataHelper * m_instance;
};

#endif
