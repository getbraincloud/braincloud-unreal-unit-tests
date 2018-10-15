#include "braincloud/BrainCloudWrapper.h"
#include "braincloud/internal/SaveDataHelper.h"
#include "braincloud/BrainCloudClient.h"

#define PROFILE_ID_KEY "profileId"
#define ANONYMOUS_ID_KEY "anonymousId"
#define AUTHENTICATION_TYPE_KEY "authenticationType"


namespace BrainCloud {

    BrainCloudWrapper * BrainCloudWrapper::m_instance = NULL;

    std::string BrainCloudWrapper::AUTHENTICATION_ANONYMOUS = "anonymous";


    BrainCloudWrapper::BrainCloudWrapper(const char * in_wrapperName)
        : client(NULL)
        , m_authenticateCallback(NULL)
        , m_lastUrl("")
        , m_lastSecretKey("")
        , m_lastGameId("")
        , m_lastGameVersion("")
        , m_wrapperName(in_wrapperName)
        , m_alwaysAllowProfileSwitch(true)
    {
    }

    BrainCloudWrapper::~BrainCloudWrapper() {
        if (this != m_instance) {
            if(client != NULL) {
                delete client;
                client = NULL;
            }
        }
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    BrainCloudWrapper * BrainCloudWrapper::getInstance()
    {
        if(BrainCloudClient::EnableSingletonMode == false) {
            throw std::invalid_argument(BrainCloudClient::SingletonUseErrorMessage);
        }

        if (m_instance == NULL)
        {
            m_instance = new BrainCloudWrapper();

            m_instance->client = BrainCloudClient::getInstance();
        }

        return m_instance;
    }
#pragma clang diagnostic pop


    void BrainCloudWrapper::initialize(const char * url, const char * secretKey, const char * appId, const char * version, const char * companyName, const char * appName)
    {
        if(client == NULL) {
            client = new BrainCloudClient();
        }

        // save the app info in case we need to reauthenticate
        m_lastUrl = url;
        m_lastSecretKey = secretKey;
        m_lastGameId = appId;
        m_lastGameVersion = version;

        // initialize the client with our app info
        client->initialize(url, secretKey, appId, version);

        // inialize the save data helper with our company and app name
        // if this is not called the profile ids will not be saved
        SaveDataHelper::getInstance()->initialize(companyName, appName);
    }

    void BrainCloudWrapper::initializeWithApps(const char * url, const char * in_defaultAppId, const std::map<std::string, std::string>& in_secretMap, const char * version, const char * companyName, const char * appName)
    {
        if (client == NULL)
        {
            client = new BrainCloudClient();
        }

        // Find the default secret key that matches the default app id
        std::string defaultSecretKey;
        std::map<std::string, std::string>::const_iterator it = in_secretMap.find(in_defaultAppId);
        if (it != in_secretMap.end())
        {
            defaultSecretKey = it->second;
        }

        // save the app info in case we need to reauthenticate
        m_lastUrl = url;
        m_lastSecretKey = defaultSecretKey;
        m_lastGameId = in_defaultAppId;
        m_lastGameVersion = version;

        // initialize the client with our app info
        client->initializeWithApps(url, in_defaultAppId, in_secretMap, version);

        // inialize the save data helper with our company and app name
        // if this is not called the profile ids will not be saved
        SaveDataHelper::getInstance()->initialize(companyName, appName);
    }

    void BrainCloudWrapper::initializeIdentity(bool in_isAnonymousAuth)
    {
        // check if we already have saved IDs
        std::string profileId = getStoredProfileId();
        std::string anonymousId = getStoredAnonymousId();

        // create an anonymous ID if necessary
        if ((!anonymousId.empty() && profileId.empty()) || anonymousId.empty())
        {
            anonymousId = client->getAuthenticationService()->generateAnonymousId();
            profileId = "";
            setStoredAnonymousId(anonymousId.c_str());
            setStoredProfileId(profileId.c_str());
        }

        std::string profileIdToAuthenticateWith = profileId;
        if (!in_isAnonymousAuth && m_alwaysAllowProfileSwitch)
        {
            profileIdToAuthenticateWith = "";
        }
        setStoredAuthenticationType(in_isAnonymousAuth ? AUTHENTICATION_ANONYMOUS.c_str() : "");

        // send our IDs to brainCloud
        client->initializeIdentity(profileIdToAuthenticateWith.c_str(), anonymousId.c_str());
    }

    void BrainCloudWrapper::reauthenticate()
    {
        // send our saved app info to brainCloud
        // company and app name can be NULL since they are already set
        initialize(m_lastUrl.c_str(), m_lastSecretKey.c_str(), m_lastGameId.c_str(), m_lastGameVersion.c_str(), NULL, NULL);

        std::string authType = getStoredAuthenticationType();
        if (authType == AUTHENTICATION_ANONYMOUS)
        {
            authenticateAnonymous();
        }
    }

    // authenticate the player with an anonymous id
    void BrainCloudWrapper::authenticateAnonymous(IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity(true);

        client->getAuthenticationService()->authenticateAnonymous(true, this);
    }

    void BrainCloudWrapper::authenticateEmailPassword(const char * in_email, const char * in_password, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        client->getAuthenticationService()->authenticateEmailPassword(in_email, in_password, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateExternal(const char * in_userid, const char * in_token, const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        client->getAuthenticationService()->authenticateExternal(in_userid, in_token, in_externalAuthName, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateFacebook(const char * in_fbUserId, const char * in_fbAuthToken, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        client->getAuthenticationService()->authenticateFacebook(in_fbUserId, in_fbAuthToken, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateGameCenter(const char * in_gameCenterId, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        client->getAuthenticationService()->authenticateGameCenter(in_gameCenterId, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateGoogle(const char * in_userid, const char * in_token, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        client->getAuthenticationService()->authenticateGoogle(in_userid, in_token, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateSteam(const char * in_userid, const char * in_sessionticket, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        client->getAuthenticationService()->authenticateSteam(in_userid, in_sessionticket, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateTwitter(const char * in_userid, const char * in_token, const char * in_secret, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        client->getAuthenticationService()->authenticateTwitter(in_userid, in_token, in_secret, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateUniversal(const char * in_userid, const char * in_password, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        client->getAuthenticationService()->authenticateUniversal(in_userid, in_password, in_forceCreate, this);
    }



	/**
	*	Callbacks used for the smart switches
	*/
	class IdentityCallback : public IServerCallback
	{
	public: 
		BrainCloudWrapper * wrapper;
		IServerCallback * authenticateCallback;

		IdentityCallback(BrainCloudWrapper * in_wrapper, IServerCallback * in_authenticateCallback) {
			wrapper = in_wrapper;
			authenticateCallback = in_authenticateCallback;
		}

		void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const & jsonData)
		{
			Json::Value response;
			Json::Reader reader;

			reader.parse(jsonData, response);

			Json::Value identitiesObject = response["data"]["identities"];
			std::vector<std::string> listOfIdentities = identitiesObject.getMemberNames();

			if (listOfIdentities.size()) {
				wrapper->client->getPlayerStateService()->logout();
			}
			else {
				wrapper->client->getPlayerStateService()->deleteUser ();
			}
			
			wrapper->client->insertEndOfMessageBundleMarker();
			authenticateCallback->serverCallback(serviceName, serviceOperation, jsonData);
			delete this;
		}

		void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, const std::string & jsonError)
		{
			authenticateCallback->serverError(serviceName, serviceOperation, statusCode, reasonCode, jsonError);
			delete this;
		}

		void serverWarning(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, int numRetries, const std::string & statusMessage)
		{
			authenticateCallback->serverWarning(serviceName, serviceOperation, statusCode, reasonCode, numRetries, statusMessage);
			delete this;
		}
	};

	class SmartSwitchCallback : public IServerCallback
	{
	public:
		SmartSwitchCallback(BrainCloudWrapper *in_wrapper, IServerCallback * in_callback) {
			wrapper = in_wrapper;
			callback = in_callback;
		}

		BrainCloudWrapper * wrapper;
		IServerCallback * callback;

		void clearIds() {
			wrapper->resetStoredAnonymousId();
			wrapper->resetStoredProfileId();
			wrapper->client->getAuthenticationService()->clearSavedProfileId();
		}

		void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, const std::string & jsonError)
		{
			callback->serverError(serviceName, serviceOperation, statusCode, reasonCode, jsonError);
			delete this;
		}

		void serverWarning(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, int numRetries, const std::string & statusMessage)
		{
			callback->serverWarning(serviceName, serviceOperation, statusCode, reasonCode, numRetries, statusMessage);
			delete this;
		}
	};

	void BrainCloudWrapper::smartSwitchAuthenticateEmailPassword(const char * in_email, const char * in_password, bool in_forceCreate, IServerCallback * in_callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, const char * in_email, const char * in_password, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				email = in_email;
				password = in_password;
				forceCreate = in_forceCreate;
			}

			const char * email; const char * password; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const & jsonData)
			{
				clearIds();
				wrapper->client->getAuthenticationService()->authenticateEmailPassword(email, password, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, in_email, in_password, in_forceCreate, in_callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateExternal(const char * in_userid, const char * in_token, const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, const char * in_userid, const char * in_token, const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				userid = in_userid;
				token = in_token;
				externalAuthName = in_externalAuthName;
				forceCreate = in_forceCreate;
			}

			const char * userid; const char * token; const char * externalAuthName; const char * fbAuthToken; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const & jsonData)
			{
				clearIds();
				wrapper->client->getAuthenticationService()->authenticateExternal(userid, token, externalAuthName, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, in_userid, in_token, in_externalAuthName, in_forceCreate, in_callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateFacebook(const char * in_fbUserId, const char * in_fbAuthToken, bool in_forceCreate, IServerCallback * in_callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, const char * in_fbUserId, const char * in_fbAuthToken, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				fbUserId = in_fbUserId;
				fbAuthToken = in_fbAuthToken;
				forceCreate = in_forceCreate;
			}

			const char * fbUserId; const char * fbAuthToken; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const & jsonData)
			{
				clearIds();
				wrapper->client->getAuthenticationService()->authenticateFacebook(fbUserId, fbAuthToken, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, in_fbUserId, in_fbAuthToken, in_forceCreate, in_callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateGameCenter(const char * in_gameCenterId, bool in_forceCreate, IServerCallback * in_callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, const char * in_gameCenterId, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				gameCenterId = in_gameCenterId;
				forceCreate = in_forceCreate;
			}

			const char * gameCenterId; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const & jsonData)
			{
				clearIds();
				wrapper->client->getAuthenticationService()->authenticateGameCenter(gameCenterId, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, in_gameCenterId, in_forceCreate, in_callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateGoogle(const char * in_userid, const char * in_token, bool in_forceCreate, IServerCallback * in_callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, const char * in_userid, const char * in_token, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				userid = in_userid;
				token = in_token;
				forceCreate = in_forceCreate;
			}

			const char * userid; const char * token; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const & jsonData)
			{
				clearIds();
				wrapper->client->getAuthenticationService()->authenticateGoogle(userid, token, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, in_userid, in_token, in_forceCreate, in_callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateSteam(const char * in_userid, const char * in_sessionticket, bool in_forceCreate, IServerCallback * in_callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, const char * in_userid, const char * in_sessionticket, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				userid = in_userid;
				sessionticket = in_sessionticket;
				forceCreate = in_forceCreate;
			}

			const char * userid; const char * sessionticket; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const & jsonData)
			{
				clearIds();
				wrapper->client->getAuthenticationService()->authenticateSteam(userid, sessionticket, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, in_userid, in_sessionticket, in_forceCreate, in_callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateTwitter(const char * in_userid, const char * in_token, const char * in_secret, bool in_forceCreate, IServerCallback * in_callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, const char * in_userid, const char * in_token, const char * in_secret, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				userid = in_userid;
				token = in_token;
				secret = in_secret;
				forceCreate = in_forceCreate;
			}

			const char * userid; const char * token; const char * secret; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const & jsonData)
			{
				clearIds();
				wrapper->client->getAuthenticationService()->authenticateTwitter(userid, token, secret, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, in_userid, in_token, in_secret, in_forceCreate, in_callback);
		getIdentitiesCallback(smartCallback);
	}

    void BrainCloudWrapper::smartSwitchAuthenticateUniversal(const char * in_userid, const char * in_password, bool in_forceCreate, IServerCallback * in_callback)
    {
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, const char * in_userid, const char * in_password, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				userid = in_userid;
				password = in_password;
				forceCreate = in_forceCreate;
			}

			const char * userid; const char * password; bool forceCreate;
			
			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const & jsonData)
			{
				clearIds();
				wrapper->client->getAuthenticationService()->authenticateUniversal(userid, password, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, in_userid, in_password, in_forceCreate, in_callback);
		getIdentitiesCallback(smartCallback);
    }

    void BrainCloudWrapper::getIdentitiesCallback(IServerCallback *success)
    {
		IdentityCallback *identityCallback = new IdentityCallback(this, success);
		identityCallback->authenticateCallback = success;

		if (client->isAuthenticated()) {
			client->getIdentityService()->getIdentities(identityCallback);
		}
		else {
			success->serverCallback(BrainCloud::ServiceName::AuthenticateV2, BrainCloud::ServiceOperation::Authenticate, "");
		}
    }

	void BrainCloudWrapper::reconnect(IServerCallback * in_callback)
	{
		authenticateAnonymous(in_callback);
	}

    void BrainCloudWrapper::runCallbacks()
    {
        client->runCallbacks();
    }

    std::string BrainCloudWrapper::getStoredProfileId()
    {
        return SaveDataHelper::getInstance()->readData(PROFILE_ID_KEY);
    }

    void BrainCloudWrapper::setStoredProfileId(const char * profileId)
    {
        SaveDataHelper::getInstance()->saveData(PROFILE_ID_KEY, profileId);
    }

    void BrainCloudWrapper::resetStoredProfileId()
    {
        SaveDataHelper::getInstance()->deleteData(PROFILE_ID_KEY);
    }

    std::string BrainCloudWrapper::getStoredAnonymousId()
    {
        return SaveDataHelper::getInstance()->readData(ANONYMOUS_ID_KEY);
    }

    void BrainCloudWrapper::setStoredAnonymousId(const char * anonymousId)
    {
        SaveDataHelper::getInstance()->saveData(ANONYMOUS_ID_KEY, anonymousId);
    }

    void BrainCloudWrapper::resetStoredAnonymousId()
    {
        SaveDataHelper::getInstance()->deleteData(ANONYMOUS_ID_KEY);
    }

    std::string BrainCloudWrapper::getStoredAuthenticationType()
    {
        return SaveDataHelper::getInstance()->readData(AUTHENTICATION_TYPE_KEY);
    }

    void BrainCloudWrapper::setStoredAuthenticationType(const char * authenticationType)
    {
        SaveDataHelper::getInstance()->saveData(AUTHENTICATION_TYPE_KEY, authenticationType);
    }

    void BrainCloudWrapper::resetStoredAuthenticationType()
    {
        SaveDataHelper::getInstance()->deleteData(AUTHENTICATION_TYPE_KEY);
    }


    void BrainCloudWrapper::setAlwaysAllowProfileSwitch(bool in_alwaysAllow)
    {
        m_alwaysAllowProfileSwitch = in_alwaysAllow;
    }

    bool BrainCloudWrapper::getAlwaysAllowProfileSwitch()
    {
        return m_alwaysAllowProfileSwitch;
    }

    void BrainCloudWrapper::serverCallback(BrainCloud::ServiceName serviceName, BrainCloud::ServiceOperation serviceOperation, std::string const & jsonData)
    {
        if (serviceName == BrainCloud::ServiceName::AuthenticateV2 && serviceOperation == BrainCloud::ServiceOperation::Authenticate)
        {
            Json::Reader reader;
            Json::Value data;
            reader.parse(jsonData, data);

            std::string profileId = data["data"]["profileId"].asString();

            if (profileId != "")
            {
                setStoredProfileId(profileId.c_str());
            }
        }

        if (m_authenticateCallback != NULL)
        {
            m_authenticateCallback->serverCallback(serviceName, serviceOperation, jsonData);
        }
    }

    void BrainCloudWrapper::serverError(BrainCloud::ServiceName serviceName,
        BrainCloud::ServiceOperation serviceOperation,
        int statusCode, int reasonCode, const std::string & message)
    {
        if (m_authenticateCallback != NULL)
        {
            m_authenticateCallback->serverError(serviceName, serviceOperation, statusCode, reasonCode, message);
        }
    }

    void BrainCloudWrapper::serverWarning(BrainCloud::ServiceName serviceName,
        BrainCloud::ServiceOperation serviceOperation,
        int statusCode, int reasonCode, int retry, const std::string & message)
    {
        if (m_authenticateCallback != NULL)
        {
            m_authenticateCallback->serverWarning(serviceName, serviceOperation, statusCode, reasonCode, retry, message);
        }
    }

}
