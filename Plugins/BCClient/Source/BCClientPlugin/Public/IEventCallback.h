// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API IEventCallback
{
  public:
    virtual ~IEventCallback() {}

    /**
    * Method called when an event is returned from brainCloud
    *
    * @param jsonData - returned data from the server
    */
    virtual void eventCallback(const FString &jsonData) = 0;
};