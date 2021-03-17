// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCAuthType.h"
#include "BCClientPluginPrivatePCH.h"

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
    case EBCAuthType::FacebookLimited:
        return TEXT("FacebookLimited");
    case EBCAuthType::Oculus:
        return TEXT("Oculus");
    case EBCAuthType::PlaystationNetwork:
        return TEXT("PlaystationNetwork");
    case EBCAuthType::GameCenter:
        return TEXT("GameCenter");
    case EBCAuthType::Steam:
        return TEXT("Steam");
    case EBCAuthType::Google:
        return TEXT("Google");
    case EBCAuthType::GoogleOpenId:
        return TEXT("GoogleOpenId");
    case EBCAuthType::Apple:
        return TEXT("Apple");
    case EBCAuthType::Twitter:
        return TEXT("Twitter");
    case EBCAuthType::Parse:
        return TEXT("Parse");
    case EBCAuthType::Handoff:
        return TEXT("Handoff");
    case EBCAuthType::SettopHandoff:
        return TEXT("SettopHandoff");
    case EBCAuthType::External:
        return TEXT("External");
    case EBCAuthType::Unknown:
        return TEXT("Unknown");
    default:
        return TEXT("TYPE_NOT_FOUND");
    }
}
