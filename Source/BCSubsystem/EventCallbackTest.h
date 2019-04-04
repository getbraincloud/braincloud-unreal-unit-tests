// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IEventCallback.h"
#include "IRewardCallback.h"
#include "IServerCallback.h"
#include "EventCallbackTest.generated.h"

class UBrainCloudWrapper;

UCLASS()
class BCSUBSYSTEM_API AEventCallbackTest : public AActor, public IEventCallback, public IServerCallback, public IRewardCallback
{
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    AEventCallbackTest();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError);
    // End of IServerCallback interface

    virtual void eventCallback(const FString &jsonData);
    virtual void rewardCallback(const FString &jsonData);

  private:
    UBrainCloudWrapper *m_wrapper;
};
