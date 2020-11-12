// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudLobby.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/reason_codes.h"
#include "braincloud/ServerCall.h"
#include "braincloud/http_codes.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/IPinger.h"
#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"

#include <algorithm>
#include <iostream>
#include <memory>

static const int MAX_PING_CALLS = 4;
static const int MAX_PING_CALLS_IN_PARRALLEL = 2;

static Json::Value serializePingData(const std::map<std::string, int>& pingData)
{
	Json::Value jsonPingData;
	for (const auto& kv : pingData)
	{
		jsonPingData[kv.first] = kv.second;
	}
	return jsonPingData;
}

namespace BrainCloud
{
	BrainCloudLobby::GetRegionsForLobbiesCallback::GetRegionsForLobbiesCallback(BrainCloudLobby* pBrainCloudLobby)
		: m_pBrainCloudLobby(pBrainCloudLobby)
		, m_pExternalCallback(nullptr)
	{
	}

	void BrainCloudLobby::GetRegionsForLobbiesCallback::setExternalCallback(IServerCallback* in_callback)
	{
		m_pExternalCallback = in_callback;
	}

	void BrainCloudLobby::GetRegionsForLobbiesCallback::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const& jsonData)
	{
		m_pBrainCloudLobby->m_pingRegionsThread.stop(); // Make sure current ping process is halted so we dont accidentally fill new data inside m_pingData
		m_pBrainCloudLobby->m_pingData = {}; // Clear previous pings
		m_pBrainCloudLobby->m_pingRegions = {}; // Clear previous pings

		Json::Reader reader;
		Json::Value json;
		if (reader.parse(jsonData, json))
		{
			const auto& jsonRegionPingData = json["data"]["regionPingData"];
			if (!jsonRegionPingData.isNull())
			{
				auto regions = jsonRegionPingData.getMemberNames();
				for (const auto& regionName : regions)
				{
					const auto& jsonRegion = jsonRegionPingData[regionName];
					const auto& jsonType = jsonRegion["type"];
					const auto& target = jsonRegion["target"];
					if (target.isString() && jsonType.isString() && jsonType.asString() == "PING")
					{
						m_pBrainCloudLobby->m_pingRegions[regionName] = target.asString();
					}
				}
			}
		}

		// Call user callback
		if (m_pExternalCallback)
		{
			m_pExternalCallback->serverCallback(serviceName, serviceOperation, jsonData);
		}
	}

	void BrainCloudLobby::GetRegionsForLobbiesCallback::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, const std::string& jsonError)
	{
		if (m_pExternalCallback)
		{
			m_pExternalCallback->serverError(serviceName, serviceOperation, statusCode, reasonCode, jsonError);
		}
	}

	BrainCloudLobby::PingRegionsThread::PingRegionsThread(BrainCloudLobby* pBrainCloudLobby)
		: m_pBrainCloudLobby(pBrainCloudLobby)
	{
		m_isRunning = false;
	}

	BrainCloudLobby::PingRegionsThread::~PingRegionsThread()
	{
		stop();
	}

	bool BrainCloudLobby::PingRegionsThread::isRunning() const
	{
		return m_isRunning;
	}

	void BrainCloudLobby::PingRegionsThread::stop()
	{
		m_isRunning = false;
		m_condition.notify_one();
		if (m_thread.joinable())
		{
			m_thread.join();
		}
	}

	class ActivePing final
	{
	public:
		ActivePing(std::string region, std::string url, std::mutex* pMutex, std::condition_variable* pCondition, BrainCloudClient* pClient)
			: m_region(region)
		{
			m_ping = -1; // -1 means it's still going

			std::thread thread([this, url, pMutex, pCondition, pClient]
			{
				// Create our cross-platform pinger helper
				auto pPinger = std::unique_ptr<IPinger>(IPinger::create(pClient));

				// Ping as many times as required (MAX_PING_CALLS)
				std::vector<int> pings;
				auto fullURL = "http://" + url;
				for (int i = 0; i < MAX_PING_CALLS; ++i)
				{
					pings.push_back(pPinger->ping(fullURL));
				}

				// Sort results from faster to slowest
				std::sort(pings.begin(), pings.end());

				// Calculate the average, minus the slowest one (MAX_PING_CALLS - 1)
				int pingResult = 0;
				for (int i = 0; i < MAX_PING_CALLS - 1; ++i)
				{
					pingResult += pings[i];
				}
				pingResult /= MAX_PING_CALLS - 1;

				// Notify
				m_ping = pingResult;
				std::unique_lock<std::mutex> lock(*pMutex);
				pCondition->notify_one();
			});
			thread.detach();
		}

		bool isFinished() const
		{
			return m_ping != -1;
		}

		int getPing() const
		{
			return m_ping;
		}

		const std::string& getRegion() const
		{
			return m_region;
		}

	private:
		std::string m_region;
		std::atomic<int> m_ping;
	};

	void BrainCloudLobby::PingRegionsThread::start(const std::map<std::string, std::string>& pingRegions)
	{
		m_isRunning = true;

		m_thread = std::thread([this](std::map<std::string, std::string> regionsToPing)
		{
			std::vector<std::shared_ptr<ActivePing>> activePings;
			std::map<std::string, int> pingData;
			std::unique_lock<std::mutex> lock(m_mutex);
			while (m_isRunning)
			{
				// Make sure we have the desired active pings count in parrallel
				while (!regionsToPing.empty() && activePings.size() < MAX_PING_CALLS_IN_PARRALLEL)
				{
					auto it = regionsToPing.begin();
					auto regionName = it->first;
					auto regionURL = it->second;
					regionsToPing.erase(it);
					activePings.push_back(std::make_shared<ActivePing>(regionName, regionURL, &m_mutex, &m_condition, m_pBrainCloudLobby->m_client));
				}

				// Check for completed active pings
				for (auto it = activePings.begin(); it != activePings.end();)
				{
					auto pActivePing = *it;
					if (pActivePing->isFinished())
					{
						if (m_pBrainCloudLobby->_loggingEnabled)
						{
							std::cout << "#PING " << pActivePing->getRegion() << " = " << pActivePing->getPing() << std::endl;
						}
						pingData[pActivePing->getRegion()] = pActivePing->getPing();
						it = activePings.erase(it);
						continue;
					}
					++it;
				}

				// Check if we completed all the regions
				if (regionsToPing.empty() && activePings.empty())
				{
					m_pBrainCloudLobby->m_pingData = pingData;
					m_isRunning = false;
					break;
				}
				
				// Otherwise, wait for an active ping to complete
				if (!activePings.empty())
				{
					m_condition.wait(lock);
				}
			}
		}, pingRegions);
	}

	BrainCloudLobby::BrainCloudLobby(BrainCloudClient* in_client)
		: m_client(in_client)
		, m_getRegionsForLobbiesCallback(this)
		, m_pingRegionsThread(this)
		, m_pingCallback(nullptr)
	{
		_loggingEnabled = false;
	}

	void BrainCloudLobby::enableLogging(bool shouldEnable)
	{
		_loggingEnabled = shouldEnable;
	}

	void BrainCloudLobby::getRegionsForLobbies(const std::vector<std::string>& in_roomTypes, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyTypes.getValue()] = JsonUtil::stringVectorToJson(in_roomTypes);

		m_getRegionsForLobbiesCallback.setExternalCallback(in_callback);
		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::GetRegionsForLobbies, message, &m_getRegionsForLobbiesCallback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::pingRegions(IServerCallback* in_callback)
	{
		if (m_pingRegions.empty())
		{
			if (in_callback)
			{
				m_errorCallbackQueue.push_back({ in_callback, ServiceName::Lobby, ServiceOperation::PingRegions, HTTP_BAD_REQUEST, MISSING_REQUIRED_PARAMETER, "Required message parameter 'pingData' is missing. Please ensure PingData exists by first calling GetRegionsForLobbies and PingRegions, and waiting for response before proceeding." });
			}
			return;
		}
		if (!m_pingRegionsThread.isRunning())
		{
			m_pingCallback = in_callback;
			m_pingRegionsThread.stop();
			m_pingRegionsThread.start(m_pingRegions);
		}
		else if (in_callback)
		{
			m_errorCallbackQueue.push_back({ in_callback, ServiceName::Lobby, ServiceOperation::PingRegions, HTTP_BAD_REQUEST, MISSING_REQUIRED_PARAMETER, "'pingRegions' is already running. Please wait for callback before calling this again." });
		}
	}

	void BrainCloudLobby::runPingCallbacks()
	{
		// pingRegions callback
		if (!m_pingRegionsThread.isRunning() && m_pingCallback)
		{
			auto dataStr = serializePingData(m_pingData).toStyledString();
			if (_loggingEnabled)
			{
				std::cout << "#PING RESULTS " << dataStr << std::endl;
			}
			m_pingCallback->serverCallback(ServiceName::Lobby, ServiceOperation::PingRegions, dataStr);
			m_pingCallback = nullptr;
		}

		// Trigger delayed events
		for (auto& evt : m_errorCallbackQueue)
		{
			evt.callback->serverError(evt.serviceName, evt.serviceOperation, evt.statusCode, evt.reasonCode, evt.jsonError);
		}
		m_errorCallbackQueue.clear();
	}

	/* Returns the Ping Data collected after calling pingRegions
	 */
	const std::map<std::string, int>& BrainCloudLobby::getPingData() const
	{
		return m_pingData;
	}

	void BrainCloudLobby::createLobby(const std::string& in_lobbyType, int in_rating, const std::vector<std::string>& in_otherUserCxIds, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, const std::string& in_jsonSettings, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyType.getValue()] = in_lobbyType;
		message[OperationParam::Rating.getValue()] = in_rating;
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());
		message[OperationParam::TeamCode.getValue()] = in_teamCode;
		message[OperationParam::Settings.getValue()] = JsonUtil::jsonStringToValue(in_jsonSettings.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::CreateLobby, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::createLobbyWithPingData(const std::string& in_lobbyType, int in_rating, const std::vector<std::string>& in_otherUserCxIds, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, const std::string& in_jsonSettings, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyType.getValue()] = in_lobbyType;
		message[OperationParam::Rating.getValue()] = in_rating;
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());
		message[OperationParam::TeamCode.getValue()] = in_teamCode;
		message[OperationParam::Settings.getValue()] = JsonUtil::jsonStringToValue(in_jsonSettings.c_str());

		attachPingDataAndSend(ServiceName::Lobby, ServiceOperation::CreateLobbyWithPingData, message, in_callback);
	}

	void BrainCloudLobby::findLobby(const std::string& in_lobbyType, int in_rating, int in_maxSteps, const std::string& in_jsonAlgo, const std::string& in_jsonFilter, const std::vector<std::string>& in_otherUserCxIds, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyType.getValue()] = in_lobbyType;
		message[OperationParam::Rating.getValue()] = in_rating;
		message[OperationParam::MaxSteps.getValue()] = in_maxSteps;
		message[OperationParam::Algo.getValue()] = JsonUtil::jsonStringToValue(in_jsonAlgo.c_str());
		message[OperationParam::Filter.getValue()] = JsonUtil::jsonStringToValue(in_jsonFilter.c_str());
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());
		message[OperationParam::TeamCode.getValue()] = in_teamCode;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::FindLobby, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::findLobbyWithPingData(const std::string& in_lobbyType, int in_rating, int in_maxSteps, const std::string& in_jsonAlgo, const std::string& in_jsonFilter, const std::vector<std::string>& in_otherUserCxIds, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyType.getValue()] = in_lobbyType;
		message[OperationParam::Rating.getValue()] = in_rating;
		message[OperationParam::MaxSteps.getValue()] = in_maxSteps;
		message[OperationParam::Algo.getValue()] = JsonUtil::jsonStringToValue(in_jsonAlgo.c_str());
		message[OperationParam::Filter.getValue()] = JsonUtil::jsonStringToValue(in_jsonFilter.c_str());
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());
		message[OperationParam::TeamCode.getValue()] = in_teamCode;

		attachPingDataAndSend(ServiceName::Lobby, ServiceOperation::FindLobbyWithPingData, message, in_callback);
	}

	void BrainCloudLobby::attachPingDataAndSend(ServiceName serviceName, ServiceOperation serviceOperation, Json::Value& data, IServerCallback* callback)
	{
		if (m_pingData.empty())
		{
			if (callback)
			{
				m_errorCallbackQueue.push_back({ callback, serviceName, serviceOperation, HTTP_BAD_REQUEST, MISSING_REQUIRED_PARAMETER, "Required message parameter 'pingData' is missing. Please ensure PingData exists by first calling GetRegionsForLobbies and PingRegions, and waiting for response before proceeding." });
			}
			return;
		}

		data[OperationParam::PingData.getValue()] = serializePingData(m_pingData);

		ServerCall* sc = new ServerCall(serviceName, serviceOperation, data, callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::findOrCreateLobby(const std::string& in_lobbyType, int in_rating, int in_maxSteps, const std::string& in_jsonAlgo, const std::string& in_jsonFilter, const std::vector<std::string>& in_otherUserCxIds, const std::string& in_jsonSettings, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyType.getValue()] = in_lobbyType;
		message[OperationParam::Rating.getValue()] = in_rating;
		message[OperationParam::MaxSteps.getValue()] = in_maxSteps;
		message[OperationParam::Algo.getValue()] = JsonUtil::jsonStringToValue(in_jsonAlgo.c_str());
		message[OperationParam::Filter.getValue()] = JsonUtil::jsonStringToValue(in_jsonFilter.c_str());
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);
		message[OperationParam::Settings.getValue()] = JsonUtil::jsonStringToValue(in_jsonSettings.c_str());
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());
		message[OperationParam::TeamCode.getValue()] = in_teamCode;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::FindOrCreateLobby, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::findOrCreateLobbyWithPingData(const std::string& in_lobbyType, int in_rating, int in_maxSteps, const std::string& in_jsonAlgo, const std::string& in_jsonFilter, const std::vector<std::string>& in_otherUserCxIds, const std::string& in_jsonSettings, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyType.getValue()] = in_lobbyType;
		message[OperationParam::Rating.getValue()] = in_rating;
		message[OperationParam::MaxSteps.getValue()] = in_maxSteps;
		message[OperationParam::Algo.getValue()] = JsonUtil::jsonStringToValue(in_jsonAlgo.c_str());
		message[OperationParam::Filter.getValue()] = JsonUtil::jsonStringToValue(in_jsonFilter.c_str());
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);
		message[OperationParam::Settings.getValue()] = JsonUtil::jsonStringToValue(in_jsonSettings.c_str());
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());
		message[OperationParam::TeamCode.getValue()] = in_teamCode;

		attachPingDataAndSend(ServiceName::Lobby, ServiceOperation::FindOrCreateLobbyWithPingData, message, in_callback);
	}

	void BrainCloudLobby::getLobbyData(const std::string& in_lobbyId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::GetLobbyData, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::joinLobby(const std::string in_lobbyId, bool in_isReady, const std::string& in_extraJson, std::string in_teamCode, 
			const std::vector<std::string>& in_otherUserCxIds, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson);
		message[OperationParam::TeamCode.getValue()] = in_teamCode;
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::JoinLobby, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::joinLobbyWithPingData(const std::string in_lobbyId, bool in_isReady, const std::string& in_extraJson, std::string in_teamCode, 
			const std::vector<std::string>& in_otherUserCxIds, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson);
		message[OperationParam::TeamCode.getValue()] = in_teamCode;
		message[OperationParam::OtherUserCxIds.getValue()] = JsonUtil::stringVectorToJson(in_otherUserCxIds);

		attachPingDataAndSend(ServiceName::Lobby, ServiceOperation::JoinLobbyWithPingData, message, in_callback);
	}

	void BrainCloudLobby::leaveLobby(const std::string& in_lobbyId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::LeaveLobby, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::removeMember(const std::string& in_lobbyId, const std::string& in_cxId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::CxId.getValue()] = in_cxId;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::RemoveMember, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::sendSignal(const std::string& in_lobbyId, const std::string& in_jsonSignalData, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::SignalData.getValue()] = JsonUtil::jsonStringToValue(in_jsonSignalData.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::SendSignal, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::switchTeam(const std::string& in_lobbyId, const std::string& in_toTeamCode, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::ToTeamCode.getValue()] = in_toTeamCode;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::SwitchTeam, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::updateReady(const std::string& in_lobbyId, bool in_isReady, const std::string& in_extraJson, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::IsReady.getValue()] = in_isReady;
		message[OperationParam::ExtraJson.getValue()] = JsonUtil::jsonStringToValue(in_extraJson.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::UpdateReady, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudLobby::updateSettings(const std::string& in_lobbyId, const std::string& in_jsonSettings, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyId.getValue()] = in_lobbyId;
		message[OperationParam::Settings.getValue()] = JsonUtil::jsonStringToValue(in_jsonSettings.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::UpdateSettings, message, in_callback);
		m_client->sendRequest(sc);
	}
	
	/// <summary>
	/// Cancel this members Find, Join and Searching of Lobbies
	/// </summary>
	void BrainCloudLobby::cancelFindRequest(const std::string& in_lobbyType, const std::string& in_cxId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::LobbyType.getValue()] = in_lobbyType;
		message[OperationParam::CxId.getValue()] = in_cxId;

		ServerCall* sc = new ServerCall(ServiceName::Lobby, ServiceOperation::CancelFindRequest, message, in_callback);
		m_client->sendRequest(sc);
	}
};
