// Copyright 2018 bitHeads, Inc. All Rights Reserved.
#pragma once

UENUM(BlueprintType)
enum class EAcl : uint8
{
    NONE UMETA(DisplayName = "None"),
    READ_ONLY UMETA(DisplayName = "Read Only"),
    READ_WRITE UMETA(DisplayName = "Read-Write")
};

class BCCLIENTPLUGIN_API IAcl
{
  public:
    virtual ~IAcl() {}
    virtual FString toJsonString() = 0;
    virtual TSharedRef<FJsonObject> toJsonObject() = 0;
};
