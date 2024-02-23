// Copyright 2015 bitHeads, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "IServerCallback.h"
#include "IFileUploadCallback.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "FileUploadTestActor.generated.h"

#define TESTFILE_SERVER_URL ""
#define TESTFILE_APP_ID ""
#define TESTFILE_APP_SECRET ""

class UBrainCloudWrapper;

UCLASS()
class BCSUBSYSTEM_API AFileUploadTestActor : public AActor, public IServerCallback, public IFileUploadCallback
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	AFileUploadTestActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// IServerCallback interface
	void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData);
	void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError);
	// End of IServerCallback interface

	void fileUploadCompleted(const FString &fileUploadId, const FString &jsonResponse);
	void fileUploadFailed(const FString &fileUploadId, int32 statusCode, int32 reasonCode, const FString &jsonResponse);

  private:
	FString _uploadId;
	bool _isUploading = false;
	float _cancelTimer = 2.0f;
	bool _shouldCancel = true;

	UBrainCloudWrapper *m_wrapper;
};
