// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudCustomEntity.h"

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
	BrainCloudCustomEntity::BrainCloudCustomEntity(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudCustomEntity::createEntity(const char * in_entityType, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, int64_t in_timeToLive, bool in_isOwned, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityData);
		message[OperationParam::CustomEntityServiceAcl.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityAcl);
		message[OperationParam::CustomEntityServiceTimeToLive.getValue()] = (Json::Int64) in_timeToLive;
		message[OperationParam::CustomEntityServiceIsOwned.getValue()] = in_isOwned;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::CreateEntity, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::deleteEntity(const char * in_entityType,  const char * in_entityId, const std::string& in_jsonEntityData, int32_t in_version, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::CustomEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityData);
		message[OperationParam::CustomEntityServiceVersion.getValue()] = in_version;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::DeleteEntity, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::getCount(const char * in_entityType, const std::string& in_whereJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_whereJson);

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::GetCount, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::getRandomEntitiesMatching(const char * in_entityType, const std::string& in_whereJson, const int32_t in_maxReturn, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_whereJson);
        message[OperationParam::CustomEntityServiceMaxReturn.getValue()] = in_maxReturn;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::GetRandomEntitiesMatching, message, in_callback);
		m_client->sendRequest(sc);
	}


	void BrainCloudCustomEntity::getEntityPage(const char * in_entityType, const char * in_context, IServerCallback * in_callback)
	{
		Json::Value message;
		Json::Reader reader;

		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		Json::Value parsedContext;
		reader.parse(in_context, parsedContext);
		message[OperationParam::CustomEntityServiceContext.getValue()] = parsedContext;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::GetCustomEntityPage, message, in_callback);
		m_client->sendRequest(sc);
	}
  
	void BrainCloudCustomEntity::getEntityPageOffset(const char * in_entityType, const std::string& in_context, int32_t in_pageOffset, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceContext.getValue()] = in_context;
		message[OperationParam::CustomEntityServicePageOffset.getValue()] = in_pageOffset;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::GetEntityPageOffset, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::readEntity(const char * in_entityType, const char * in_entityId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceEntityId.getValue()] = in_entityId;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::ReadEntity, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::updateEntity(const char * in_entityType, const char * in_entityId, int32_t in_version, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, int64_t in_timeToLive, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::CustomEntityServiceVersion.getValue()] = in_version;
		message[OperationParam::CustomEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityData);
		message[OperationParam::CustomEntityServiceAcl.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityAcl);
		message[OperationParam::CustomEntityServiceTimeToLive.getValue()] = (Json::Int64) in_timeToLive;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateEntity, message, in_callback);
		m_client->sendRequest(sc);
	}
	
	void BrainCloudCustomEntity::updateEntityFields(const char * in_entityType, const char * in_entityId, int32_t in_version, const std::string& in_fieldsJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::CustomEntityServiceVersion.getValue()] = in_version;
		message[OperationParam::CustomEntityFieldsJson.getValue()] = JsonUtil::jsonStringToValue(in_fieldsJson);

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateEntityFields, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::deleteEntities(const char * in_entityType, const char * in_deleteCriteria, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceDeleteCriteria.getValue()] = JsonUtil::jsonStringToValue(in_deleteCriteria);
		
		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::DeleteEntities, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::deleteSingleton(const char * in_entityType, int32_t in_version, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceVersion.getValue()] = in_version;
		
		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::DeleteSingleton, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::updateSingleton(const char * in_entityType, int32_t in_version, const std::string& in_dataJson, const std::string& in_acl, int64_t in_timeToLive, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceVersion.getValue()] = in_version;
		message[OperationParam::CustomEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_dataJson);
		message[OperationParam::CustomEntityServiceAcl.getValue()] = JsonUtil::jsonStringToValue(in_acl);
		message[OperationParam::CustomEntityServiceTimeToLive.getValue()] = (Json::Int64) in_timeToLive;
		
		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateSingleton, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::updateSingletonFields(const char * in_entityType, int32_t in_version, const std::string& in_fieldsJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceVersion.getValue()] = in_version;
		message[OperationParam::CustomEntityFieldsJson.getValue()] = JsonUtil::jsonStringToValue(in_fieldsJson);

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateSingletonFields, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::readSingleton(const char * in_entityType, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
				
		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::ReadSingleton, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::incrementData(const char * in_entityType, const char * in_entityId, const std::string& in_fieldsJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::CustomEntityFieldsJson.getValue()] = JsonUtil::jsonStringToValue(in_fieldsJson);

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::IncrementData, message, in_callback);
		m_client->sendRequest(sc);
	}

}
