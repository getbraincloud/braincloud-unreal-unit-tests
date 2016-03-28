#pragma once

#include "json/json.h"

namespace BrainCloud
{
    class JsonUtil
    {
    public:
        static Json::Value jsonStringToValue(const std::string& in_jsonString);
        static Json::Value jsonStringToValue(const char * in_jsonString);
        static std::string jsonValueToString(const Json::Value& in_jsonValue);

        static void commaSepStringToJsonArray(const char * in_str, Json::Value & out_value);
        static Json::Value stringVectorToJson(const std::vector<std::string> & in_stringVec);
    };
}