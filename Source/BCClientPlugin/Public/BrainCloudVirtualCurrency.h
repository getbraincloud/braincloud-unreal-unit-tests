// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudVirtualCurrency
{
  public:
    BrainCloudVirtualCurrency(BrainCloudClient *client);

    /**
    * Retrieve the user's currency account. Optional parameters: vcId (if retrieving all currencies).
    *
    * Service Name - VirtualCurrency
    * Service Operation - GetCurrency
    *
    * @param vcId
    * @param in_callback The method to be invoked when the server response is received
    */
    void getCurrency(const FString &in_vcId, IServerCallback *callback = nullptr);

    /**
    * Retrieve the parent user's currency account. Optional parameters: vcId (if retrieving all currencies).
    *
    * Service Name - VirtualCurrency
    * Service Operation - GetParentCurrency
    *
    * @param vcId
    * @param levelName
    * @param in_callback The method to be invoked when the server response is received
    */
    void getParentCurrency(const FString &in_vcId, const FString &in_levelName, IServerCallback *callback = nullptr);

    /**
    * Retrieve the peer user's currency account. Optional parameters: vcId (if retrieving all currencies).
    *
    * Service Name - VirtualCurrency
    * Service Operation - GetPeerCurrency
    *
    * @param vcId
    * @param peerCode
    * @param in_callback The method to be invoked when the server response is received
    */
    void getPeerCurrency(const FString &in_vcId, const FString &in_peerCode, IServerCallback *callback = nullptr);

    /**
    * Reset the player's currency to 0. 
    *
    * Service Name - VirtualCurrency
    * Service Operation - ResetCurrency
    * 
    * @param in_callback The method to be invoked when the server response is received
    */
    void resetCurrency(IServerCallback *callback = nullptr);

    /**
	* @warning Method is recommended to be used in Cloud Code only for security
	*
	* For security reasons calling this API from the client is not recommended, and is rejected at the server by default. To over-ride, enable the 'Allow Currency Calls from Client" compatibility setting in the Design Portal.
	*/
    void awardCurrency(const FString &currencyType, int32 amount, IServerCallback *callback);

    /**
	* @warning Method is recommended to be used in Cloud Code only for security
	*
	* For security reasons calling this API from the client is not recommended, and is rejected at the server by default. To over-ride, enable the 'Allow Currency Calls from Client" compatibility setting in the Design Portal.
	*/
    void consumeCurrency(const FString &currencyType, int32 amount, IServerCallback *callback);

  private:
    BrainCloudClient *_client = nullptr;
};
