#include "BrainCloudEntity.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

namespace BrainCloud {

	void BrainCloudEntity::createEntity( const char * in_entityType, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::EntityServiceCreateEntityType.getValue()] = in_entityType;
		message[OperationParam::EntityServiceCreateData.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonEntityData);
		message[OperationParam::EntityServiceCreateAcl.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonEntityAcl);
		
		ServerCall * sc = new ServerCall( ServiceName::Entity, ServiceOperation::Create, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
    }
    
	void BrainCloudEntity::getEntity(const char * in_entityId, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::EntityServiceCreateEntityId.getValue()] = in_entityId;
		
		ServerCall * sc = new ServerCall( ServiceName::Entity, ServiceOperation::Read, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
	}
    
    void BrainCloudEntity::getSingleton(const char * in_entityType, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::EntityServiceCreateEntityType.getValue()] = in_entityType;
        
        ServerCall * sc = new ServerCall( ServiceName::Entity, ServiceOperation::ReadSingleton, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
    }

	void BrainCloudEntity::getEntitiesByType( const char * in_entityType, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::EntityServiceGetEntitiesByTypeEntityType.getValue()] = in_entityType;
		
		ServerCall * sc = new ServerCall( ServiceName::Entity, ServiceOperation::ReadByType, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudEntity::updateEntity( const char * in_entityId, const char * in_entityType, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, int64_t in_version, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::EntityServiceCreateEntityId.getValue()] = in_entityId;
		message[OperationParam::EntityServiceCreateEntityType.getValue()] = in_entityType;
		message[OperationParam::EntityServiceCreateData.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonEntityData);
		message[OperationParam::EntityServiceCreateAcl.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonEntityAcl);
        message[OperationParam::EntityServiceUpdateVersion.getValue()] = (Json::Int64) in_version;
		
        ServerCall * sc = new ServerCall( ServiceName::Entity, ServiceOperation::Update, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
    }
	
    void BrainCloudEntity::updateSingleton(const char * in_entityType, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, int64_t in_version, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::EntityServiceCreateEntityType.getValue()] = in_entityType;
		message[OperationParam::EntityServiceCreateData.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonEntityData);
        message[OperationParam::EntityServiceCreateAcl.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonEntityAcl);
		message[OperationParam::EntityServiceUpdateVersion.getValue()] = (Json::Int64) in_version;

		ServerCall * sc = new ServerCall(ServiceName::Entity, ServiceOperation::UpdateSingleton, message, in_callback);
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	/*Unavailable for now...
	void BrainCloudEntity::updatePartialEntity( const char * type, int64_t id, const std::string& jsonUpdateOps, IServerCallback * callback )
	{
#if defined(USING_PANTHEIOS)
		
		pantheios::log_DEBUG( "BrainCloudClient::updatePartialEntity: ", type, " ", pantheios::integer(id), " ", jsonUpdateOps.c_str() );
#endif
		Json::Value message;
		message["entityType"] = type;
		message["entityId"] = id;
		message["updateOps"] = BrainCloudClient::getInstance()->jsonStringToValue(jsonUpdateOps);
		
        ServerCall * sc = new ServerCall( ServiceName::Entity, ServiceOperation::UpdatePartial, message, callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
		
#if defined(USING_PANTHEIOS)
		
		pantheios::log_DEBUG( "BrainCloudClient::updatePartialEntity returns" );
#endif
    }
	*/
	
	void BrainCloudEntity::deleteEntity(const char * in_entityId, int64_t in_version, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::EntityServiceDeleteEntityId.getValue()] = in_entityId;
		message[OperationParam::EntityServiceUpdateVersion.getValue()] = (Json::Int64) in_version;
		
		ServerCall * sc = new ServerCall( ServiceName::Entity, ServiceOperation::Delete, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
    }
	
	void BrainCloudEntity::deleteSingleton(const char * in_entityType, int64_t in_version, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::EntityServiceCreateEntityType.getValue()] = in_entityType;
		message[OperationParam::EntityServiceUpdateVersion.getValue()] = (Json::Int64) in_version;

		ServerCall * sc = new ServerCall(ServiceName::Entity, ServiceOperation::DeleteSingleton, message, in_callback);
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudEntity::getSharedEntitiesForPlayerId(const char * in_playerId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::EntityServiceGetSharedEntitiesTargetPlayerId.getValue()] = in_playerId;
		
		ServerCall * sc = new ServerCall( ServiceName::Entity, ServiceOperation::ReadShared, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
	}
    
	void BrainCloudEntity::updateSharedEntity(const char * in_entityId, const char * in_targetPlayerId, const char * in_entityType, const std::string& in_jsonEntityData, int64_t in_version, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::EntityServiceUpdateEntityId.getValue()] = in_entityId;
   		message[OperationParam::EntityServiceUpdateTargetPlayerId.getValue()] = in_targetPlayerId;
		message[OperationParam::EntityServiceUpdateEntityType.getValue()] = in_entityType;
		message[OperationParam::EntityServiceUpdateVersion.getValue()] = (Json::Int64) in_version;
		message[OperationParam::EntityServiceUpdateData.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonEntityData);
		
        ServerCall * sc = new ServerCall( ServiceName::Entity, ServiceOperation::UpdateShared, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
    }
    
    void BrainCloudEntity::getPage(const char * in_context, IServerCallback * in_callback)
    {
        Json::Value message;
        Json::Reader reader;
        
        Json::Value parsedContext;
        reader.parse(in_context, parsedContext);
        message[OperationParam::GlobalEntityServiceContext.getValue()] = parsedContext;
        
        ServerCall * sc = new ServerCall(ServiceName::Entity, ServiceOperation::GetPage, message, in_callback);
        BrainCloudClient::getInstance()->sendRequest(sc);
    }
    
    void BrainCloudEntity::getPageOffset(const char * in_context, int in_pageOffset, IServerCallback * in_callback)
    {
        Json::Value message;
        Json::Reader reader;
        
        message[OperationParam::GlobalEntityServiceContext.getValue()] = in_context;
        message[OperationParam::GlobalEntityServicePageOffset.getValue()] = in_pageOffset;
        
        ServerCall * sc = new ServerCall(ServiceName::Entity, ServiceOperation::GetPageOffset, message, in_callback);
        BrainCloudClient::getInstance()->sendRequest(sc);
    }

}