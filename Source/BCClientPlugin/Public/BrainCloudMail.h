// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudMail
{
  public:
	BrainCloudMail(BrainCloudClient *client);

	/**
	* Sends a simple text email to the specified user
	*
	* Service Name - mail
	* Service Operation - SEND_BASIC_EMAIL
	*
	* @param profileId The user to send the email to
	* @param subject The email subject
	* @param body The email body
	* @param callback The method to be invoked when the server response is received
	*/
	void sendBasicEmail(const FString &profileId, const FString &subject, const FString &body, IServerCallback *callback = nullptr);

	/**
	* Sends an advanced email to the specified user
	*
	* Service Name - mail
	* Service Operation - SEND_ADVANCED_EMAIL
	*
	* @param profileId The user to send the email to
	* @param jsonServiceParams Parameters to send to the email service. See the documentation for
	*	a full list. http://getbraincloud.com/apidocs/apiref/#capi-mail
	* @param callback The method to be invoked when the server response is received
	*/
	void sendAdvancedEmail(const FString &profileId, const FString &jsonServiceParams, IServerCallback *callback = nullptr);

	/**
	* Sends an advanced email to the specified email address
	*
	* Service Name - mail
	* Service Operation - SEND_ADVANCED_EMAIL_BY_EMAIL
	*
	* @param emailAddress The address to send the email to
	* @param jsonServiceParams Parameters to send to the email service. See the documentation for
	*	a full list. http://getbraincloud.com/apidocs/apiref/#capi-mail
	* @param callback The method to be invoked when the server response is received
	*/
	void sendAdvancedEmailByAddress(const FString &emailAddress, const FString &jsonServiceParams, IServerCallback *callback = nullptr);

  private:
	BrainCloudClient *_client = nullptr;
};