// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudRedemptionCode
{
public:
  BrainCloudRedemptionCode(BrainCloudClient *client);

  /**
    * Redeem a code.
    *
    * Service Name - RedemptionCode
    * Service Operation - REDEEM_CODE
    *
    * @param scanCode The code to redeem
    * @param codeType The type of code
    * @param customRedemptionInfo Optional - A JSON string containing custom redemption data
    * @param callback The method to be invoked when the server response is received
    */
  void redeemCode(const FString &scanCode, const FString &codeType, const FString &customRedemptionInfo, IServerCallback *callback);

  /**
    * Retrieve the codes already redeemed by player.
    *
    * Service Name - RedemptionCode
    * Service Operation - GET_REDEEMED_CODES
    *
    * @param codeType Optional - The type of codes to retrieve. Returns all codes if left unspecified.
    * @param callback The method to be invoked when the server response is received
    */
  void getRedeemedCodes(const FString &codeType, IServerCallback *callback);

private:
  BrainCloudClient *_client = nullptr;
};
