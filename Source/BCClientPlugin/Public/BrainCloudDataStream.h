// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;
class IAcl;

class BCCLIENTPLUGIN_API BrainCloudDataStream
{
public:
  BrainCloudDataStream(BrainCloudClient *client);

  /**
     * Creates custom data stream page event
     *
     * @param eventName Name of event
     * @param jsonEventProperties Properties of event
     * @param callback The callback object
     */
  void customPageEvent(const FString &eventName, const FString &jsonEventProperties, IServerCallback *callback = nullptr);

  /**
     * Creates custom data stream screen event
     *
     * @param eventName Name of event
     * @param jsonEventProperties Properties of event
     * @param callback The callback object
     */
  void customScreenEvent(const FString &eventName, const FString &jsonEventProperties, IServerCallback *callback = nullptr);

  /**
     * Creates custom data stream track event
     *
     * @param eventName Name of event
     * @param jsonEventProperties Properties of event
     * @param callback The callback object
     */
  void customTrackEvent(const FString &eventName, const FString &jsonEventProperties, IServerCallback *callback = nullptr);

    /**
     * Send crash report
     *
     * @param crashType String the type of crash
     * @param errosMsg String the message to send
     * @param crashJson Json the fields of the crash
     * @param crashLog String log data
     * @param userName
     * @param userEmail
     * @param userNotes
     * @param userSubmitted
     * @param callback The callback object
     */
  void submitCrashReport(const FString &crashType, const FString &errorMsg, const FString &crashJson, const FString &crashLog, const FString &userName, const FString &userEmail, const FString &userNotes, bool userSubmitted, IServerCallback *callback = nullptr);


private:
  BrainCloudClient *_client = nullptr;
};