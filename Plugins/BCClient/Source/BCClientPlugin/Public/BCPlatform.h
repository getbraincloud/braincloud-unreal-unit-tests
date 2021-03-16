// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

UENUM(BlueprintType)
enum class EBCPlatform : uint8
{
    GOOGLE_PLAY_ANDROID UMETA(DisplayName = "Google Play Android"),
    AMAZON_ANDROID UMETA(DisplayName = "Amazon Android"),
    BLACKBERRY UMETA(DisplayName = "BlackBerry"),
    FACEBOOK UMETA(DisplayName = "Facebook"),
    OCULUS UMETA(DisplayName = "Oculus"),
    IOS UMETA(DisplayName = "iOS"),
    LINUX_PLATFORM UMETA(DisplayName = "Linux"),
    MAC UMETA(DisplayName = "Mac"),
    WEB UMETA(DisplayName = "Web"),
    WINDOWS UMETA(DisplayName = "Windows"),
    WINDOWS_PHONE UMETA(DisplayName = "Windows Phone"),
    XBOX_360 UMETA(DisplayName = "Xbox 360"),
    PS3 UMETA(DisplayName = "PS3"),
    XBOX_ONE UMETA(DisplayName = "Xbox One"),
    PS4 UMETA(DisplayName = "PS4"),
    WATCH_OS UMETA(DisplayName = "WatchOS"),
    WII UMETA(DisplayName = "Wii"),
    PS_VITA UMETA(DisplayName = "PS Vita"),
    TIZEN UMETA(DisplayName = "Tizen"),
    ROKU UMETA(DisplayName = "Roku"),
    UNKNOWN UMETA(DisplayName = "Unknown")
};

class BCCLIENTPLUGIN_API BCPlatform
{
  public:
    static FString EnumToString(EBCPlatform platform);

  private:
    BCPlatform(){};
};