// TestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "braincloud/BrainCloudClient.h"

using namespace BrainCloud;

int main()
{
	BrainCloudClient * bcc = BrainCloudClient::getInstance();
	bcc->enableLogging(true);
    return 0;
}

