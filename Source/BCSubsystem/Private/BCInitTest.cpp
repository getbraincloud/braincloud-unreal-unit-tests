// Copyright 2026 bitHeads, Inc. All Rights Reserved.

#include "Misc/AutomationTest.h"
#include "BCConfigStore.h"
#include "BrainCloudClient.h"
#include "BrainCloudIdentity.h"
#include "BrainCloudWrapper.h"
#include "IServerCallback.h"
#include "ServiceName.h"
#include "ServiceOperation.h"

#if WITH_DEV_AUTOMATION_TESTS

namespace
{
	class FInitTestCallback : public IServerCallback
	{
	public:
		bool bDone = false;
		bool bSuccess = false;
		FString Response;

		void Reset()
		{
			bDone = false;
			bSuccess = false;
			Response.Empty();
		}

		virtual void serverCallback(ServiceName, ServiceOperation, const FString& JsonData) override
		{
			bDone = true;
			bSuccess = true;
			Response = JsonData;
		}

		virtual void serverError(ServiceName, ServiceOperation, int32, int32, const FString& JsonError) override
		{
			bDone = true;
			bSuccess = false;
			Response = JsonError;
		}
	};
}

// Init() signs with the app configuration in Config/BrainCloudNative.ini: the parent app on
// authentication, then the first child app after switchToChildProfile.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBCInitTest, "Project.BrainCloud.Init",
	EAutomationTestFlags::ClientContext | EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FBCInitTest::RunTest(const FString& Parameters)
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

	const TArray<FString> ChildAppIds = FBCConfigStore::ResolveChildAppIds();
	TSharedRef<FInitTestCallback> Callback = MakeShared<FInitTestCallback>();
	TSharedRef<int32> Step = MakeShared<int32>(0);
	const double Deadline = FPlatformTime::Seconds() + 60.0;

	Wrapper->authenticateUniversal(TEXT("UnrealInitTest"), TEXT("UnrealInitTest"), true, &Callback.Get());

	ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Wrapper, Callback, Step, ChildAppIds, Deadline]() -> bool
	{
		Wrapper->runCallbacks();
		if (!Callback->bDone)
		{
			if (FPlatformTime::Seconds() < Deadline)
			{
				return false;
			}
			AddError(TEXT("Timed out waiting for brainCloud."));
			Wrapper->RemoveFromRoot();
			return true;
		}

		if (*Step == 0)
		{
			if (!TestTrue(TEXT("authenticates with the parent app's signature"), Callback->bSuccess))
			{
				AddError(Callback->Response);
				Wrapper->RemoveFromRoot();
				return true;
			}
			if (ChildAppIds.Num() == 0)
			{
				AddWarning(TEXT("No child app configured, so the child app signature was not checked."));
				Wrapper->RemoveFromRoot();
				return true;
			}
			Callback->Reset();
			*Step = 1;
			Wrapper->getClient()->getIdentityService()->switchToChildProfile(TEXT(""), ChildAppIds[0], true, &Callback.Get());
			return false;
		}

		if (!TestTrue(TEXT("switches to the child app and signs with its secret"), Callback->bSuccess))
		{
			AddError(Callback->Response);
		}
		Wrapper->RemoveFromRoot();
		return true;
	}));
	return true;
}

#endif
