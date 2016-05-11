#include "braincloud/ServiceName.h"

namespace BrainCloud
{
	const ServiceName ServiceName::None = ServiceName("None");

	const ServiceName ServiceName::Authenticate = ServiceName("authentication");
	const ServiceName ServiceName::AuthenticateV2 = ServiceName("authenticationV2");
	const ServiceName ServiceName::Identity = ServiceName("identity");
	const ServiceName ServiceName::Currency = ServiceName("currency");
	const ServiceName ServiceName::FriendData = ServiceName("friendData");
	const ServiceName ServiceName::HeartBeat = ServiceName("heartbeat");
	const ServiceName ServiceName::ServerTime = ServiceName("time");

	const ServiceName ServiceName::PushNotification = ServiceName("pushNotification");
	const ServiceName ServiceName::GlobalGameStatistics = ServiceName("globalGameStatistics");
	const ServiceName ServiceName::PlayerStatisticsEvent = ServiceName("playerStatisticsEvent");
	const ServiceName ServiceName::Twitter = ServiceName("twitter");
	const ServiceName ServiceName::Steam = ServiceName("steam");

	const ServiceName ServiceName::PlayerState = ServiceName("playerState");
	const ServiceName ServiceName::Entity = ServiceName("entity");
	const ServiceName ServiceName::GlobalEntity = ServiceName("globalEntity");
	const ServiceName ServiceName::Friend = ServiceName("friend");
	const ServiceName ServiceName::Time = ServiceName("time");

	const ServiceName ServiceName::SocialLeaderboard = ServiceName("socialLeaderboard");
	const ServiceName ServiceName::Event = ServiceName("event");
	const ServiceName ServiceName::Product = ServiceName("product");
	const ServiceName ServiceName::PlayerStatistics = ServiceName("playerStatistics");
	const ServiceName ServiceName::GlobalStatistics = ServiceName("globalGameStatistics");
	const ServiceName ServiceName::AsyncMatch = ServiceName("asyncMatch");

	const ServiceName ServiceName::Script = ServiceName("script");
	const ServiceName ServiceName::MatchMaking = ServiceName("matchMaking");
	const ServiceName ServiceName::OneWayMatch = ServiceName("onewayMatch");
	const ServiceName ServiceName::PlaybackStream = ServiceName("playbackStream");
	const ServiceName ServiceName::Gamification = ServiceName("gamification");

	const ServiceName ServiceName::GlobalApp = ServiceName("globalApp");
	const ServiceName ServiceName::S3Handling = ServiceName("s3Handling");
	const ServiceName ServiceName::RedemptionCode = ServiceName("redemptionCode");
	const ServiceName ServiceName::DataStream = ServiceName("dataStream");
	const ServiceName ServiceName::Profanity = ServiceName("profanity");
	const ServiceName ServiceName::File = ServiceName("file");
	const ServiceName ServiceName::Group = ServiceName("group");

	ServiceName::ServiceName(const char * value)
	{
		_value = value;
	}

	bool ServiceName::operator== (const ServiceName& s) const
	{
		return _value == s.getValue();
	}

	void ServiceName::operator= (const ServiceName& s)
	{
		_value = s.getValue();
	}
}