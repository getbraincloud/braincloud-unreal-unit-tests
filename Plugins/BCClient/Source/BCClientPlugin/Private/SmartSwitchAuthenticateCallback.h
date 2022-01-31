#pragma once
#include <BCAuthenticationIds.h>

#include "BCIdentityCallback.h"
#include "IServerCallback.h"
#include "BCAuthType.h"

class UBrainCloudWrapper;
class ServiceName;
class ServiceOperation;

/**
*	Callbacks used for the smart switches
*/
class SmartSwitchAuthenticateCallback : public BCIdentityCallback
{
public:
  SmartSwitchAuthenticateCallback(UBrainCloudWrapper *in_wrapper, EBCAuthType in_authType, const FString &in_userId,
                                  const FString &in_token, bool forceCreate, IServerCallback *in_callback);

  SmartSwitchAuthenticateCallback(UBrainCloudWrapper *in_wrapper, EBCAuthType in_authType, const FString &in_userId,
                                  const FString &in_token, const FString &in_extraStringDetail, bool forceCreate, IServerCallback *in_callback);

  SmartSwitchAuthenticateCallback(UBrainCloudWrapper *in_wrapper, EBCAuthType in_authType, const FAuthenticationIds in_ids,
  								  const FString &in_extraStringDetail, bool forceCreate, IServerCallback *in_callback);
	
  virtual ~SmartSwitchAuthenticateCallback();
  virtual void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const &jsonData) override;
  virtual void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &message) override;

private:
  FString m_userId;
  FString m_token;
  FString m_extraStringDetail;
  FAuthenticationIds m_ids;
  EBCAuthType m_authType;
  bool m_forceCreate;
  bool m_advancedCallback;
};
