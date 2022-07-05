// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudGroupACL.h"
#include "BCClientPluginPrivatePCH.h"

UBrainCloudGroupACL *UBrainCloudGroupACL::CreateNewGroupACL(EAcl other, EAcl member)
{
    UBrainCloudGroupACL *newObj = NewObject<UBrainCloudGroupACL>();
    newObj->Other = other;
    newObj->Member = member;
    return newObj;
}

FString UBrainCloudGroupACL::toJsonString()
{
    FString jsonStr;
    TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonStr);
    FJsonSerializer::Serialize(toJsonObject(), writer);
    return jsonStr;
}

TSharedRef<FJsonObject> UBrainCloudGroupACL::toJsonObject()
{
    TSharedPtr<FJsonObject> object = MakeShareable(new FJsonObject());
    object->SetNumberField("other", (uint8)Other);
    object->SetNumberField("member", (uint8)Member);
    return object.ToSharedRef();
}
