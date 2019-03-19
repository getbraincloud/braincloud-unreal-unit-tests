// Fill out your copyright notice in the Description page of Project Settings.

#include "BCSubsystem.h"
#include "MessageSubsystemTestActor.h"
#include "BrainCloudClient.h"

// Sets default values
AMessageSubsystemTestActor::AMessageSubsystemTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	_subsystem = IOnlineSubsystem::Get();
	if (_subsystem)
	{
		_identity = _subsystem->GetIdentityInterface();
		_message = _subsystem->GetMessageInterface();
	}
}

// Called every frame
void AMessageSubsystemTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void AMessageSubsystemTestActor::BeginPlay()
{
	Super::BeginPlay();
	
	//#pragma warning(suppress: 4996)
	//BrainCloudClient::getInstance()->enableLogging(true);

	_identity->OnLoginCompleteDelegates->AddUObject(this, &AMessageSubsystemTestActor::LoginCallback);

	_message->OnSendMessageCompleteDelegates->AddUObject(this, &AMessageSubsystemTestActor::SendMessageCallback);
	_message->OnEnumerateMessagesCompleteDelegates->AddUObject(this, &AMessageSubsystemTestActor::EumerateMessagesCallback);
	_message->OnReadMessageCompleteDelegates->AddUObject(this, &AMessageSubsystemTestActor::ReadMessageCallback);
	_message->OnDeleteMessageCompleteDelegates->AddUObject(this, &AMessageSubsystemTestActor::DeleteMessageCallback);

	_identity->Login(0, FOnlineAccountCredentials("BrainCloud", "UnrealUser2", "UnrealUser2"));
}

void AMessageSubsystemTestActor::LoginCallback(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), (_identity->GetLoginStatus(0) == ELoginStatus::LoggedIn) ? TEXT("true") : TEXT("false"));

	TArray<TSharedRef<const FUniqueNetId>> ids;
	ids.Add(UserId.AsShared());

	FOnlineMessagePayload payload = FOnlineMessagePayload();
	FVariantData data = FVariantData();
	data.SetValue(true);
	payload.SetAttribute("test", data);

	_message->SendMessage(0, ids, TEXT("testMessage"), payload);
}

void AMessageSubsystemTestActor::SendMessageCallback(int userNum, bool wasSuccess, const FString& errorStr)
{
	UE_LOG(LogTemp, Log, TEXT("Send Message: %s"), wasSuccess ? TEXT("true") : TEXT("false"));
	_message->EnumerateMessages(0);
}

void AMessageSubsystemTestActor::EumerateMessagesCallback(int userNum, bool wasSuccess, const FString& errorStr)
{
	UE_LOG(LogTemp, Log, TEXT("EumerateMessages: %s"), wasSuccess ? TEXT("true") : TEXT("false"));

	TArray<TSharedRef<FOnlineMessageHeader>> outHeaders;
	_message->GetMessageHeaders(0, outHeaders);

	for (int32 i = 0; i < outHeaders.Num(); i++)
	{
		UE_LOG(LogTemp, Log, TEXT("Message header %d: %s"), i, *outHeaders[i]->Type);
	}

	_message->ReadMessage(0, outHeaders[0]->MessageId.Get());
}

void AMessageSubsystemTestActor::ReadMessageCallback(int userNum, bool wasSuccess, const FUniqueMessageId& messageId, const FString& errorStr)
{
	UE_LOG(LogTemp, Log, TEXT("ReadMessage: %s"), wasSuccess ? TEXT("true") : TEXT("false"));
	TSharedPtr<FOnlineMessage> message = _message->GetMessage(0, messageId);

	FVariantData data;		
	message->Payload.GetAttribute(TEXT("test"), data);

	//UE_LOG(LogTemp, Log, TEXT("Message Payload: %s | %s"), TEXT("test"), *data.GetTypeString());

	_message->DeleteMessage(0, messageId);
}

void AMessageSubsystemTestActor::DeleteMessageCallback(int userNum, bool wasSuccess, const FUniqueMessageId& messageId, const FString& errorStr)
{
	UE_LOG(LogTemp, Log, TEXT("DeleteMessage: %s"), wasSuccess ? TEXT("true") : TEXT("false"));
}

