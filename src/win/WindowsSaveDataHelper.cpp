#include "braincloud/internal/win/WindowsSaveDataHelper.h"

#include <Windows.h>

namespace BrainCloud
{
    SaveDataHelper* SaveDataHelper::create()
    {
        return new WindowsSaveDataHelper();
    }

    WindowsSaveDataHelper::WindowsSaveDataHelper()
    {
    }

    void WindowsSaveDataHelper::initialize(const char * companyName, const char * appName, const char * wrapperName)
    {
        if (companyName != NULL && appName != NULL)
        {
            std::string companyNameStr = companyName;
            std::string gameNameStr = appName;
            m_savePath = std::string("Software\\" + companyNameStr + "\\" + gameNameStr + "\\");
        }
    }

    void WindowsSaveDataHelper::saveData(const char * key, const char * data)
    {
#if defined WINAPI_FAMILY && (WINAPI_FAMILY != WINAPI_FAMILY_DESKTOP_APP)
        std::string skey = key;
        std::string sdata = data;
        std::wstring wskey;
        std::wstring wsdata;
        for (auto c : skey) {
            wskey += (wchar_t)c;
        }
        for (auto c : sdata) {
            wsdata += (wchar_t)c;
        }
        Windows::Storage::ApplicationDataContainer^ localSettings = Windows::Storage::ApplicationData::Current->LocalSettings;
        auto values = localSettings->Values;
        values->Insert(
            ref new Platform::String(wskey.c_str()),
            dynamic_cast<Windows::Foundation::PropertyValue^>(Windows::Foundation::PropertyValue::CreateString(ref new Platform::String(wsdata.c_str()))));
#else
        if (m_savePath.empty())
        {
            return;
        }

        LONG status;
        HKEY hKey;

        status = RegOpenKeyExA(HKEY_CURRENT_USER, m_savePath.c_str(), 0, KEY_ALL_ACCESS, &hKey);
        if ((status == ERROR_SUCCESS) && (hKey != NULL)) {
            status = RegSetValueExA(hKey, key, 0, REG_SZ, (BYTE*)data, ((DWORD)strlen(data) + 1) * sizeof(char));
            RegCloseKey(hKey);
        }
        else if (status == ERROR_FILE_NOT_FOUND) {
            // Key didn't exist, create it
            SECURITY_ATTRIBUTES sAttribs = { sizeof(SECURITY_ATTRIBUTES) };
            DWORD dwDisposition = 0;
            status = RegCreateKeyExA(HKEY_CURRENT_USER, m_savePath.c_str(), 0, "", REG_OPTION_VOLATILE, KEY_ALL_ACCESS, &sAttribs, &hKey, &dwDisposition);
            if (status == ERROR_SUCCESS) {
                // Set it's value
                status = RegOpenKeyExA(HKEY_CURRENT_USER, m_savePath.c_str(), 0, KEY_ALL_ACCESS, &hKey);
                if ((status == ERROR_SUCCESS) && (hKey != NULL)) {
                    status = RegSetValueExA(hKey, key, 0, REG_SZ, (BYTE*)data, ((DWORD)strlen(data) + 1) * sizeof(char));
                    RegCloseKey(hKey);
                }
            }
        }
#endif
    }

    std::string WindowsSaveDataHelper::readData(const char * key)
    {
        std::string sdata;

#if defined WINAPI_FAMILY && (WINAPI_FAMILY != WINAPI_FAMILY_DESKTOP_APP)
        std::string skey = key;
        std::wstring wskey;
        for (auto c : skey) {
            wskey += (wchar_t)c;
        }
        Windows::Storage::ApplicationDataContainer^ localSettings = Windows::Storage::ApplicationData::Current->LocalSettings;
        auto values = localSettings->Values;
        Platform::String^ value = safe_cast<Platform::String^>(localSettings->Values->Lookup(ref new Platform::String(wskey.c_str())));
        if (!value) return "";
        std::wstring wsdata = value->Data();
        for (auto c : wsdata) {
            sdata += (char)c;
        }
#else
        if (m_savePath.empty())
        {
            return "";
        }

        LONG status;
        HKEY hKey;
        status = RegOpenKeyExA(HKEY_CURRENT_USER, m_savePath.c_str(), 0, KEY_READ, &hKey);
        if ((status == ERROR_SUCCESS) && (hKey != NULL)) {
            unsigned long type = REG_SZ, size = 1024;
            char res[1024] = "";

            status = RegQueryValueExA(hKey,
                key, NULL, &type, (LPBYTE)&res[0], &size);

            RegCloseKey(hKey);

            if (status == ERROR_SUCCESS) {
                sdata = res;
            }
        }
#endif

        return sdata;
    }

    void WindowsSaveDataHelper::deleteData(const char * key)
    {
#if defined WINAPI_FAMILY && (WINAPI_FAMILY != WINAPI_FAMILY_DESKTOP_APP)
        std::string skey = key;
        std::wstring wskey;
        for (auto c : skey) {
            wskey += (wchar_t)c;
        }
        Windows::Storage::ApplicationDataContainer^ localSettings = Windows::Storage::ApplicationData::Current->LocalSettings;
        auto values = localSettings->Values;
        values->Remove(ref new Platform::String(wskey.c_str()));
#else
        if (m_savePath.empty())
        {
            return;
        }

        std::string data;

        LONG status;
        HKEY hKey;
        status = RegOpenKeyExA(HKEY_CURRENT_USER, m_savePath.c_str(), 0, KEY_SET_VALUE, &hKey);
        if ((status == ERROR_SUCCESS) && (hKey != NULL)) {
            unsigned long type = REG_SZ, size = 1024;
            char res[1024] = "";

            status = RegDeleteValueA(hKey, key);
            RegCloseKey(hKey);
        }
#endif
    }
}
