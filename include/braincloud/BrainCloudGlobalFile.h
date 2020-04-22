// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <stddef.h>
#include <string>

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudGlobalFile
    {
    public:
        BrainCloudGlobalFile(BrainCloudClient* in_client);

        /**
         * Returns the complete info for the specified file given it’s fileId
         *
         * Service Name - GlobalFileV3
         * Service Operation - GetFileInfo
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void getFileInfo(const std::string& in_fileId, IServerCallback* in_callback = NULL);

        /**
         * Returns the complete info for the specified file, without having to look up the fileId first.
         *
         * Service Name - GlobalFileV3
         * Service Operation - GetFileInfoSimple
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void getFileInfoSimple(const std::string& in_folderPath, const std::string& in_filename, IServerCallback* in_callback = NULL);

        /**
         * Returns the CDN of the specified file.
         *
         * Service Name - GlobalFileV3
         * Service Operation - GetGlobalCDNUrl
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void getGlobalCDNUrl(const std::string& in_fileId, IServerCallback* in_callback = NULL);

        /**
         * Returns files at the current path.
         *
         * Service Name - GlobalFileV3
         * Service Operation - GetGlobalFileList
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void getGlobalFileList(const std::string& in_folderPath, bool in_recurse, IServerCallback* in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}