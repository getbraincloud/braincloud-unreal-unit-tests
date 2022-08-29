@ echo OFF

set PROJECT_NAME=%1
set APP_ID=%2
set SECRET_KEY=%3
set CHILD_APP_ID=%4
set CHILD_SECRET_KEY=%5
set SERVER_SECRET_KEY=%6

REM run from project root folder

cd Source\%PROJECT_NAME%


echo #pragma once >ids.h


echo #define BRAINCLOUD_SERVER_URL "https://api.internal.braincloudservers.com/dispatcherv2" >>ids.h
echo #define BRAINCLOUD_APP_ID "%APP_ID%" >>ids.h
echo #define BRAINCLOUD_APP_SECRET "%SECRET_KEY%" >>ids.h
echo #define BRAINCLOUD_APP_VERSION "1.0" >>ids.h

echo #define BRAINCLOUD_CHILD_APP_ID "%CHILD_APP_ID%" >>ids.h
echo #define BRAINCLOUD_CHILD_APP_SECRET "%CHILD_SECRET_KEY%" >>ids.h
echo #define BRAINCLOUD_PARENT_LEVEL_NAME "Master" >>ids.h
echo #define BRAINCLOUD_PEER_NAME "peerapp" >>ids.h
echo #define BRAINCLOUD_SERVER_NAME "TestServer" >>ids.h
echo #define BRAINCLOUD_SERVER_SECRET "%SERVER_SECRET_KEY%" >>ids.h
echo #define BRAINCLOUD_S2S_SERVER "https://sharedprod.braincloudservers.com/s2sdispatcher" >>ids.h

echo #define TESTFILE_SERVER_URL "" >>ids.h
echo #define TESTFILE_APP_ID "" >>ids.h
echo #define TESTFILE_APP_SECRET "" >>ids.h

echo File ids.h created in Source/%PROJECT_NAME%

type ids.h

cd ..\..
