cmake_minimum_required(VERSION 3.0)

project(brainCloud)

# Usefull flags
if (UNIX AND NOT APPLE)
    set(LINUX 1)
endif()
if (WIN32 AND MSVC AND MSVC_VERSION)
	if (MSVC_VERSION LESS 1800)
		set(VS2013_OR_HIGHER 0)
	else()
		set(VS2013_OR_HIGHER 1)
	endif()
endif()

#=============================================================================
# CMake options
#=============================================================================
option(USE_CPPREST "Use CPPREST instead of CURL (Ignored in VS2013+)" OFF)
option(BUILD_TESTS "brainCloud Unit Tests" OFF)

#=============================================================================
# Definitions
#=============================================================================
add_definitions(-DUSE_IMMEDIATE_RETRY)
add_definitions(-DGAMECLIENT_DEBUGLEVEL=1)

# On VS2013+, lets not use CURL but straight Windows' IXMLHttpRequest2, unless specified otherwise
if (NOT USE_CPPREST AND NOT VS2013_OR_HIGHER AND NOT APPLE)
	add_definitions(-DUSE_CURL)
	set(USE_CURL 1)
endif()

# On VS2013+, lets not use CURL but straight Windows' IXMLHttpRequest2, unless specified otherwise
if (NOT USE_CPPREST AND NOT VS2013_OR_HIGHER AND NOT APPLE)
	add_definitions(-DUSE_PTHREAD)
	set(USE_PTHREAD 1)
endif()

#=============================================================================
# Compiler flags
#=============================================================================
# We want to use C++11 flag on the compiler for std::thread
if (VS2013_OR_HIGHER)
	set(CMAKE_CXX_STANDARD 11)
endif()

