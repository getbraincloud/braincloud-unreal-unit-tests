// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BCAuthType.h"

FString BCAuthType::EnumToString(EBCAuthType type)
{
    switch (type)
    {
    case EBCAuthType::Anonymous:
        return TEXT("Anonymous");
    case EBCAuthType::Universal:
        return TEXT("Universal");
    case EBCAuthType::Email:
        return TEXT("Email");
    case EBCAuthType::Facebook:
        return TEXT("Facebook");
    case EBCAuthType::GameCenter:
        return TEXT("GameCenter");
    case EBCAuthType::Steam:
        return TEXT("Steam");
    case EBCAuthType::Google:
        return TEXT("Google");
    case EBCAuthType::Twitter:
        return TEXT("Twitter");
    case EBCAuthType::Parse:
        return TEXT("Parse");
    case EBCAuthType::External:
        return TEXT("External");
    case EBCAuthType::Unknown:
        return TEXT("Unknown");
    default:
        return TEXT("TYPE_NOT_FOUND");
    }
}
