// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCProfanityProxy.generated.h"

UCLASS(MinimalAPI)
class UBCProfanityProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCProfanityProxy(const FObjectInitializer &ObjectInitializer);

  /**
    * Checks supplied text for profanity.
    *
    * Service Name - Profanity
    * Service Operation - ProfanityCheck
    *
    * Param - text The text to check
    * Param - languages Optional comma delimited list of two character language codes
    * Param - flagEmail Optional processing of email addresses
    * Param - flagPhone Optional processing of phone numbers
    * Param - flagUrls Optional processing of urls
    *
    * Significant error codes:
    *
    * 40421 - WebPurify not configured
    * 40422 - General exception occurred
    * 40423 - WebPurify returned an error (Http status != 200)
    * 40424 - WebPurify not enabled
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Profanity")
  static UBCProfanityProxy *ProfanityCheck(UBrainCloudWrapper *brainCloudWrapper, const FString &text, const FString &languages, bool flagEmail, bool flagPhone, bool flagUrls);

  /**
    * Replaces the characters of profanity text with a passed character(s).
    *
    * Service Name - Profanity
    * Service Operation - ProfanityReplaceText
    *
    * Param - text The text to check
    * Param - replaceSymbol The text to replace individual characters of profanity text with
    * Param - languages Optional comma delimited list of two character language codes
    * Param - flagEmail Optional processing of email addresses
    * Param - flagPhone Optional processing of phone numbers
    * Param - flagUrls Optional processing of urls
    *
    * Significant error codes:
    *
    * 40421 - WebPurify not configured
    * 40422 - General exception occurred
    * 40423 - WebPurify returned an error (Http status != 200)
    * 40424 - WebPurify not enabled
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Profanity")
  static UBCProfanityProxy *ProfanityReplaceText(UBrainCloudWrapper *brainCloudWrapper, const FString &text, const FString &replaceSymbol, const FString &languages, bool flagEmail, bool flagPhone, bool flagUrls);

  /**
    * Checks supplied text for profanity and returns a list of bad wors.
    *
    * Service Name - Profanity
    * Service Operation - ProfanityIdentifyBadWords
    *
    * Param - text The text to check
    * Param - languages Optional comma delimited list of two character language codes
    * Param - flagEmail Optional processing of email addresses
    * Param - flagPhone Optional processing of phone numbers
    * Param - flagUrls Optional processing of urls
    *
    * Significant error codes:
    *
    * 40421 - WebPurify not configured
    * 40422 - General exception occurred
    * 40423 - WebPurify returned an error (Http status != 200)
    * 40424 - WebPurify not enabled
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Profanity")
  static UBCProfanityProxy *ProfanityIdentifyBadWords(UBrainCloudWrapper *brainCloudWrapper, const FString &text, const FString &languages, bool flagEmail, bool flagPhone, bool flagUrls);
};
