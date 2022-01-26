// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once
#include "BCAuthType.generated.h"

UENUM(BlueprintType)
enum class EBCAuthType : uint8
{
	Anonymous UMETA(DisplayName = "Anonymous"),
	Universal UMETA(DisplayName = "Universal"),
	Email UMETA(DisplayName = "Email"),
	Facebook UMETA(DisplayName = "Facebook"),
	FacebookLimited UMETA(DisplayName = "FacebookLimited"),
	Oculus UMETA(DisplayName = "Oculus"),
	PlaystationNetwork UMETA(DisplayName = "PlaystationNetwork"),
	GameCenter UMETA(DisplayName = "GameCenter"),
	Steam UMETA(DisplayName = "Steam"),
	Google UMETA(DisplayName = "Google"),
	GoogleOpenId UMETA(DisplayName = "GoogleOpenId"),
	Apple UMETA(DisplayName = "Apple"),
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

USTRUCT(BlueprintType, Category = "BrainCloud")
struct FAuthenticateAdvancedIds
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(BlueprintReadWrite)
	FString externalId = TEXT("");

	UPROPERTY(BlueprintReadWrite)
	FString authenticationToken = TEXT("");

	UPROPERTY(BlueprintReadWrite)
	FString authenticationSubType = TEXT("");

	FAuthenticateAdvancedIds() {}

	FAuthenticateAdvancedIds(FString in_externalId, FString in_authenticationToken, FString in_authenticationSubType)
		: externalId(in_externalId), authenticationToken(in_authenticationToken), authenticationSubType(in_authenticationSubType)
	{
	}
};