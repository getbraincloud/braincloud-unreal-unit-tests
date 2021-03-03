// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCPlatform.h"
#include "BCClientPluginPrivatePCH.h"

FString BCPlatform::EnumToString(EBCPlatform platform)
{
    switch (platform)
    {
    case EBCPlatform::GOOGLE_PLAY_ANDROID:
        return TEXT("ANG");
    case EBCPlatform::AMAZON_ANDROID:
        return TEXT("Amazon");
    case EBCPlatform::BLACKBERRY:
        return TEXT("BB");
    case EBCPlatform::FACEBOOK:
        return TEXT("FB");
    case EBCPlatform::OCULUS:
        return TEXT("Oculus");
    case EBCPlatform::IOS:
        return TEXT("IOS");
    case EBCPlatform::LINUX_PLATFORM:
        return TEXT("LINUX");
    case EBCPlatform::MAC:
        return TEXT("MAC");
    case EBCPlatform::WEB:
        return TEXT("WEB");
    case EBCPlatform::WINDOWS:
        return TEXT("WINDOWS");
    case EBCPlatform::WINDOWS_PHONE:
        return TEXT("WINP");
    case EBCPlatform::XBOX_360:
        return TEXT("XBOX_360");
    case EBCPlatform::PS3:
        return TEXT("PS3");
    case EBCPlatform::XBOX_ONE:
        return TEXT("XBOX_ONE");
    case EBCPlatform::PS4:
        return TEXT("PS4");
    case EBCPlatform::WATCH_OS:
        return TEXT("WATCH_OS");
    case EBCPlatform::WII:
        return TEXT("WII");
    case EBCPlatform::PS_VITA:
        return TEXT("PS_VITA");
    case EBCPlatform::TIZEN:
        return TEXT("TIZEN");
    case EBCPlatform::ROKU:
        return TEXT("ROKU");
    case EBCPlatform::UNKNOWN:
        return TEXT("UNKNOWN");
    }
    return TEXT("TYPE_NOT_FOUND");
}
