// Fill out your copyright notice in the Description page of Project Settings.

#include "BCSubsystem.h"
#include "BrainCloudTestActor.h"
#include "BrainCloudWrapper.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "ids.h"

// Sets default values
ABrainCloudTestActor::ABrainCloudTestActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    m_wrapper = NewObject<UBrainCloudWrapper>();
}

// Called when the game starts or when spawned
void ABrainCloudTestActor::BeginPlay()
{
    Super::BeginPlay();
    m_wrapper->initialize(
		TESTFILE_SERVER_URL,
		TESTFILE_APP_ID,
		TESTFILE_APP_SECRET,
		m_wrapper->getBCClient()->getBrainCloudClientVersion());

    m_wrapper->getBCClient()->getAuthenticationService()->authenticateUniversal("UnrealUser", "UnrealUser", true, this);
}

// Called every frame
void ABrainCloudTestActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    m_wrapper->runCallbacks();
}

void ABrainCloudTestActor::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData)
{
    if (serviceName == ServiceName::AuthenticateV2) //authenticate return handling
    {
        UE_LOG(LogTemp, Display, TEXT("Authenticated!"));

        //send our next request
        m_wrapper->getTimeService()->readServerTime(this);
    }
    else if (serviceName == ServiceName::Time) //time return handling
    {
        UE_LOG(LogTemp, Display, TEXT("Reading the time..."));

        TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(*jsonData);
        TSharedPtr<FJsonObject> jsonReadObject;
        bool result = FJsonSerializer::Deserialize(reader, jsonReadObject);

        if (result == true) //if deserializing was successful
        {
            TSharedPtr<FJsonObject> data = jsonReadObject->GetObjectField("data");
            int64 serverTime = data->GetNumberField("server_time");
            UE_LOG(LogTemp, Display, TEXT("The time is %d"), serverTime);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON!"));
        }
    }
}

void ABrainCloudTestActor::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
{
}