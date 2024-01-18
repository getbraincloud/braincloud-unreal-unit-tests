// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#include "FileUploadTestActor.h"
#include "BCSubsystem.h"
#include "BrainCloudWrapper.h"
#include "ServiceName.h"
#include "ServiceOperation.h"

// Sets default values
AFileUploadTestActor::AFileUploadTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_wrapper = NewObject<UBrainCloudWrapper>();
}

// Called when the game starts or when spawned
void AFileUploadTestActor::BeginPlay()
{
	Super::BeginPlay();
	m_wrapper->initialize(
		TESTFILE_SERVER_URL,
		TESTFILE_APP_ID,
		TESTFILE_APP_SECRET,
		m_wrapper->getBCClient()->getBrainCloudClientVersion());

	BrainCloudClient *bcClient = m_wrapper->getBCClient();
	bcClient->enableLogging(true);
	bcClient->registerFileUploadCallback(this);
	bcClient->getAuthenticationService()->authenticateUniversal("UnrealUser", "UnrealUser", true, this);
}

// Called every frame
void AFileUploadTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_wrapper->runCallbacks();

	BrainCloudClient *bcClient = m_wrapper->getBCClient();

	if (_isUploading)
	{
		BrainCloudFile *bcFile = bcClient->getFileService();
		double progress = bcFile->getUploadProgress(_uploadId);
		int32 uploadedBytes = bcFile->getUploadBytesTransferred(_uploadId);
		int32 totalBytes = bcFile->getUploadTotalBytesToTransfer(_uploadId);
		UE_LOG(LogTemp, Display, TEXT("Progress | %f | %d/%d"), progress, uploadedBytes, totalBytes);

		if (_shouldCancel)
		{
			if (_cancelTimer <= 0.0f)
			{
				bcFile->cancelUpload(_uploadId);
				_shouldCancel = false;
			}
			else
				_cancelTimer -= DeltaTime;
		}
	}
}

void AFileUploadTestActor::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData)
{
	if (serviceName == ServiceName::AuthenticateV2) //authenticate return handling
	{
		UE_LOG(LogTemp, Display, TEXT("Authenticated! Seinding upload request..."));

		//send our next request
		m_wrapper->getFileService()->uploadFile("", "testUnreal", true, true, "C:/Users/bradleyh/Pictures/deepField_med.jpg", this);
	}
	else if (serviceName == ServiceName::File) //File return handling
	{
		UE_LOG(LogTemp, Display, TEXT("Prepare upload complete: \n%s"), *jsonData);

		TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(*jsonData);
		TSharedPtr<FJsonObject> jsonReadObject;
		bool result = FJsonSerializer::Deserialize(reader, jsonReadObject);

		if (result == true) //if deserializing was successful
		{
			TSharedPtr<FJsonObject> data = jsonReadObject->GetObjectField(TEXT("data"));
			_uploadId = data->GetObjectField(TEXT("fileDetails"))->GetStringField(TEXT("uploadId"));
			_isUploading = true;
		}
	}
}

void AFileUploadTestActor::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
{
	UE_LOG(LogTemp, Display, TEXT("Server error: \n%s"), *jsonError);
}

void AFileUploadTestActor::fileUploadCompleted(const FString &fileUploadId, const FString &jsonResponse)
{
	_isUploading = false;
	UE_LOG(LogTemp, Display, TEXT("Upload success: \n%s"), *jsonResponse);
}

void AFileUploadTestActor::fileUploadFailed(const FString &fileUploadId, int32 statusCode, int32 reasonCode, const FString &jsonResponse)
{
	_isUploading = false;
	UE_LOG(LogTemp, Error, TEXT("Upload failed: \n%s"), *jsonResponse);
}