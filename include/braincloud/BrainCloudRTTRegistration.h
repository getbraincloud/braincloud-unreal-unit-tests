// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#ifndef _BRAINCLOUDRTTREGISTRATION_H_
#define _BRAINCLOUDRTTREGISTRATION_H_

namespace BrainCloud
{
	class BrainCloudClient;
	class IServerCallback;
	
	class BrainCloudRTTRegistration
	{
	public:
		BrainCloudRTTRegistration(BrainCloudClient* in_client);

		/**
		 * Requests the event server address
		 *
		 * @param callback The callback.
		 */
		void requestClientConnection(IServerCallback* in_callback);

	private:
		BrainCloudClient* m_client;
	};
};

#endif /* _BRAINCLOUDRTTREGISTRATION_H_ */
