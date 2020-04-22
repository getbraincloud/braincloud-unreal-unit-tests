// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudGlobalFile
{
  public:
    BrainCloudGlobalFile(BrainCloudClient *client);

    /**
     * Returns information on a file using fileId.
     *
     * Service Name - GlobalFile
     * Service Operation - GetFileInfo
     *
     * @param - fileId - the file's id
     * @param - callback The method to be invoked when the server response is received
     */
    void getFileInfo(const FString &fileId, IServerCallback *callback);

    /**
     * Returns information on a file using path and name.
     *
     * Service Name - GlobalFile
     * Service Operation - GetFileInfoSimple
     *
     * @param - folderPath - the folder path the file is stored at
     * @param - fileId - the file's id
     * @param - callback The method to be invoked when the server response is received
     */
    void getFileInfoSimple(const FString &fileName, const FString &folderPath, IServerCallback *callback);

    /**
     * Return CDN url for file for clients that cannot handle redirect.
     *
     * Service Name - GlobalFile
     * Service Operation - GetGlobalCDNUrl
     *
     * @param - fileId - the file's id
     * @param - callback The method to be invoked when the server response is received
     */
    void getGlobalCDNUrl(const FString &fileId, IServerCallback *callback);

    /**
     * Returns a list of files.
     *
     * Service Name - GlobalFile
     * Service Operation - GetGlobalFileList
     *
     * @param - folderPath - the folder path the file is stored at
     * @param - recurse - does it recurse?
     * @param - callback The method to be invoked when the server response is received
     */
    void getGlobalFileList(const FString &folderPath, bool recurse, IServerCallback *callback);

  private:
    BrainCloudClient *_client = nullptr;
};