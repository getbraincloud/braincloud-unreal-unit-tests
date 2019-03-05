// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudFile
{
  public:
    BrainCloudFile(BrainCloudClient *client);

    /**
     * Prepares a user file upload. On success the file will begin uploading
     * to the brainCloud server. To be informed of success/failure of the upload
     * register an IFileUploadCallback with the BrainCloudClient class.
     *
     * @param cloudPath The desired cloud path of the file
     * @param cloudFilename The desired cloud filename of the file
     * @param shareable True if the file is shareable.
     * @param replaceIfExists Whether to replace file if it exists
     * @param localPath The path and filename of the local file
     * @param callback The method to be invoked when the server response is received
     * @return A bool which is false if the file cannot be found, or file size cannot be determind.
     *
     * Significant error codes:
     *
     * 40429 - File maximum file size exceeded
     * 40430 - File exists, replaceIfExists not set
     */
    bool uploadFile(
        const FString &cloudPath,
        const FString &cloudFilename,
        bool shareable,
        bool replaceIfExists,
        const FString &localPath,
        IServerCallback *callback = nullptr);

    /**
     * List all user files
     *
     * @param callback The method to be invoked when the server response is received
     */
    void listUserFiles(IServerCallback *callback = nullptr);

    /**
     * List user files from the given cloud path
     *
     * @param cloudPath File path
     * @param recurse Whether to recurse into sub-directories
     * @param callback The method to be invoked when the server response is received
     */
    void listUserFiles(const FString &cloudPath, bool recurse, IServerCallback *callback = nullptr);

    /**
     * Deletes a single user file.
     *
     * @param cloudPath File path
     * @param cloudFilename name of file
     * @param callback The method to be invoked when the server response is received
     *
     * Significant error codes:
     *
     * 40431 - Cloud storage service error
     * 40432 - File does not exist
     *
     */
    void deleteUserFile(const FString &cloudPath, const FString &cloudFilename, IServerCallback *callback = nullptr);

    /**
     * Delete multiple user files
     *
     * @param cloudPath File path
     * @param recurse Whether to recurse into sub-directories
     * @param callback The method to be invoked when the server response is received
     */
    void deleteUserFiles(const FString &cloudPath, bool recurse, IServerCallback *callback = nullptr);

    /**
	* Returns the CDN url for a file object
	*
	* @param cloudPath File path
	* @param cloudFileName File name
	* @param callback The method to be invoked when the server response is received
	*/
    void getCDNUrl(const FString &cloudPath, const FString &cloudFileName, IServerCallback *callback = nullptr);

    /**
     * Method cancels an upload. If an IFileUploadCallback has been registered with the BrainCloudClient class,
     * the fileUploadFailed callback method will be called once the upload has been canceled.
     *
     * @param uploadId The id of the upload
     */
    void cancelUpload(const FString &uploadId);

    /**
     * Returns the progress of the given upload from 0.0 to 1.0
     * or -1 if upload not found.
     *
     * @param uploadId The id of the upload
     * @return A progress from 0.0 to 1.0 or -1 if upload not found.
     */
    float getUploadProgress(const FString &uploadId);

    /**
     * Returns the number of bytes uploaded or -1 if upload not found.
     *
     * @param uploadId The id of the upload
     * @return The number of bytes uploaded or -1 if upload not found.
     */
    int32 getUploadBytesTransferred(const FString &uploadId);

    /**
     * Returns the total number of bytes that will be uploaded or -1 if upload not found.
     *
     * @param uploadId The id of the upload
     * @return The total number of bytes that will be uploaded or -1 if upload not found.
     */
    int32 getUploadTotalBytesToTransfer(const FString &uploadId);

  private:
    BrainCloudClient *_client = nullptr;
};
