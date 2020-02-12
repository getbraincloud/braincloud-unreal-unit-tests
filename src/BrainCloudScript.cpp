// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudScript.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"
#include <time.h>
#include "braincloud/internal/timegm.h"

namespace BrainCloud
{
	BrainCloudScript::BrainCloudScript(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudScript::runScript(const char * in_scriptName, const std::string & in_jsonScriptData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;

		if (StringUtil::IsOptionalParameterValid(in_jsonScriptData)) {
			Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonScriptData);
			message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
		}

		ServerCall * sc = new ServerCall(ServiceName::Script, ServiceOperation::Run, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudScript::scheduleRunScriptUTC(const char * in_scriptName, const char * in_jsonScriptData, const tm* in_startDateInUTC, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;

		if (StringUtil::IsOptionalParameterValid(in_jsonScriptData)) {
			Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonScriptData);
			message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
		}

		struct tm timeInfo = *in_startDateInUTC;
		message[OperationParam::ScriptServiceStartDateUTC.getValue()] = (Json::Int64) ((int64_t)internal_timegm(&timeInfo)) * 1000;

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

	void BrainCloudScript::cancelScheduledScript(const char * in_jobId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ScriptServiceJobId.getValue()] = in_jobId;

		ServerCall * sc = new ServerCall(ServiceName::Script, ServiceOperation::CancelScheduledScript, message, in_callback);
		m_client->sendRequest(sc);
	}

		void BrainCloudScript::getScheduledCloudScript(const char * in_jobId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ScriptServiceJobId.getValue()] = in_jobId;

		ServerCall * sc = new ServerCall(ServiceName::Script, ServiceOperation::GetScheduledCloudScripts, message, in_callback);
		m_client->sendRequest(sc);
	}

		void BrainCloudScript::getRunningOrScheduledScripts(IServerCallback * in_callback)
	{
		// Json::Value message;
		// message[OperationParam::ScriptServiceJobId.getValue()] = in_jobId;

		ServerCall * sc = new ServerCall(ServiceName::Script, ServiceOperation::GetRunningOrQueuedCloudScripts, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudScript::runPeerScript(const char * in_scriptName, const std::string & in_jsonScriptData, const char * in_peer, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;
		message[OperationParam::Peer.getValue()] = in_peer;

		if (StringUtil::IsOptionalParameterValid(in_jsonScriptData)) {
			Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonScriptData);
			message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
		}

		ServerCall * sc = new ServerCall(ServiceName::Script, ServiceOperation::RunPeerScript, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudScript::runPeerScriptAsync(const char * in_scriptName, const std::string & in_jsonScriptData, const char * in_peer, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ScriptServiceRunScriptName.getValue()] = in_scriptName;
		message[OperationParam::Peer.getValue()] = in_peer;

		if (StringUtil::IsOptionalParameterValid(in_jsonScriptData)) {
			Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonScriptData);
			message[OperationParam::ScriptServiceRunScriptData.getValue()] = jsonData;
		}

		ServerCall * sc = new ServerCall(ServiceName::Script, ServiceOperation::RunPeerScriptAsync, message, in_callback);
		m_client->sendRequest(sc);
	}
}