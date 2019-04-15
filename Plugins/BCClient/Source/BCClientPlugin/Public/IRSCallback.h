// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API IRSCallback
{
  public:
    /**
     */
    virtual void rsCallback(const FString &jsonData) = 0;
};
