// Copyright 2026 bitHeads, Inc. All Rights Reserved.

#include "Misc/AutomationTest.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "BCConfigStore.h"
#include "BrainCloudAppStore.h"
#include "BrainCloudClient.h"
#include "BrainCloudWrapper.h"
#include "HttpCodes.h"
#include "IServerCallback.h"
#include "ReasonCodes.h"
#include "ServiceName.h"
#include "ServiceOperation.h"

#if WITH_DEV_AUTOMATION_TESTS

namespace
{
	class FAppStoreTestCallback : public IServerCallback
	{
	public:
		bool bDone = false;
		bool bSuccess = false;
		int32 StatusCode = 0;
		int32 ReasonCode = 0;
		FString Response;

		void Reset()
		{
			bDone = false;
			bSuccess = false;
			StatusCode = 0;
			ReasonCode = 0;
			Response.Empty();
		}

		virtual void serverCallback(ServiceName, ServiceOperation, const FString& JsonData) override
		{
			bDone = true;
			bSuccess = true;
			Response = JsonData;
		}

		virtual void serverError(ServiceName, ServiceOperation, int32 InStatusCode, int32 InReasonCode, const FString& JsonError) override
		{
			bDone = true;
			bSuccess = false;
			StatusCode = InStatusCode;
			ReasonCode = InReasonCode;
			Response = JsonError;
		}
	};

	struct FAppStoreTestStep
	{
		FString Label;
		TFunction<void(BrainCloudAppStore*, IServerCallback*)> Send;
		bool bExpectSuccess;
	};
}

// Same cases as the C# TestAppStore: GetStoreInfo and GetUserToken for xsolla, and an unknown store id.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBCAppStoreTest, "Project.BrainCloud.AppStore",
	EAutomationTestFlags::ClientContext | EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FBCAppStoreTest::RunTest(const FString& Parameters)
{
	if (FBCConfigStore::DetectState() != EBCConfigState::Ready)
	{
		AddError(FString::Printf(TEXT("No readable app configuration at %s."), *FBCConfigStore::GetConfigPath()));
		return false;
	}

	UBrainCloudWrapper* Wrapper = NewObject<UBrainCloudWrapper>();
	Wrapper->AddToRoot();
	if (!TestTrue(TEXT("init() reads the app configuration"), Wrapper->init()))
	{
		Wrapper->RemoveFromRoot();
		return false;
	}

	const TArray<FAppStoreTestStep> Steps = {
		{ TEXT("GetStoreInfo"), [](BrainCloudAppStore* Store, IServerCallback* Cb) { Store->getStoreInfo(TEXT("xsolla"), Cb); }, true },
		{ TEXT("GetStoreInfoFail"), [](BrainCloudAppStore* Store, IServerCallback* Cb) { Store->getStoreInfo(TEXT("_invalid_store_id_"), Cb); }, false },
		{ TEXT("GetUserToken"), [](BrainCloudAppStore* Store, IServerCallback* Cb) { Store->getUserToken(TEXT("xsolla"), Cb); }, true },
		{ TEXT("GetUserTokenFail"), [](BrainCloudAppStore* Store, IServerCallback* Cb) { Store->getUserToken(TEXT("_invalid_store_id_"), Cb); }, false },
	};

	TSharedRef<FAppStoreTestCallback> Callback = MakeShared<FAppStoreTestCallback>();
	TSharedRef<int32> Step = MakeShared<int32>(-1);
	TSharedRef<double> Deadline = MakeShared<double>(FPlatformTime::Seconds() + 60.0);

	Wrapper->authenticateUniversal(TEXT("UnrealAppStoreTest"), TEXT("UnrealAppStoreTest"), true, &Callback.Get());

	ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Wrapper, Callback, Step, Steps, Deadline]() -> bool
	{
		Wrapper->runCallbacks();
		if (!Callback->bDone)
		{
			if (FPlatformTime::Seconds() < *Deadline)
			{
				return false;
			}
			AddError(TEXT("Timed out waiting for brainCloud."));
			Wrapper->RemoveFromRoot();
			return true;
		}

		if (*Step < 0)
		{
			if (!TestTrue(TEXT("authenticates"), Callback->bSuccess))
			{
				AddError(Callback->Response);
				Wrapper->RemoveFromRoot();
				return true;
			}
		}
		else
		{
			const FAppStoreTestStep& Current = Steps[*Step];
			if (Current.bExpectSuccess)
			{
				if (!TestTrue(Current.Label + TEXT(" succeeds"), Callback->bSuccess))
				{
					AddError(Callback->Response);
				}
			}
			else
			{
				TestFalse(Current.Label + TEXT(" fails"), Callback->bSuccess);
				TestEqual(Current.Label + TEXT(" status code"), Callback->StatusCode, (int32)HttpCode::BAD_REQUEST);
				TestEqual(Current.Label + TEXT(" reason code"), Callback->ReasonCode, ReasonCodes::INVALID_STORE_ID);
			}
			// The user token is a live credential, so only report whether one came back.
			if (Current.Label == TEXT("GetUserToken") && Callback->bSuccess)
			{
				TSharedPtr<FJsonObject> Json;
				const TSharedPtr<FJsonObject>* Data = nullptr;
				FString Token;
				const bool bHasToken = FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Callback->Response), Json) && Json.IsValid() &&
					Json->TryGetObjectField(TEXT("data"), Data) && (*Data)->TryGetStringField(TEXT("userToken"), Token) && !Token.IsEmpty();
				AddInfo(FString::Printf(TEXT("%s: %s"), *Current.Label,
					bHasToken ? TEXT("userToken returned") : TEXT("userToken is null (check the app's Xsolla server client id, secret and login id)")));
			}
			else
			{
				AddInfo(FString::Printf(TEXT("%s: %s"), *Current.Label, *Callback->Response));
			}
		}

		*Step += 1;
		if (*Step >= Steps.Num())
		{
			Wrapper->RemoveFromRoot();
			return true;
		}
		Callback->Reset();
		*Deadline = FPlatformTime::Seconds() + 60.0;
		Steps[*Step].Send(Wrapper->getClient()->getAppStoreService(), &Callback.Get());
		return false;
	}));
	return true;
}

#endif
