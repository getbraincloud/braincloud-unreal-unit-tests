// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

UENUM(BlueprintType)
enum class EBCAuthType : uint8
{
	Anonymous UMETA(DisplayName = "Anonymous"),
	Universal UMETA(DisplayName = "Universal"),
	Email UMETA(DisplayName = "Email"),
	Facebook UMETA(DisplayName = "Facebook"),
	GameCenter UMETA(DisplayName = "GameCenter"),
	Steam UMETA(DisplayName = "Steam"),
	Google UMETA(DisplayName = "Google"),
	Twitter UMETA(DisplayName = "Twitter"),
	Parse UMETA(DisplayName = "Parse"),
	Handoff UMETA(DisplayName = "Handoff"),
	SettopHandoff UMETA(DisplayName = "SettopHandoff"),
	External UMETA(DisplayName = "External"),
	Unknown UMETA(DisplayName = "Unknown")
};

class BCCLIENTPLUGIN_API BCAuthType
{
  public:
	static FString EnumToString(EBCAuthType platform);

  private:
	BCAuthType(){};
};