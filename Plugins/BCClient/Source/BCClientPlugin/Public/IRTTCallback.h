// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API IRTTCallback
{
  public:
    /**
     */
    virtual void rttCallback(const FString &jsonData) = 0;
};
