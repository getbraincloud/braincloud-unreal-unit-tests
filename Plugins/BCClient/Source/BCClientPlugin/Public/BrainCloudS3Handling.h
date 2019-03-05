// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudS3Handling
{
public:
  BrainCloudS3Handling(BrainCloudClient *client);

  /*
    * Sends an array of file details and returns
    * the details of any of those files that have changed
    *
    * Service Name - S3Handling
    * Service Operation - GetUpdatedFiles
    *
    * @param category  Category of files on server to compare against
    * @param fileDetailsJson  An array of file details
    * @param callback  Instance of IServerCallback to call when the server response is received
    */
  void getUpdatedFiles(const FString &category, const FString &fileDetails, IServerCallback *callback = nullptr);

  /*
    * Retrieves the details of custom files stored on the server
    *
    * Service Name - S3Handling
    * Service Operation - GetFileList
    *
    * @param category  Category of files to retrieve
    * @param callback  Instance of IServerCallback to call when the server response is receieved
    */
  void getFileList(const FString &category, IServerCallback *callback = nullptr);

  /**
	* Returns the CDN url for a file
	*
	* @param fileId ID of file
	* @param callback The method to be invoked when the server response is received
	*/
  void getCDNUrl(const FString &fileId, IServerCallback *callback = nullptr);

private:
  BrainCloudClient *_client = nullptr;
};
