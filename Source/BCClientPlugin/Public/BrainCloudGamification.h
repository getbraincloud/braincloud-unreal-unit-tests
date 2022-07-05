// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;
class ServiceName;
class ServiceOperation;

class BCCLIENTPLUGIN_API BrainCloudGamification
{
  public:
    BrainCloudGamification(BrainCloudClient *client);

    /**
     * Sets the achievement awarded delegate which is called anytime
     * an achievement is awarded
     */
    void setAchievementAwardedDelegate(IServerCallback *callback);

    /**
    * Method retrieves all gamification data for the player.
    *
    * Service Name - Gamification
    * Service Operation - Read
    *
    * @param callback Method to be invoked when the server response is received.
    */
    void readAllGamification(IServerCallback *callback, bool includeMetaData = false);

    /**
     * Method retrieves all milestones defined for the game.
     *
     * Service Name - Gamification
     * Service Operation - ReadMilestones
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readMilestones(IServerCallback *callback, bool includeMetaData = false);

    /**
     * Read all of the achievements defined for the game.
     *
     * Service Name - Gamification
     * Service Operation - ReadAchievements
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readAchievements(IServerCallback *callback, bool includeMetaData = false);

    /**
     * Method returns all defined xp levels and any rewards associated
     * with those xp levels.
     *
     * Service Name - Gamification
     * Service Operation - ReadXpLevels
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readXpLevelsMetaData(IServerCallback *callback);

    /**
    * Method retrives the list of achieved achievements.
    *
    * Service Name - Gamification
    * Service Operation - ReadAchievedAchievements
    *
    * @param callback Method to be invoked when the server response is received.
    */
    void readAchievedAchievements(IServerCallback *callback, bool includeMetaData = false);

    /**
     * Method retrieves the list of completed milestones.
     *
     * Service Name - Gamification
     * Service Operation - ReadCompleteMilestones
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readCompletedMilestones(IServerCallback *callback, bool includeMetaData = false);

    /**
     * Method retrieves the list of in progress milestones
     *
     * Service Name - Gamification
     * Service Operation - ReadInProgressMilestones
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readInProgressMilestones(IServerCallback *callback, bool includeMetaData = false);

    /**
    * Method retrieves milestones of the given category.
    *
    * Service Name - Gamification
    * Service Operation - ReadMilestonesByCategory
    *
    * @param category The milestone category
    * @param callback Method to be invoked when the server response is received.
    */
    void readMilestonesByCategory(const FString &category, IServerCallback *callback, bool includeMetaData = false);

    /**
    * Method will award the achievements specified. On success, this will
    * call AwardThirdPartyAchievement to hook into the client-side Achievement
    * service (ie GameCentre, Facebook etc).
    *
    * Service Name - Gamification
    * Service Operation - AwardAchievements
    *
    * @param achievementIds A list of achievement ids to award
    * @param callback Method to be invoked when the server response is received.
    */
    void awardAchievements(const TArray<FString> &achievements, IServerCallback *callback);

    void achievementAwardedCallback(ServiceName serviceName, ServiceOperation serviceOperation, const TCHAR *jsonData);

    /**
     * Method retrieves all of the quests defined for the game.
     *
     * Service Name - Gamification
     * Service Operation - ReadQuests
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readQuests(IServerCallback *callback, bool includeMetaData = false);

    /**
     *  Method returns all completed quests.
     *
     * Service Name - Gamification
     * Service Operation - ReadCompletedQuests
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readCompletedQuests(IServerCallback *callback, bool includeMetaData = false);

    /**
     *  Method returns quests that are in progress.
     *
     * Service Name - Gamification
     * Service Operation - ReadInProgressQuests
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readInProgressQuests(IServerCallback *callback, bool includeMetaData = false);

    /**
     *  Method returns quests that have not been started.
     *
     * Service Name - Gamification
     * Service Operation - ReadNotStartedQuests
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readNotStartedQuests(IServerCallback *callback, bool includeMetaData = false);

    /**
     *  Method returns quests with a status.
     *
     * Service Name - Gamification
     * Service Operation - ReadQuestsWithStatus
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readQuestsWithStatus(IServerCallback *callback, bool includeMetaData = false);

    /**
     *  Method returns quests with a basic percentage.
     *
     * Service Name - Gamification
     * Service Operation - ReadQuestsWithBasicPercentage
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readQuestsWithBasicPercentage(IServerCallback *callback, bool includeMetaData = false);

    /**
     *  Method returns quests with a complex percentage.
     *
     * Service Name - Gamification
     * Service Operation - ReadQuestsWithComplexPercentage
     *
     * @param callback Method to be invoked when the server response is received.
     */
    void readQuestsWithComplexPercentage(IServerCallback *callback, bool includeMetaData = false);

    /**
     * Method returns quests for the given category.
     *
     * Service Name - Gamification
     * Service Operation - ReadQuestsByCategory
     *
     * @param category The quest category
     * @param callback Method to be invoked when the server response is received.
     */
    void readQuestsByCategory(const FString &category, IServerCallback *callback, bool includeMetaData = false);

    // goes through JSON response to award achievements via third party (ie game centre, facebook etc).
    // notifies achievement delegate
    void checkForAchievementsToAward(ServiceName serviceName, ServiceOperation serviceOperation, const TCHAR *jsonData);

  private:
    BrainCloudClient *_client = nullptr;
    IServerCallback *m_achievementsDelegate;
};