#include "braincloud/BrainCloudWrapper.h"
#include "braincloud/internal/SaveDataHelper.h"

#define PROFILE_ID_KEY "profileId"
#define ANONYMOUS_ID_KEY "anonymousId"
#define AUTHENTICATION_TYPE_KEY "authenticationType"


namespace BrainCloud {

    BrainCloudWrapper * BrainCloudWrapper::m_instance = NULL;

    std::string BrainCloudWrapper::AUTHENTICATION_ANONYMOUS = "anonymous";


    BrainCloudWrapper::BrainCloudWrapper()
        : client(NULL)
        , m_authenticateCallback(NULL)
        , m_lastUrl("")
        , m_lastSecretKey("")
        , m_lastGameId("")
        , m_lastGameVersion("")
        , m_wrapperName("")
        , m_alwaysAllowProfileSwitch(true)
    {
    }

    BrainCloudWrapper::~BrainCloudWrapper() {
        if (this != m_instance) {
            if(client != nullptr) {
                delete client;
                client = nullptr;
            }
        }
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    BrainCloudWrapper * BrainCloudWrapper::getInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new BrainCloudWrapper();

            m_instance->client = BrainCloudClient::getInstance();
        }

        return m_instance;
    }
#pragma clang diagnostic pop


    void BrainCloudWrapper::initialize(const char * url, const char * secretKey, const char * appId, const char * version, const char * companyName, const char * appName, const char * wrapperName)
    {
        if(client == nullptr) {
            client = new BrainCloudClient();
        }

        // save the app info in case we need to reauthenticate
        m_wrapperName = wrapperName;
        m_lastUrl = url;
        m_lastSecretKey = secretKey;
        m_lastGameId = appId;
        m_lastGameVersion = version;

        // initialize the client with our app info
        client->initialize(url, secretKey, appId, version);

        // inialize the save data helper with our company and app name
        // if this is not called the profile ids will not be saved
        SaveDataHelper::getInstance()->initialize(companyName, appName, wrapperName);
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
        initialize(m_lastUrl.c_str(), m_lastSecretKey.c_str(), m_lastGameId.c_str(), m_lastGameVersion.c_str(), NULL, NULL, m_wrapperName.c_str());

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
