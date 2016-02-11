#include "BrainCloudScript.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "StringUtil.h"
#include <time.h>

namespace BrainCloud {
    
    void BrainCloudScript::runScript(const char * in_scriptName, const std::string & in_jsonScriptData, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;
        
        Json::Value jsonData = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonScriptData);
        message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
        
        ServerCall * sc = new ServerCall( ServiceName::Script, ServiceOperation::Run, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest(sc);
    }
    
    void BrainCloudScript::scheduleRunScriptUTC(const char * in_scriptName, const char * in_jsonScriptData, const struct tm* in_startDateInUTC, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;
        
        if (StringUtil::IsOptionalParameterValid(in_jsonScriptData)) {
            Json::Value jsonData = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonScriptData);
            message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
        }
        
        struct tm timeInfo = *in_startDateInUTC;
        message[OperationParam::ScriptServiceStartDateUTC.getValue()] = Json::Int64(mktime(&timeInfo) * 1000);
        
        ServerCall * sc = new ServerCall( ServiceName::Script, ServiceOperation::ScheduleCloudScript, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest(sc);
    }
    
    void BrainCloudScript::scheduleRunScriptMinutes(const char * in_scriptName, const char * in_jsonScriptData, int in_minutesFromNow, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;
        
        if (StringUtil::IsOptionalParameterValid(in_jsonScriptData)) {
            Json::Value jsonData = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonScriptData);
            message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
        }
        
        message[OperationParam::ScriptServiceStartMinutesFromNow.getValue()] = in_minutesFromNow;
        
        ServerCall * sc = new ServerCall( ServiceName::Script, ServiceOperation::ScheduleCloudScript, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest(sc);
    }
    
    void BrainCloudScript::runParentScript(const char * in_scriptName, const char * in_jsonScriptData, const char * in_parentLevel, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;
        
        if (StringUtil::IsOptionalParameterValid(in_jsonScriptData)) {
            Json::Value jsonData = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonScriptData);
            message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
        }
        
        message[OperationParam::ScriptServiceParentLevelName.getValue()] = in_parentLevel;
        
        ServerCall * sc = new ServerCall( ServiceName::Script, ServiceOperation::RunParentScript, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest(sc);
    }
}