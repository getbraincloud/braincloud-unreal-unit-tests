#include "SaveDataHelper.h"

#import "SSKeychain.h"
#import "SSKeychainQuery.h"

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

void SaveDataHelper::initialize(const char * companyName, const char * gameName)
{
	if (companyName != NULL && gameName != NULL)
	{
		std::string companyNameStr = companyName;
		std::string gameNameStr = gameName;
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
	
	[SSKeychain setPassword:dataString forService:serviceString account:keyString];
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
		data = [dataString UTF8String];
	
	return data;
}

void SaveDataHelper::deleteData(const char * key)
{
	if (m_savePath.empty())
		return;
	
	NSString * serviceString = [NSString stringWithUTF8String:m_savePath.c_str()];
	NSString * keyString = [NSString stringWithUTF8String:key];
	
	[SSKeychain deletePasswordForService:serviceString account:keyString];
}
