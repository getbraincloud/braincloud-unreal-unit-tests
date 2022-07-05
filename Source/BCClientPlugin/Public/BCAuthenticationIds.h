#pragma once
#include "BCAuthenticationIds.generated.h"

USTRUCT(BlueprintType, Category = "BrainCloud")
struct FAuthenticationIds
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(BlueprintReadWrite)
	FString externalId = TEXT("");

	UPROPERTY(BlueprintReadWrite)
	FString authenticationToken = TEXT("");

	UPROPERTY(BlueprintReadWrite)
	FString authenticationSubType = TEXT("");

	FAuthenticationIds() {}

	FAuthenticationIds(FString in_externalId, FString in_authenticationToken, FString in_authenticationSubType)
		: externalId(in_externalId), authenticationToken(in_authenticationToken), authenticationSubType(in_authenticationSubType)
	{
	}
};
