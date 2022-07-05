// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudACL.h"
#include "BCClientPluginPrivatePCH.h"

UBrainCloudACL *UBrainCloudACL::CreateNewACL(EAcl access)
{
    UBrainCloudACL *newObj = NewObject<UBrainCloudACL>();
    newObj->Other = access;
    return newObj;
}

FString UBrainCloudACL::toJsonString()
{
    FString jsonStr;
    TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonStr);
    FJsonSerializer::Serialize(toJsonObject(), writer);
    return jsonStr;
}

TSharedRef<FJsonObject> UBrainCloudACL::toJsonObject()
{
    TSharedPtr<FJsonObject> object = MakeShareable(new FJsonObject());
    object->SetNumberField("other", (uint8)Other);
    return object.ToSharedRef();
}
