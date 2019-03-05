// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API IRewardCallback
{
  public:
    /**
     * The rewardCallback method is invoked whenever a brainCloud server API call returns rewards data.
     *
     * @param serviceName The service that returned rewards
     * @param serviceOperation The operation that returned rewards
     * @param jsonData The rewards JSON data. The format is as follows:
     * {
     *   "status": 200,
     *   "apiRewards": [
     *     {
     *       "service": "authenticationV2",
     *       "operation": "AUTHENTICATE",
     *       "rewards": {
     *         "rewardDetails": {
     *           // the reward depending on type (see docs)
     *         }
     *       }
     *     }
     *   ]
     * }
     */
    virtual void rewardCallback(const FString &jsonData) = 0;
};
