// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCScriptProxy.generated.h"

UCLASS(MinimalAPI)
class UBCScriptProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCScriptProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Executes a script on the server.
    *
    * Service Name - Script
    * Service Operation - Run
    *
    * Param - scriptName The name of the script to be run
    * Param - jsonScriptData Data to be sent to the script in json format
    * @see The API documentation site for more details on cloud code
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Cloud Script")
        static UBCScriptProxy* RunScript(FString scriptName, FString jsonScriptData);

    /**
    * Allows cloud script executions to be scheduled
    *
    * Service Name - Script
    * Service Operation - ScheduleCloudScript
    *
    * Param - scriptName The name of the script to be run
    * Param - jsonScriptData Data to be sent to the script in json format
    * Param - startDateInUTC The start date as a time struct
    * @see The API documentation site for more details on cloud code
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Cloud Script")
        static UBCScriptProxy* ScheduleRunScriptUTC(FString scriptName, FString jsonScriptData, FDateTime startDateInUTC);

    /**
    * Allows cloud script executions to be scheduled
    *
    * Service Name - Script
    * Service Operation - ScheduleCloudScript
    *
    * Param - scriptName The name of the script to be run
    * Param - jsonScriptData Data to be sent to the script in json format
    * Param - minutesFromNow Number of minutes from now to run script
    * @see The API documentation site for more details on cloud code
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Cloud Script")
        static UBCScriptProxy* ScheduleRunScriptMinutes(FString scriptName, FString jsonScriptData, int32 minutesFromNow);

    /**
    * Run a cloud script in a parent app
    *
    * Service Name - Script
    * Service Operation - RUN_PARENT_SCRIPT
    *
    * Param - scriptName The name of the script to be run
    * Param - scriptData Data to be sent to the script in json format
    * Param - parentLevel The level name of the parent to run the script from
    * @see The API documentation site for more details on cloud code
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Cloud Script")
        static UBCScriptProxy* RunParentScript(FString scriptName, FString jsonScriptData, FString parentLevel);

	/**
	* Cancels a scheduled cloud code script
	*
	* Service Name - Script
	* Service Operation - CANCEL_SCHEDULED_SCRIPT
	*
	* Param - jobId ID of script job to cancel
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Cloud Script")
		static UBCScriptProxy* CancelScheduledScript(const FString& jobId);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
