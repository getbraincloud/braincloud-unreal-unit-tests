// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudScript.h"

#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
#include "json/json.h"

#include "StringUtil.h"
#include "JsonUtil.h"
#include <time.h>

namespace BrainCloud
{
    BrainCloudScript::BrainCloudScript(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudScript::runScript(const char * in_scriptName, const std::string & in_jsonScriptData, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;

        Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonScriptData);
        message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;

        ServerCall * sc = new ServerCall(ServiceName::Script, ServiceOperation::Run, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudScript::scheduleRunScriptUTC(const char * in_scriptName, const char * in_jsonScriptData, const struct tm* in_startDateInUTC, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;

        if (StringUtil::IsOptionalParameterValid(in_jsonScriptData)) {
            Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonScriptData);
            message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
        }

        struct tm timeInfo = *in_startDateInUTC;
        message[OperationParam::ScriptServiceStartDateUTC.getValue()] = Json::Int64(mktime(&timeInfo) * 1000);

        ServerCall * sc = new ServerCall(ServiceName::Script, ServiceOperation::ScheduleCloudScript, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudScript::scheduleRunScriptMinutes(const char * in_scriptName, const char * in_jsonScriptData, int in_minutesFromNow, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;

        if (StringUtil::IsOptionalParameterValid(in_jsonScriptData)) {
            Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonScriptData);
            message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
        }

        message[OperationParam::ScriptServiceStartMinutesFromNow.getValue()] = in_minutesFromNow;

        ServerCall * sc = new ServerCall(ServiceName::Script, ServiceOperation::ScheduleCloudScript, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudScript::runParentScript(const char * in_scriptName, const char * in_jsonScriptData, const char * in_parentLevel, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;

        if (StringUtil::IsOptionalParameterValid(in_jsonScriptData)) {
            Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonScriptData);
            message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
        }

        message[OperationParam::ScriptServiceParentLevelName.getValue()] = in_parentLevel;

        ServerCall * sc = new ServerCall(ServiceName::Script, ServiceOperation::RunParentScript, message, in_callback);
        m_client->sendRequest(sc);
    }
}