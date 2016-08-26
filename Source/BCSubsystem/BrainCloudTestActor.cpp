// Fill out your copyright notice in the Description page of Project Settings.

#include "BCSubsystem.h"
#include "BrainCloudClient.h"
#include "BrainCloudTestActor.h"

#include "ServiceName.h"
#include "ServiceOperation.h"

// Sets default values
ABrainCloudTestActor::ABrainCloudTestActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABrainCloudTestActor::BeginPlay()
{
    Super::BeginPlay();
    BrainCloudClient::getInstance()->initialize(
        "https://internal.braincloudservers.com/dispatcherv2", 
        "91c3a097-4697-4787-ba1c-ff6e737ff8b3", 
        "10299", 
        "1.0.0");

    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateUniversal("UnrealUser", "UnrealUser", true, this);

    //JSON TEST
    //FString writeJsonStr;
    //TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&writeJsonStr);

    //TSharedRef<FJsonObject> jsonWriteObject = MakeShareable(new FJsonObject());

    //TArray<TSharedPtr<FJsonValue>> testArray;

    //for (int16 i = 0; i < 5; i++)
    //{
    //    TSharedPtr<FJsonValue> val = MakeShareable(new FJsonValueString("test"));
    //    testArray.Add(val);
    //}

    //jsonWriteObject->SetArrayField("testArray", testArray);

    //FJsonSerializer::Serialize(jsonWriteObject, writer);
    //UE_LOG(LogTemp, Display, TEXT("%s"), *writeJsonStr);

    //FString readJsonStr = TEXT("[\"test\", \"test\", \"test\", \"test\", \"test\"]");
    //TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(readJsonStr);


    //TSharedPtr<FJsonValue> jsonReadObject;

    //bool res = FJsonSerializer::Deserialize(reader, jsonReadObject);

    //TArray<TSharedPtr<FJsonValue>> arrayDes = jsonReadObject->AsArray();

    //bool a = true;
}

// Called every frame
void ABrainCloudTestActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    BrainCloudClient::getInstance()->runCallbacks();
}

void ABrainCloudTestActor::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    if (serviceName == ServiceName::AuthenticateV2) //authenticate return handling
    {
        UE_LOG(LogTemp, Display, TEXT("Authenticated!"));

        //send our next request
        BrainCloudClient::getInstance()->getTimeService()->readServerTime(this);
    }
    else if (serviceName == ServiceName::Time) //time return handling
    {
        UE_LOG(LogTemp, Display, TEXT("Reading the time..."));

        TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(*jsonData);
        TSharedPtr<FJsonObject> jsonReadObject;
        bool result = FJsonSerializer::Deserialize(reader, jsonReadObject);

        if (result == true) //if deserializing was successful
        {
            TSharedPtr<FJsonObject> data = jsonReadObject->GetObjectField(TEXT("data"));
            int64 serverTime = data->GetNumberField(TEXT("server_time"));
            UE_LOG(LogTemp, Display, TEXT("The time is %d"), serverTime);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON!"));
        }
    }
}

void ABrainCloudTestActor::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{

}