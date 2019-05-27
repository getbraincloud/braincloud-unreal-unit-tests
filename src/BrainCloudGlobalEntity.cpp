// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudGlobalEntity.h"

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
	BrainCloudGlobalEntity::BrainCloudGlobalEntity(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudGlobalEntity::createEntity(const std::string& in_entityType, int64_t in_timeToLive, const std::string& in_jsonEntityAcl,
		const std::string& in_jsonEntityData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::GlobalEntityServiceTimeToLive.getValue()] = (Json::Int64) in_timeToLive;
		message[OperationParam::GlobalEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityData);
		message[OperationParam::GlobalEntityServiceAcl.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityAcl);

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::Create, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::createEntityWithIndexedId(const std::string& in_entityType, const std::string& in_indexedId, int64_t in_timeToLive,
		const std::string& in_jsonEntityAcl, const std::string& in_jsonEntityData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::GlobalEntityServiceIndexedId.getValue()] = in_indexedId;
		message[OperationParam::GlobalEntityServiceTimeToLive.getValue()] = (Json::Int64) in_timeToLive;
		message[OperationParam::GlobalEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityData);
		message[OperationParam::GlobalEntityServiceAcl.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityAcl);

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::CreateWithIndexedId, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::updateEntity(const std::string& in_entityId, int64_t in_version, const std::string& in_jsonEntityData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::GlobalEntityServiceVersion.getValue()] = (Json::Int64) in_version;
		message[OperationParam::GlobalEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityData);

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::Update, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::updateEntityAcl(const std::string& in_entityId, int64_t in_version, const std::string& in_jsonEntityAcl, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::GlobalEntityServiceVersion.getValue()] = (Json::Int64) in_version;
		message[OperationParam::GlobalEntityServiceAcl.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityAcl);

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::UpdateAcl, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::updateEntityTimeToLive(const std::string& in_entityId, int64_t in_version, int64_t in_timeToLive, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::GlobalEntityServiceVersion.getValue()] = (Json::Int64) in_version;
		message[OperationParam::GlobalEntityServiceTimeToLive.getValue()] = (Json::Int64) in_timeToLive;

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::UpdateTimeToLive, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::deleteEntity(const std::string& in_entityId, int64_t in_version, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::GlobalEntityServiceVersion.getValue()] = (Json::Int64) in_version;

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::Delete, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::readEntity(const std::string& in_entityId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceEntityId.getValue()] = in_entityId;

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::Read, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::getList(const std::string& in_where, const std::string& in_orderBy, int64_t in_maxReturn, IServerCallback * in_callback)
	{
		Json::Value message;

		if (StringUtil::IsOptionalParameterValid(in_where)) {
			message[OperationParam::GlobalEntityServiceWhere.getValue()] = JsonUtil::jsonStringToValue(in_where);
		}

		if (StringUtil::IsOptionalParameterValid(in_orderBy)) {
			message[OperationParam::GlobalEntityServiceOrderBy.getValue()] = JsonUtil::jsonStringToValue(in_orderBy);
		}

		message[OperationParam::GlobalEntityServiceMaxReturn.getValue()] = (Json::Int64) in_maxReturn;

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetList, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::getListByIndexedId(const std::string& in_entityIndexedId, int64_t in_maxReturn, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceIndexedId.getValue()] = in_entityIndexedId;
		message[OperationParam::GlobalEntityServiceMaxReturn.getValue()] = (Json::Int64) in_maxReturn;

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetListByIndexedId, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::getListCount(const std::string& in_where, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceWhere.getValue()] = JsonUtil::jsonStringToValue(in_where);

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetListCount, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::getPage(const char * in_context, IServerCallback * in_callback)
	{
		Json::Value message;
		Json::Reader reader;

		Json::Value parsedContext;
		reader.parse(in_context, parsedContext);
		message[OperationParam::GlobalEntityServiceContext.getValue()] = parsedContext;

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetPage, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::getPageOffset(const char * in_context, int in_pageOffset, IServerCallback * in_callback)
	{
		Json::Value message;
		Json::Reader reader;

		message[OperationParam::GlobalEntityServiceContext.getValue()] = in_context;
		message[OperationParam::GlobalEntityServicePageOffset.getValue()] = in_pageOffset;

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetPageOffset, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::incrementGlobalEntityData(const char * in_entityId, std::string in_jsonData, IServerCallback * in_callback)
	{
		Json::Value message;
		Json::Reader reader;

		message[OperationParam::GlobalEntityServiceEntityId.getValue()] = in_entityId;

		Json::Value parsedData;
		reader.parse(in_jsonData, parsedData);
		message[OperationParam::GlobalEntityServiceData.getValue()] = parsedData;

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::IncrementGlobalEntityData, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::getRandomEntitiesMatching(const std::string& in_where, int64_t in_maxReturn, IServerCallback * in_callback)
	{
		Json::Value message;

		if (StringUtil::IsOptionalParameterValid(in_where)) {
			message[OperationParam::GlobalEntityServiceWhere.getValue()] = JsonUtil::jsonStringToValue(in_where);
		}

		message[OperationParam::GlobalEntityServiceMaxReturn.getValue()] = (Json::Int64) in_maxReturn;

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetRandomEntitiesMatching, message, in_callback);
		m_client->sendRequest(sc);
	}
	
	void BrainCloudGlobalEntity::updateEntityIndexedId(const char * in_entityId, int64_t in_version, const char * in_entityIndexedId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::GlobalEntityServiceVersion.getValue()] = (Json::Int64) in_version;
		message[OperationParam::GlobalEntityServiceIndexedId.getValue()] = in_entityIndexedId;

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::UpdateEntityIndexedId, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::updateEntityOwnerAndAcl(const char * in_entityId, int64_t in_version, const char * in_ownerId, const std::string & in_jsonEntityAcl, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::GlobalEntityServiceVersion.getValue()] = (Json::Int64) in_version;
		message[OperationParam::OwnerId.getValue()] = in_ownerId;
		message[OperationParam::GlobalEntityServiceAcl.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityAcl);

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::UpdateEntityOwnerAndAcl, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudGlobalEntity::makeSystemEntity(const char * in_entityId, int64_t in_version, const std::string & in_jsonEntityAcl, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GlobalEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::GlobalEntityServiceVersion.getValue()] = (Json::Int64) in_version;
		message[OperationParam::GlobalEntityServiceAcl.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityAcl);

		ServerCall * sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::MakeSystemEntity, message, in_callback);
		m_client->sendRequest(sc);
	}
}