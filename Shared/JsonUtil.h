#include "json/json.h"

namespace BrainCloud
{
	class JsonUtil
	{
	public:
		static void commaSepStringToJsonArray(const char * in_str, Json::Value & out_value);        
        static Json::Value stringVectorToJson(const std::vector<std::string> & in_stringVec);
	};
}