// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API ServiceName
{
public:
  static const ServiceName None;

  static const ServiceName AuthenticateV2;
  static const ServiceName Identity;
  static const ServiceName Currency;
  static const ServiceName FriendData;
  static const ServiceName HeartBeat;

  static const ServiceName PushNotification;
  static const ServiceName GlobalGameStatistics;
  static const ServiceName PlayerStatisticsEvent;
  static const ServiceName Presence;
  static const ServiceName Twitter;
  static const ServiceName Steam;

  static const ServiceName PlayerState;
  static const ServiceName Entity;
  static const ServiceName GlobalEntity;
  static const ServiceName Friend;
  static const ServiceName Time;
  static const ServiceName Tournament;
  static const ServiceName VirtualCurrency;
  static const ServiceName AppStore;

  static const ServiceName Leaderboard;
  static const ServiceName Event;
  static const ServiceName Product;
  static const ServiceName PlayerStatistics;
  static const ServiceName GlobalStatistics;
  static const ServiceName AsyncMatch;

  static const ServiceName Script;
  static const ServiceName MatchMaking;
  static const ServiceName OneWayMatch;
  static const ServiceName PlaybackStream;
  static const ServiceName Gamification;

  static const ServiceName GlobalApp;
  static const ServiceName S3Handling;
  static const ServiceName RedemptionCode;
  static const ServiceName DataStream;
  static const ServiceName Profanity;
  static const ServiceName File;
  static const ServiceName Group;
  static const ServiceName Mail;

  // RTT
  static const ServiceName RTTRegistration;
  static const ServiceName RTT;
  static const ServiceName Chat;
  static const ServiceName Messaging;
  static const ServiceName Lobby;

  FString getValue() const { return _value; }

  bool operator==(const ServiceName &s) const;
  void operator=(const ServiceName &s);

private:
  ServiceName(const FString &value);

  FString _value;
};
