// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <stddef.h>

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudS3Handling
    {
    public:
        BrainCloudS3Handling(BrainCloudClient* in_client);

        /*
         * Sends an array of file details and returns
         * the details of any of those files that have changed
         *
         * Service Name - S3Handling
         * Service Operation - GetUpdatedFiles
         *
         * @param in_category  Category of files on server to compare against
         * @param in_fileDetailsJson  An array of file details
         * @param in_callback  Instance of IServerCallback to call when the server response is received
         */
        void getUpdatedFiles(const char * in_category, const char * in_fileDetails, IServerCallback * in_callback = NULL);

        /*
         * Retrieves the details of custom files stored on the server
         *
         * Service Name - S3Handling
         * Service Operation - GetFileList
         *
         * @param in_category  Category of files to retrieve
         * @param in_callback  Instance of IServerCallback to call when the server response is receieved
         */
        void getFileList(const char * in_category, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}