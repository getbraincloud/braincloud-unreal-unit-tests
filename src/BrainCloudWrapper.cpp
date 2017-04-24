#include "braincloud/BrainCloudWrapper.h"
#include "braincloud/internal/SaveDataHelper.h"

#define PROFILE_ID_KEY "profileId"
#define ANONYMOUS_ID_KEY "anonymousId"
#define AUTHENTICATION_TYPE_KEY "authenticationType"


namespace BrainCloud {

    BrainCloudWrapper * BrainCloudWrapper::m_instance = NULL;

    std::string BrainCloudWrapper::AUTHENTICATION_ANONYMOUS = "anonymous";


    BrainCloudWrapper::BrainCloudWrapper()
        : m_BCClient(NULL)
        , m_authenticateCallback(NULL)
        , m_lastUrl("")
        , m_lastSecretKey("")
        , m_lastGameId("")
        , m_lastGameVersion("")
        , m_alwaysAllowProfileSwitch(true)
    {
        m_BCClient = BrainCloud::BrainCloudClient::getInstance();
    }

    BrainCloudWrapper * BrainCloudWrapper::getInstance()
    {
        if (m_instance == NULL)
        {
            m_instance = new BrainCloudWrapper();
        }

        return m_instance;
    }


    void BrainCloudWrapper::initialize(const char * url, const char * secretKey, const char * appId, const char * version, const char * companyName, const char * appName)
    {
        // save the app info in case we need to reauthenticate
        m_lastUrl = url;
        m_lastSecretKey = secretKey;
        m_lastGameId = appId;
        m_lastGameVersion = version;

        // initialize the client with our app info
        m_BCClient->initialize(url, secretKey, appId, version);

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
            anonymousId = m_BCClient->getAuthenticationService()->generateAnonymousId();
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
        m_BCClient->initializeIdentity(profileIdToAuthenticateWith.c_str(), anonymousId.c_str());
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

        m_BCClient->getAuthenticationService()->authenticateAnonymous(true, this);
    }

    void BrainCloudWrapper::authenticateEmailPassword(const char * in_email, const char * in_password, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        m_BCClient->getAuthenticationService()->authenticateEmailPassword(in_email, in_password, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateExternal(const char * in_userid, const char * in_token, const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        m_BCClient->getAuthenticationService()->authenticateExternal(in_userid, in_token, in_externalAuthName, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateFacebook(const char * in_fbUserId, const char * in_fbAuthToken, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        m_BCClient->getAuthenticationService()->authenticateFacebook(in_fbUserId, in_fbAuthToken, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateGameCenter(const char * in_gameCenterId, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        m_BCClient->getAuthenticationService()->authenticateGameCenter(in_gameCenterId, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateGoogle(const char * in_userid, const char * in_token, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        m_BCClient->getAuthenticationService()->authenticateGoogle(in_userid, in_token, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateSteam(const char * in_userid, const char * in_sessionticket, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        m_BCClient->getAuthenticationService()->authenticateSteam(in_userid, in_sessionticket, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateTwitter(const char * in_userid, const char * in_token, const char * in_secret, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        m_BCClient->getAuthenticationService()->authenticateTwitter(in_userid, in_token, in_secret, in_forceCreate, this);
    }

    void BrainCloudWrapper::authenticateUniversal(const char * in_userid, const char * in_password, bool in_forceCreate, IServerCallback * in_callback)
    {
        m_authenticateCallback = in_callback;

        initializeIdentity();

        m_BCClient->getAuthenticationService()->authenticateUniversal(in_userid, in_password, in_forceCreate, this);
    }

	void BrainCloudWrapper::reconnect(IServerCallback * in_callback)
	{
		authenticateAnonymous(in_callback);
	}

    void BrainCloudWrapper::runCallbacks()
    {
        m_BCClient->runCallbacks();
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
