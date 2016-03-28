#include "JsonUtil.h"

namespace BrainCloud
{
    Json::Value JsonUtil::jsonStringToValue(const std::string& in_jsonString)
    {
        Json::Value value;
        Json::Reader reader;
        reader.parse(in_jsonString, value);
        return value;
    }

    Json::Value JsonUtil::jsonStringToValue(const char * in_jsonString)
    {
        const char * end = in_jsonString;
        while (*end != '\0') {
            ++end;
        }
        Json::Value value;
        Json::Reader reader;
        reader.parse(in_jsonString, end, value);
        return value;
    }

    std::string JsonUtil::jsonValueToString(const Json::Value& in_jsonValue)
    {
        Json::FastWriter write;
        return write.write(in_jsonValue);
    }

    void JsonUtil::commaSepStringToJsonArray(const char * in_str, Json::Value & out_value)
    {
        std::string s = in_str;
        std::string json = "[";
        size_t start = 0, end = 0;

        while ((end = s.find(',', start)) != std::string::npos)
        {
            json += start == 0 ? "\"" : ",\"";
            json += s.substr(start, end - start);
            json += "\"";
            start = end + 1;
        }
        json += start == 0 ? "\"" : ",\"";
        json += s.substr(start, s.length() - start);
        json += "\"]";

        Json::Value value;
        Json::Reader reader;
        reader.parse(json, value);
        out_value = value;
    }

    Json::Value JsonUtil::stringVectorToJson(const std::vector<std::string> & in_stringVec)
    {
        Json::Value value;
        for (size_t i = 0, isize = in_stringVec.size(); i < isize; ++i)
        {
            value.append(in_stringVec[i]);
        }
        return value;
    }
}
