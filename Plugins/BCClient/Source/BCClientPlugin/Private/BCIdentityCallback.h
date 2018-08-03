#pragma once
#include "IServerCallback.h"

class BrainCloudWrapper;
class ServiceName;
class ServiceOperation;

/**
*	Callbacks used for the smart switches
*/
class BCIdentityCallback : public IServerCallback
{
  public:
    BCIdentityCallback(BrainCloudWrapper *in_wrapper, IServerCallback *in_callback);

    virtual ~BCIdentityCallback();
    virtual void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const & jsonData);
    virtual void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString & message);
  protected:
    BrainCloudWrapper *m_wrapper;
    IServerCallback *m_callback;
};
