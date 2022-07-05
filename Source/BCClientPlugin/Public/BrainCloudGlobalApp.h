// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudGlobalApp
{
  public:
    BrainCloudGlobalApp(BrainCloudClient *client);

    /**
     * Read game's global properties
     *
     * Service Name - GlobalApp
     * Service Operation - ReadProperties
     *
     * @param - callback The method to be invoked when the server response is received
     */
    void readProperties(IServerCallback *callback);

	/**
	* Read game's global properties
	*
	* Service Name - GlobalApp
	* Service Operation - ReadSelectedProperties
	*
	* @param - in_propertyId Specifies which property to return
	* @param - callback The method to be invoked when the server response is received
	*/
	void readSelectedProperties(const TArray<FString>& in_propertyId,IServerCallback *callback);

	/**
	* Read game's global properties
	*
	* Service Name - GlobalApp
	* Service Operation - ReadPropertiesInCategories
	*
	* @param - in_categories Specifies which category to return
	* @param callback - callback The method to be invoked when the server response is received
	*/
	void readPropertiesInCategories(const TArray<FString>& in_categories,IServerCallback *callback);

  private:
    BrainCloudClient *_client = nullptr;
};