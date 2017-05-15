// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudMail.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud
{
	BrainCloudMail::BrainCloudMail(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudMail::sendBasicEmail(const char * in_profileId, const char * in_subject, const char * in_body, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ProfileId.getValue()] = in_profileId;
		message[OperationParam::Subject.getValue()] = in_subject;
		message[OperationParam::Body.getValue()] = in_body;

		ServerCall * sc = new ServerCall(ServiceName::Mail, ServiceOperation::SendBasicEmail, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudMail::sendAdvancedEmail(const char * in_profileId, const std::string & in_jsonServiceParams, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ProfileId.getValue()] = in_profileId;

		Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonServiceParams);
		message[OperationParam::ServiceParams.getValue()] = jsonData;

		ServerCall * sc = new ServerCall(ServiceName::Mail, ServiceOperation::SendAdvancedEmail, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudMail::sendAdvancedEmailByAddress(const char * in_emailAddress, const std::string & in_jsonServiceParams, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::EmailAddress.getValue()] = in_emailAddress;

		Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonServiceParams);
		message[OperationParam::ServiceParams.getValue()] = jsonData;

		ServerCall * sc = new ServerCall(ServiceName::Mail, ServiceOperation::SendAdvancedEmailByAddress, message, in_callback);
		m_client->sendRequest(sc);
	}
}