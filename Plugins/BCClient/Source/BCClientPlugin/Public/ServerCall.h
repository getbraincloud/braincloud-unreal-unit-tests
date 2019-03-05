// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IServerCallback.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"

/**
 * This is a data structure representing a single message to send to the
 * server.
 */
class BCCLIENTPLUGIN_API ServerCall
{

  public:
	ServerCall(ServiceName serviceName, ServiceOperation serviceOperation, TSharedRef<FJsonObject> data, IServerCallback *callback = nullptr);
	virtual ~ServerCall();

	IServerCallback *getCallback() const { return _callback; }
	TSharedRef<FJsonObject> getPayload();
	ServiceOperation getOperation() const { return _operation; }
	ServiceName getService() const { return _service; }
	bool getIsEndOfBundle() const { return _isEndOfBundle; }
	void setIsEndOfBundle(bool isEndOfBundle) { _isEndOfBundle = isEndOfBundle; }

  private:
	IServerCallback *_callback;
	TSharedPtr<FJsonObject> _data;
	ServiceOperation _operation;
	ServiceName _service;
	bool _isEndOfBundle = false;
};
