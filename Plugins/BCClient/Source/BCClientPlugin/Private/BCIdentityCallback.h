#pragma once
#include "IServerCallback.h"

class UBrainCloudWrapper;
class ServiceName;
class ServiceOperation;

/**
*	Callbacks used for the smart switches
*/
class BCIdentityCallback : public IServerCallback
{
public:
  BCIdentityCallback(UBrainCloudWrapper *in_wrapper, IServerCallback *in_callback);

  virtual ~BCIdentityCallback();
  virtual void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const &jsonData);
  virtual void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &message);

protected:
  UBrainCloudWrapper *m_wrapper;
  IServerCallback *m_callback;
};
