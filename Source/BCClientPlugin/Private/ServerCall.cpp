// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "ServerCall.h"
#include "BCClientPluginPrivatePCH.h"

#include <Json.h>

//////////////////////////////////////////////////////
// (De)Constructors
//////////////////////////////////////////////////////

/**
 * Constructor
 */
ServerCall::ServerCall(ServiceName serviceName, ServiceOperation serviceOperation,
                       TSharedRef<FJsonObject> data, IServerCallback *callback /* = nullptr*/)
    : _callback(callback),
      _operation(serviceOperation),
      _service(serviceName)
{
    _data = data;
}

/**
 * Destructor
 */
ServerCall::~ServerCall()
{
}

/**
 * Spit out a JSON object tree based on the contents of this ServerCall.
 *
 * @return Json::Value
 */
TSharedRef<FJsonObject> ServerCall::getPayload()
{
    TSharedRef<FJsonObject> payload = MakeShareable(new FJsonObject());
    payload->SetStringField(TEXT("service"), _service.getValue());
    payload->SetStringField(TEXT("operation"), _operation.getValue());
    payload->SetObjectField(TEXT("data"), _data);
    return payload;
}
