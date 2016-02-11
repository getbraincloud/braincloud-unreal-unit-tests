#include "BrainCloudPlayerStatisticsEvent.h"

#include "BrainCloudTypes.h"
#include "BrainCloudClient.h"

namespace BrainCloud {

	void BrainCloudPlayerStatisticsEvent::triggerPlayerStatisticsEvent(const char * in_eventName, int in_eventMultiplier, IServerCallback * in_callback) {
        Json::Value message;
		
		message[OperationParam::PlayerStatisticEventServiceEventName.getValue()] = in_eventName;
        message[OperationParam::PlayerStatisticEventServiceEventMultiplier.getValue()] = in_eventMultiplier;
		
		ServerCall * sc = new ServerCall(ServiceName::PlayerStatisticsEvent, ServiceOperation::Trigger, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );

    }
	
    void BrainCloudPlayerStatisticsEvent::triggerPlayerStatisticsEvents(const std::string& in_jsonData, IServerCallback * in_callback) {
		
        Json::Value message;
		
        message[OperationParam::PlayerStatisticEventServiceEvents.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonData);
		
		ServerCall * sc = new ServerCall( ServiceName::PlayerStatisticsEvent, ServiceOperation::TriggerMultiple, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
    }
	
}