# Multi core compilation in VS
if (MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" "/MP")
endif()

#=============================================================================
# Unit Tests
#=============================================================================
if (DEFINED(${BUILD_TESTS}) OR ${BUILD_TESTS})
	add_subdirectory("${CMAKE_SOURCE_DIR}/tests")
endif()

#=============================================================================
# Braincloud client
#=============================================================================

set (BC_DIR "${PROJECT_SOURCE_DIR}")
set (OS_SPECIFIC_SRCS "")
set (OS_SPECIFIC_INCS "")

file(GLOB_RECURSE JSONCPP_FILES "${BC_DIR}/lib/jsoncpp-1.0.0/*.*")

# cpprestsdk (most windows platforms) or curl (most *nix platforms)
if (WIN32 AND ${USE_CPPREST})
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/win/BrainCloudComms2.h")
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/win/CppRestFileUploader.h")
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/win/MD5.h")
	list(APPEND OS_SPECIFIC_SRCS "src/win/BrainCloudComms2.cpp")
	list(APPEND OS_SPECIFIC_SRCS "src/win/CppRestFileUploader.cpp")
	list(APPEND OS_SPECIFIC_SRCS "src/win/MD5.cpp")
elseif (USE_CURL)
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/BrainCloudComms.h")
	list(APPEND OS_SPECIFIC_SRCS "src/BrainCloudComms.cpp")
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/nix/cURLFileUploader.h")
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/nix/cURLLoader.h")
	list(APPEND OS_SPECIFIC_SRCS "src/nix/cURLFileUploader.cpp")
	list(APPEND OS_SPECIFIC_SRCS "src/nix/cURLLoader.cpp")
elseif (VS2013_OR_HIGHER)
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/BrainCloudComms.h")
	list(APPEND OS_SPECIFIC_SRCS "src/BrainCloudComms.cpp")
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/win/XMLHTTPRequestFileUploader.h")
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/win/XMLHTTPRequestLoader.h")
	list(APPEND OS_SPECIFIC_SRCS "src/win/XMLHTTPRequestFileUploader.cpp")
	list(APPEND OS_SPECIFIC_SRCS "src/win/XMLHTTPRequestLoader.cpp")
else()
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/BrainCloudComms.h")
	list(APPEND OS_SPECIFIC_SRCS "src/BrainCloudComms.cpp")
endif()

# other platform specific srcs/includes
if (APPLE)
    list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/mac/nsFileUploader.h")
    list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/mac/nsURLLoader.h")
    list(APPEND OS_SPECIFIC_SRCS "src/mac/GUID.mm")
    list(APPEND OS_SPECIFIC_SRCS "src/mac/nsFileUploader.mm")
    list(APPEND OS_SPECIFIC_SRCS "src/mac/nsURLLoader.mm")
    list(APPEND OS_SPECIFIC_SRCS "src/mac/SaveDataHelper.mm")
	include_directories("${BC_DIR}/lib/mac/sskeychain")
    list(APPEND OS_SPECIFIC_SRCS "lib/mac/sskeychain/SSKeychain/SSKeychain.m")
    list(APPEND OS_SPECIFIC_SRCS "lib/mac/sskeychain/SSKeychain/SSKeychainQuery.m")
else()
    list(APPEND OS_SPECIFIC_SRCS "src/SaveDataHelper.cpp")
endif()

include_directories("${BC_DIR}/include")
include_directories("${BC_DIR}/lib/jsoncpp-1.0.0")

add_library(brainCloud STATIC

	# public headers
	include/braincloud/AuthenticationType.h
	include/braincloud/BrainCloudAsyncMatch.h
	include/braincloud/BrainCloudAuthentication.h
	include/braincloud/BrainCloudClient.h
	include/braincloud/BrainCloudDataStream.h
	include/braincloud/BrainCloudEntity.h
	include/braincloud/BrainCloudEvent.h
	include/braincloud/BrainCloudFile.h
	include/braincloud/BrainCloudFriend.h
	include/braincloud/BrainCloudGamification.h
	include/braincloud/BrainCloudGlobalApp.h
	include/braincloud/BrainCloudGlobalEntity.h
	include/braincloud/BrainCloudGlobalStatistics.h
	include/braincloud/BrainCloudGroup.h
	include/braincloud/BrainCloudIdentity.h
	include/braincloud/BrainCloudMail.h
	include/braincloud/BrainCloudMatchmaking.h
	include/braincloud/BrainCloudOneWayMatch.h
	include/braincloud/BrainCloudPlaybackStream.h
	include/braincloud/BrainCloudPlayerState.h
	include/braincloud/BrainCloudPlayerStatistics.h
	include/braincloud/BrainCloudPlayerStatisticsEvent.h
	include/braincloud/BrainCloudProduct.h
	include/braincloud/BrainCloudProfanity.h
	include/braincloud/BrainCloudPushNotification.h
	include/braincloud/BrainCloudRedemptionCode.h
	include/braincloud/BrainCloudS3Handling.h
	include/braincloud/BrainCloudScript.h
	include/braincloud/BrainCloudSocialLeaderboard.h
	include/braincloud/BrainCloudSteam.h
	include/braincloud/BrainCloudTime.h
	include/braincloud/BrainCloudTournament.h
	include/braincloud/BrainCloudTypes.h
	include/braincloud/BrainCloudWrapper.h
	include/braincloud/FriendPlatform.h
	include/braincloud/IEventCallback.h
	include/braincloud/IFileUploadCallback.h
	include/braincloud/IGlobalErrorCallback.h
	include/braincloud/INetworkErrorCallback.h
	include/braincloud/IRewardCallback.h
	include/braincloud/IServerCallback.h
	include/braincloud/OperationParam.h
	include/braincloud/Platform.h
	include/braincloud/ServerCall.h
	include/braincloud/ServiceName.h
	include/braincloud/ServiceOperation.h
	include/braincloud/http_codes.h
	include/braincloud/reason_codes.h

	# private headers
	include/braincloud/internal/Mutex.h
	include/braincloud/internal/GUID.h
	include/braincloud/internal/IBrainCloudComms.h
	include/braincloud/internal/IFileUploader.h
	include/braincloud/internal/JsonUtil.h
	include/braincloud/internal/SaveDataHelper.h
	include/braincloud/internal/StringUtil.h
	include/braincloud/internal/TimeUtil.h
	include/braincloud/internal/TimerCallback.h
	include/braincloud/internal/URLLoader.h
	include/braincloud/internal/URLLoaderClient.h
	include/braincloud/internal/URLRequest.h
	include/braincloud/internal/URLRequestHeader.h
	include/braincloud/internal/URLRequestMethod.h
	include/braincloud/internal/URLResponse.h
	include/braincloud/internal/md5x.h
	include/braincloud/internal/timegm.h

	# source files
	src/AuthenticationType.cpp
	src/BrainCloudAsyncMatch.cpp
	src/BrainCloudAuthentication.cpp
	src/BrainCloudClient.cpp
	src/BrainCloudDataStream.cpp
	src/BrainCloudEntity.cpp
	src/BrainCloudEvent.cpp
	src/BrainCloudFile.cpp
	src/BrainCloudFriend.cpp
	src/BrainCloudGamification.cpp
	src/BrainCloudGlobalApp.cpp
	src/BrainCloudGlobalEntity.cpp
	src/BrainCloudGlobalStatistics.cpp
	src/BrainCloudGroup.cpp
	src/BrainCloudIdentity.cpp
	src/BrainCloudMail.cpp
	src/BrainCloudMatchmaking.cpp
	src/BrainCloudOneWayMatch.cpp
	src/BrainCloudPlaybackStream.cpp
	src/BrainCloudPlayerState.cpp
	src/BrainCloudPlayerStatistics.cpp
	src/BrainCloudPlayerStatisticsEvent.cpp
	src/BrainCloudProduct.cpp
	src/BrainCloudProfanity.cpp
	src/BrainCloudPushNotification.cpp
	src/BrainCloudRedemptionCode.cpp
	src/BrainCloudS3Handling.cpp
	src/BrainCloudScript.cpp
	src/BrainCloudSocialLeaderboard.cpp
	src/BrainCloudSteam.cpp
	src/BrainCloudTime.cpp
	src/BrainCloudTournament.cpp
	src/BrainCloudWrapper.cpp
	src/FriendPlatform.cpp
	src/GUID.cpp
	src/IBrainCloudComms.cpp
	src/JsonUtil.cpp
	src/OperationParam.cpp
	src/Platform.cpp
	src/ServerCall.cpp
	src/ServiceName.cpp
	src/ServiceOperation.cpp
	src/StringUtil.cpp
	src/TimeUtil.cpp
	src/TimerCallback.cpp
	src/URLLoader.cpp
	src/URLLoaderClient.cpp
	src/URLRequest.cpp
	src/URLRequestHeader.cpp
	src/URLRequestMethod.cpp
	src/URLResponse.cpp
	src/md5x.c

	${OS_SPECIFIC_INCS}
	${OS_SPECIFIC_SRCS}
	${JSONCPP_FILES}
)

#=============================================================================
# Libraries
#=============================================================================
if (APPLE)
	find_library(BC_GAMEKIT_LIB GameKit)
	find_library(BC_COREFOUNDATION_LIB CoreFoundation)
	find_library(BC_FOUNDATION_LIB Foundation)
	find_library(BC_SYSCONFIG_LIB SystemConfiguration)
	target_link_libraries(brainCloud ${BC_GAMEKIT_LIB} ${BC_COREFOUNDATION_LIB} ${BC_FOUNDATION_LIB} ${BC_SYSCONFIG_LIB})
elseif (LINUX)
	find_package(CURL REQUIRED)
	list(APPEND includes PUBLIC ${CURL_INCLUDE_DIRS})
	target_link_libraries(brainCloud PUBLIC ${CURL_LIBRARIES})
elseif (WIN32)
	if (${USE_CPPREST})
		# TODO: the cpprestsdk-static is *not* built by the CMake project.
		# You will need to manually load up the project and build the various libs
		include_directories("${BC_DIR}/lib/win32/cpprestsdk-static/Release/include")
		add_definitions(-D_NO_ASYNCRTIMP -DUSE_NEW_COMMS)
		find_library(BC_CPPREST_RELEASE_LIB cpprest120_2_0.lib "${BC_DIR}/lib/win32/cpprestsdk-static/Binaries/Win32/Release")
		find_library(BC_CPPREST_DEBUG_LIB cpprest120d_2_0.lib "${BC_DIR}/lib/win32/cpprestsdk-static/Binaries/Win32/Debug")

		# additional libs required by cpprestsdk
		set (WIN_PLATFORM_DIR "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x86")
		find_library(BC_WINHTTP_LIB winhttp.lib ${WIN_PLATFORM_DIR})
		find_library(BC_BCRYPT_LIB bcrypt.lib ${WIN_PLATFORM_DIR})
		find_library(BC_CRYPT32_LIB crypt32.lib ${WIN_PLATFORM_DIR})

		target_link_libraries(brainCloud general ${BC_WINHTTP_LIB} ${BC_BCRYPT_LIB} ${BC_CRYPT32_LIB} debug ${BC_CPPREST_DEBUG_LIB} optimized ${BC_CPPREST_RELEASE_LIB})
	else()
		if (VS2013_OR_HIGHER)
			target_link_libraries(brainCloud PUBLIC msxml6 comsuppwd)
		else()
			include_directories("${BC_DIR}/lib/win32/pthread-w32-2-8-0/Pre-built.2/include")

			add_definitions(-DWIN32 -D_LIB -DPTW32_STATIC_LIB)
			find_library(BC_PTHREADW32_LIB pthreadVCE2 "${BC_DIR}/lib/win32/pthread-w32-2-8-0/Pre-built.2/lib")

			add_definitions(-DCURL_STATICLIB)
			include_directories("${BC_DIR}/lib/win32/curl-7.44.0/include")
			find_library(BC_CURL_LIB_RELEASE libcurl_a.lib "${BC_DIR}/lib/win32/curl-7.44.0/lib")
			find_library(BC_CURL_LIB_DEBUG libcurl_a_debug.lib "${BC_DIR}/lib/win32/curl-7.44.0/lib")
			target_link_libraries(brainCloud general ${BC_PTHREADW32_LIB} optimized ${BC_CURL_LIB_RELEASE} debug ${BC_CURL_LIB_DEBUG})
		endif()
	endif()
endif()

target_include_directories(brainCloud PUBLIC "${BC_DIR}/include" ${includes})
