// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IServerCallback.h"
#include "BrainCloudTestActor.generated.h"

UCLASS()
class BCSUBSYSTEM_API ABrainCloudTestActor : public AActor, public IServerCallback
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrainCloudTestActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
