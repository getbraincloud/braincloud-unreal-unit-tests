// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#include "BCSubsystem.h"
#include "WrapperTestActor.h"
#include "BrainCloudWrapper.h"
#include "ServiceName.h"
#include "ServiceOperation.h"

// Sets default values
AWrapperTestActor::AWrapperTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_wrapper = NewObject<UBrainCloudWrapper>();
}

// Called when the game starts or when spawned
void AWrapperTestActor::BeginPlay()
{
	Super::BeginPlay();
	m_wrapper->initialize(
		"https://internal.braincloudservers.com/dispatcherv2",
		"91c3a097-4697-4787-ba1c-ff6e737ff8b3",
		"10299",
		"1.0.0");

	m_wrapper->authenticateAnonymous(this);

	FString id = m_wrapper->getStoredAnonymousId();
	UE_LOG(LogTemp, Display, TEXT("Saved Anon ID | %s"), *id);
	id = m_wrapper->getStoredProfileId();
	UE_LOG(LogTemp, Display, TEXT("Saved Profile ID | %s"), *id);
}

// Called every frame
void AWrapperTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_wrapper->runCallbacks();
}

void AWrapperTestActor::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData)
{
	if (serviceName == ServiceName::AuthenticateV2) //authenticate return handling
	{
		FString id = m_wrapper->getStoredAnonymousId();
		UE_LOG(LogTemp, Display, TEXT("Authenticated! Anon ID | %s"), *id);
		id = m_wrapper->getStoredProfileId();
		UE_LOG(LogTemp, Display, TEXT("Authenticated! Profile ID | %s"), *id);
	}
}

void AWrapperTestActor::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
{
}
