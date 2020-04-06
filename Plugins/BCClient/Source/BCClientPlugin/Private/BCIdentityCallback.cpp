// Copyright 2018 bitHeads, Inc. All Rights Reserved.
#include "BCIdentityCallback.h"
#include "BCClientPluginPrivatePCH.h"
#include "ServerCall.h"
#include "BrainCloudWrapper.h"

BCIdentityCallback::BCIdentityCallback(UBrainCloudWrapper *in_wrapper, IServerCallback *in_callback)
{
    m_wrapper = in_wrapper;
    m_callback = in_callback;
}

BCIdentityCallback::~BCIdentityCallback()
{
}

void BCIdentityCallback::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData)
{
    TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(jsonData);
    TSharedPtr<FJsonObject> jsonPacket = MakeShareable(new FJsonObject());
    bool res = FJsonSerializer::Deserialize(reader, jsonPacket);

    if (res)
    {
        TSharedPtr<FJsonObject> data = jsonPacket->GetObjectField(TEXT("data"));
        TSharedPtr<FJsonObject> identities = data->GetObjectField(TEXT("identities"));

        if (identities->Values.Num() == 0)
        {
            m_wrapper->getBCClient()->getPlayerStateService()->deleteUser(m_callback);
        }
        else
        {
            m_wrapper->getBCClient()->getPlayerStateService()->logout(m_callback);
        }

        m_wrapper->getBCClient()->insertEndOfMessageBundleMarker();
    }

    delete this;
}

void BCIdentityCallback::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
{
    m_callback->serverError(serviceName, serviceOperation, statusCode, reasonCode, jsonError);
    delete this;
}
