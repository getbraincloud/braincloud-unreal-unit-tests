//
//  ServerCall.cpp
//  BrainCloudLib
//


#include <sstream>
#include "braincloud/BrainCloudClient.h"
#include "braincloud/ServerCall.h"


namespace BrainCloud {

    //////////////////////////////////////////////////////
    // (De)Constructors
    //////////////////////////////////////////////////////

    ServerCall::ServerCall()
    : _service(ServiceName::None)
    , _operation(ServiceOperation::None)
    , _callback(NULL)
    {
    }
    
    /**
     * Constructor
     */
    ServerCall::ServerCall( ServiceName serviceName, ServiceOperation serviceOperation, const Json::Value & data, IServerCallback * callback )
        : _operation(serviceOperation), _service(serviceName), _callback(callback), _data(data)
	{

    }

    /**
     * Destructor
     */
    ServerCall::~ServerCall( ) 
	{
    }

    //////////////////////////////////////////////////////
    // Public methods
    //////////////////////////////////////////////////////

    /**
     * Spit out a JSON object tree based on the contents of this ServerCall.
     *
     * @return Json::Value
     */
	const Json::Value * ServerCall::getPayload( )
	{
		_payload["service"] = _service.getValue();
		_payload["operation"] = _operation.getValue();
		_payload["data"] = _data;
		return &_payload;
    }

    //////////////////////////////////////////////////////
    // Protected methods
    //////////////////////////////////////////////////////

    //////////////////////////////////////////////////////
    // Private methods
    //////////////////////////////////////////////////////


}  // end namespace
