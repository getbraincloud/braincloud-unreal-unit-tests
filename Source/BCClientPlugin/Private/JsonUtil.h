// Copyright 2018 bitHeads, Inc. All Rights Reserved.
#pragma once

#include <Json.h>

class BCCLIENTPLUGIN_API JsonUtil
{
  public:
    static TArray<TSharedPtr<FJsonValue>> commaSepStringToJsonArray(const TCHAR *str);
    static TSharedPtr<FJsonValue> jsonStringToActualValue(const FString &jsonString);
    static TSharedPtr<FJsonObject> jsonStringToValue(const FString &jsonString);
    static TSharedPtr<FJsonObject> jsonStringToValue(const TCHAR *jsonString);
    static FString jsonValueToString(const TSharedRef<FJsonObject> &jsonValue);
    static FString jsonArrayToString(const TArray<TSharedPtr<FJsonValue>> &jsonArray);
    static TArray<TSharedPtr<FJsonValue>> arrayToJsonArray(const TArray<FString> &array);
    static TArray<TSharedPtr<FJsonValue>> arrayToJsonArray(const TArray<int32> &array);
};
