// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudFile
    {
    public:
        BrainCloudFile(BrainCloudClient* in_client);

        /**
         * Prepares a user file upload. On success the file will begin uploading
         * to the brainCloud server. To be informed of success/failure of the upload
         * register an IFileUploadCallback with the BrainCloudClient class.
         *
         * @param in_cloudPath The desired cloud path of the file
         * @param in_cloudFilename The desired cloud filename of the file
         * @param in_shareable True if the file is shareable.
         * @param in_replaceIfExists Whether to replace file if it exists
         * @param in_localPath The path and filename of the local file
         * @param in_callback The method to be invoked when the server response is received
         *
         * Significant error codes:
         *
         * 40429 - File maximum file size exceeded
         * 40430 - File exists, replaceIfExists not set
         */
        bool uploadFile(const char * in_cloudPath,
            const char * in_cloudFilename,
            bool in_shareable,
            bool in_replaceIfExists,
            const char * in_localPath,
            IServerCallback * in_callback = NULL);

        /**
         * List all user files
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void listUserFiles(IServerCallback * in_callback = NULL);

        /**
         * List user files from the given cloud path
         *
         * @param in_cloudPath File path
         * @param in_recurse Whether to recurse into sub-directories
         * @param in_callback The method to be invoked when the server response is received
         */
        void listUserFiles(const char * in_cloudPath, bool in_recurse, IServerCallback * in_callback = NULL);

        /**
         * Deletes a single user file.
         *
         * @param in_cloudPath File path
         * @param in_cloudFilename name of file
         * @param in_callback The method to be invoked when the server response is received
         *
         * Significant error codes:
         *
         * 40431 - Cloud storage service error
         * 40432 - File does not exist
         *
         */
        void deleteUserFile(const char * in_cloudPath, const char * in_cloudFilename, IServerCallback * in_callback = NULL);

        /**
         * Delete multiple user files
         *
         * @param in_cloudPath File path
         * @param in_recurse Whether to recurse into sub-directories
         * @param in_callback The method to be invoked when the server response is received
         */
        void deleteUserFiles(const char * in_cloudPath, bool in_recurse, IServerCallback * in_callback = NULL);

		/**
		* Returns the CDN url for a file object
		*
		* @param in_cloudPath File path
		* @param in_cloudFileName File name
		* @param in_callback The method to be invoked when the server response is received
		*/
		void getCDNUrl(const char * in_cloudPath, const char * in_cloudFileName, IServerCallback * in_callback = NULL);

        /**
         * Method cancels an upload. If an IFileUploadCallback has been registered with the BrainCloudClient class,
         * the fileUploadFailed callback method will be called once the upload has been canceled.
         *
         * @param in_uploadId The id of the upload
         */
        void cancelUpload(const char * in_uploadId);

        /**
         * Returns the progress of the given upload from 0.0 to 1.0
         * or -1 if upload not found.
         *
         * @param in_uploadId The id of the upload
         * @return A progress from 0.0 to 1.0 or -1 if upload not found.
         */
        double getUploadProgress(const char * in_uploadId);

        /**
         * Returns the number of bytes uploaded or -1 if upload not found.
         *
         * @param in_uploadId The id of the upload
         * @return The number of bytes uploaded or -1 if upload not found.
         */
        int64_t getUploadBytesTransferred(const char * in_uploadId);

        /**
         * Returns the total number of bytes that will be uploaded or -1 if upload not found.
         *
         * @param in_uploadId The id of the upload
         * @return The total number of bytes that will be uploaded or -1 if upload not found.
         */
        int64_t getUploadTotalBytesToTransfer(const char * in_uploadId);

    private:
        BrainCloudClient * m_client;
    };
}
