// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include <vector>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud {

    class BrainCloudClient;
    class IServerCallback;

    class BrainCloudGamification {

    public:
        BrainCloudGamification(BrainCloudClient* in_client);

        /**
         * Method retrieves all gamification data for the player.
         *
         * Service Name - Gamification
         * Service Operation - Read
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readAllGamification(bool in_includeMetaData = false, IServerCallback * in_callback = NULL);

        /**
         * Method retrieves all milestones defined for the game.
         *
         * Service Name - Gamification
         * Service Operation - ReadMilestones
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readMilestones(bool in_includeMetaData = false, IServerCallback * in_callback = NULL);

        /**
         * Read all of the achievements defined for the game.
         *
         * Service Name - Gamification
         * Service Operation - ReadAchievements
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readAchievements(bool in_includeMetaData = false, IServerCallback * in_callback = NULL);

        /**
         * Method returns all defined xp levels and any rewards associated
         * with those xp levels.
         *
         * Service Name - Gamification
         * Service Operation - ReadXpLevels
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readXpLevelsMetaData(IServerCallback * in_callback = NULL);

        /**
        * Method retrives the list of achieved achievements.
        *
        * Service Name - Gamification
        * Service Operation - ReadAchievedAchievements
        *
        * @param in_callback Method to be invoked when the server response is received.
        */
        void readAchievedAchievements(bool in_includeMetaData = false, IServerCallback * in_callback = NULL);

        /**
         * Method retrieves the list of completed milestones.
         *
         * Service Name - Gamification
         * Service Operation - ReadCompleteMilestones
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readCompletedMilestones(bool in_includeMetaData = false, IServerCallback * in_callback = NULL);

        /**
         * Method retrieves the list of in progress milestones
         *
         * Service Name - Gamification
         * Service Operation - ReadInProgressMilestones
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readInProgressMilestones(bool in_includeMetaData = false, IServerCallback * in_callback = NULL);

        /**
        * Method retrieves milestones of the given category.
        *
        * Service Name - Gamification
        * Service Operation - ReadMilestonesByCategory
        *
        * @param in_category The milestone category
        * @param in_callback Method to be invoked when the server response is received.
        */
        void readMilestonesByCategory(const char * in_category, bool in_includeMetaData = false, IServerCallback * in_callback = NULL);

        /**
        * Method will award the achievements specified.
        *
        * Service Name - Gamification
        * Service Operation - AwardAchievements
        *
        * @param in_achievementIds Collection of achievement ids to award
        * @param in_callback Method to be invoked when the server response is received.
        */
        void awardAchievements(const std::vector<std::string> & in_achievements, IServerCallback * in_callback = NULL);

        /**
         * Method retrieves all of the quests defined for the game.
         *
         * Service Name - Gamification
         * Service Operation - ReadQuests
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readQuests(bool in_includeMetaData = false, IServerCallback * callback = NULL);

        /**
         *  Method returns all completed quests.
         *
         * Service Name - Gamification
         * Service Operation - ReadCompletedQuests
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readCompletedQuests(bool in_includeMetaData = false, IServerCallback * callback = NULL);

        /**
         *  Method returns quests that are in progress.
         *
         * Service Name - Gamification
         * Service Operation - ReadInProgressQuests
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readInProgressQuests(bool in_includeMetaData = false, IServerCallback * callback = NULL);

        /**
         *  Method returns quests that have not been started.
         *
         * Service Name - Gamification
         * Service Operation - ReadNotStartedQuests
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readNotStartedQuests(bool in_includeMetaData = false, IServerCallback * callback = NULL);

        /**
         *  Method returns quests with a status.
         *
         * Service Name - Gamification
         * Service Operation - ReadQuestsWithStatus
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readQuestsWithStatus(bool in_includeMetaData = false, IServerCallback * callback = NULL);

        /**
         *  Method returns quests with a basic percentage.
         *
         * Service Name - Gamification
         * Service Operation - ReadQuestsWithBasicPercentage
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readQuestsWithBasicPercentage(bool in_includeMetaData = false, IServerCallback * callback = NULL);

        /**
         *  Method returns quests with a complex percentage.
         *
         * Service Name - Gamification
         * Service Operation - ReadQuestsWithComplexPercentage
         *
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readQuestsWithComplexPercentage(bool in_includeMetaData = false, IServerCallback * callback = NULL);

        /**
         * Method returns quests for the given category.
         *
         * Service Name - Gamification
         * Service Operation - ReadQuestsByCategory
         *
         * @param in_category The quest category
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readQuestsByCategory(const char * category, bool in_includeMetaData = false, IServerCallback * callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}