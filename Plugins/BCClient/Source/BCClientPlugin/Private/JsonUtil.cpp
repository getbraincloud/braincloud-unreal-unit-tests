// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "JsonUtil.h"
#include "BCClientPluginPrivatePCH.h"

TArray<TSharedPtr<FJsonValue>> JsonUtil::commaSepStringToJsonArray(const TCHAR *str)
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;
    TArray<FString> strArray;

    FString arrayStr = str;
    arrayStr.ParseIntoArray(strArray, TEXT(","), true);

    return arrayToJsonArray(strArray);
}

TSharedPtr<FJsonValue> JsonUtil::jsonStringToActualValue(const FString &jsonString)
{
    TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(jsonString);
    TSharedPtr<FJsonValue> jsonValue;
    FJsonSerializer::Deserialize(reader, jsonValue);

    return jsonValue;
}

TSharedPtr<FJsonObject> JsonUtil::jsonStringToValue(const FString &jsonString)
{
    TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(jsonString);
    TSharedPtr<FJsonObject> jsonValue;
    FJsonSerializer::Deserialize(reader, jsonValue);

    return jsonValue;
}

TSharedPtr<FJsonObject> JsonUtil::jsonStringToValue(const TCHAR *jsonString)
{
    TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(jsonString);
    TSharedPtr<FJsonObject> jsonValue = MakeShareable(new FJsonObject());
    FJsonSerializer::Deserialize(reader, jsonValue);

    return jsonValue;
}

FString JsonUtil::jsonValueToString(const TSharedRef<FJsonObject> &jsonValue)
{
    FString jsonStr;

    TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonStr);
    FJsonSerializer::Serialize(jsonValue, writer);

    return jsonStr;
}

FString JsonUtil::jsonArrayToString(const TArray<TSharedPtr<FJsonValue>> &jsonArray)
{
    FString jsonStr;

    TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonStr);
    FJsonSerializer::Serialize(jsonArray, writer);

    return jsonStr;
}

TArray<TSharedPtr<FJsonValue>> JsonUtil::arrayToJsonArray(const TArray<FString> &array)
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;

    for (int32 i = 0; i < array.Num(); i++)
    {
        jsonArray.Add(MakeShareable(new FJsonValueString(array[i])));
    }
    return jsonArray;
}

TArray<TSharedPtr<FJsonValue>> JsonUtil::arrayToJsonArray(const TArray<int32> &array)
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;

    for (int32 i = 0; i < array.Num(); i++)
    {
        jsonArray.Add(MakeShareable(new FJsonValueNumber(array[i])));
    }
    return jsonArray;
}
