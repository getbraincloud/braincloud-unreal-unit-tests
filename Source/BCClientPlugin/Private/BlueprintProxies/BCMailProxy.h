// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCMailProxy.generated.h"

UCLASS(MinimalAPI)
class UBCMailProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCMailProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* Sends a simple text email to the specified player
	*
	* Service Name - mail
	* Service Operation - SEND_BASIC_EMAIL
	*
	* Param - profileId The user to send the email to
	* Param - subject The email subject
	* Param - body The email body
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Mail")
	static UBCMailProxy *SendBasicEmail(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &subject, const FString &body);

	/**
	* Sends an advanced email to the specified player
	*
	* Service Name - mail
	* Service Operation - SEND_ADVANCED_EMAIL
	*
	*Param - profileId The user to send the email to
	*Param - jsonServiceParams Parameters to send to the email service. See the documentation for
	*	a full list. http://getbraincloud.com/apidocs/apiref/#capi-mail
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Mail")
	static UBCMailProxy *SendAdvancedEmail(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &jsonServiceParams);

	/**
	* Sends an advanced email to the specified email address
	*
	* Service Name - mail
	* Service Operation - SEND_ADVANCED_EMAIL_BY_ADDRESS
	*
	*Param - emailAddress The address to send the email to
	*Param - jsonServiceParams Parameters to send to the email service. See the documentation for
	*	a full list. http://getbraincloud.com/apidocs/apiref/#capi-mail
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Mail")
	static UBCMailProxy *SendAdvancedEmailByAddress(UBrainCloudWrapper *brainCloudWrapper, const FString &emailAddress, const FString &jsonServiceParams);
};
