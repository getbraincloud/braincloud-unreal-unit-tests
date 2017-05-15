#include "braincloud/internal/SaveDataHelper.h"

#import "SSKeychain/SSKeychain.h"
#import "SSKeychain/SSKeychainQuery.h"

SaveDataHelper * SaveDataHelper::m_instance = NULL;

SaveDataHelper::SaveDataHelper()
: m_savePath("")
{

}

SaveDataHelper * SaveDataHelper::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new SaveDataHelper();
	}

	return m_instance;
}

void SaveDataHelper::initialize(const char * companyName, const char * appName)
{
	if (companyName != NULL && appName != NULL)
	{
		std::string companyNameStr = companyName;
		std::string gameNameStr = appName;
		m_savePath = companyNameStr + "." + gameNameStr;
	}
}

void SaveDataHelper::saveData(const char * key, const char * data)
{
	if (m_savePath.empty())
		return;

	NSString * serviceString = [NSString stringWithUTF8String:m_savePath.c_str()];
	NSString * keyString = [NSString stringWithUTF8String:key];
	NSString * dataString = [NSString stringWithUTF8String:data];

    [SSKeychain deletePasswordForService:serviceString account:keyString];

    if (dataString.length == 0)
    {
        [[NSUserDefaults standardUserDefaults] removeObjectForKey:keyString];
    }
    else
    {
        [[NSUserDefaults standardUserDefaults] setValue:dataString forKeyPath:keyString];
    }
}

std::string SaveDataHelper::readData(const char * key)
{
	if (m_savePath.empty())
		return "";

	NSString * serviceString = [NSString stringWithUTF8String:m_savePath.c_str()];
	NSString * keyString = [NSString stringWithUTF8String:key];

	NSString * dataString = [SSKeychain passwordForService:serviceString account:keyString];

	std::string data = "";

	if (dataString != nil)
    {
        [[NSUserDefaults standardUserDefaults] setValue:dataString forKeyPath:keyString];
        [SSKeychain deletePasswordForService:serviceString account:keyString];
        data = [dataString UTF8String];
    }

	return data;
}

void SaveDataHelper::deleteData(const char * key)
{
	if (m_savePath.empty())
		return;

	NSString * serviceString = [NSString stringWithUTF8String:m_savePath.c_str()];
	NSString * keyString = [NSString stringWithUTF8String:key];

	[SSKeychain deletePasswordForService:serviceString account:keyString];
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:keyString];
}
