cmake_minimum_required (VERSION 3.0)
project (brainCloud)

add_definitions(-DUSE_IMMEDIATE_RETRY)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_definitions(-DUNICODE -D_UNICODE)
endif()

if (NOT DEFINED(${SKIP_TESTS}) OR NOT ${SKIP_TESTS})
	add_subdirectory("${CMAKE_SOURCE_DIR}/tests")
endif()


add_definitions(-DGAMECLIENT_DEBUGLEVEL=1)

################################
# Braincloud client
################################

set (BC_DIR "${PROJECT_SOURCE_DIR}")
set (OS_SPECIFIC_SRCS "")
set (OS_SPECIFIC_INCS "")

file(GLOB_RECURSE JSONCPP_FILES "${BC_DIR}/lib/jsoncpp-1.0.0/*.*")

# cpprestsdk (most windows platforms) or curl (most *nix platforms)
if ((${CMAKE_SYSTEM_NAME} MATCHES "Windows") AND NOT (${NO_CPPREST_SDK}))
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/win/BrainCloudComms2.h")
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/win/CppRestFileUploader.h")
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/win/MD5.h")
	list(APPEND OS_SPECIFIC_SRCS "src/win/BrainCloudComms2.cpp")
	list(APPEND OS_SPECIFIC_SRCS "src/win/CppRestFileUploader.cpp")
	list(APPEND OS_SPECIFIC_SRCS "src/win/MD5.cpp")
else()
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/BrainCloudComms.h")
	list(APPEND OS_SPECIFIC_SRCS "src/BrainCloudComms.cpp")
    if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	    list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/nix/cURLFileUploader.h")
    	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/nix/cURLLoader.h")
	    list(APPEND OS_SPECIFIC_SRCS "src/nix/cURLFileUploader.cpp")
    	list(APPEND OS_SPECIFIC_SRCS "src/nix/cURLLoader.cpp")
    endif()
endif()

# other platform specific srcs/includes
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/mac/nsFileUploader.h")
	list(APPEND OS_SPECIFIC_INCS "include/braincloud/internal/mac/nsURLLoader.h")
	list(APPEND OS_SPECIFIC_SRCS "src/mac/GUID.mm")
    list(APPEND OS_SPECIFIC_SRCS "src/mac/nsFileUploader.mm")
	list(APPEND OS_SPECIFIC_SRCS "src/mac/nsURLLoader.mm")

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

elseif (${CMAKE_SYSTEM_NAME} MATCHES "WindowsPhone")
	
elseif (${CMAKE_SYSTEM_NAME} MATCHES "WindowsStore")
	
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
include/braincloud/BrainCloudTwitter.h
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
src/BrainCloudTwitter.cpp
src/BrainCloudWrapper.cpp
src/FriendPlatform.cpp
src/GUID.cpp
src/IBrainCloudComms.cpp
src/JsonUtil.cpp
src/OperationParam.cpp
src/Platform.cpp
src/SaveDataHelper.cpp
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
${JSONCPP_FILES})


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	find_library(BC_GAMEKIT_LIB GameKit)
	find_library(BC_COREFOUNDATION_LIB CoreFoundation)
	find_library(BC_FOUNDATION_LIB Foundation)
	find_library(BC_SYSCONFIG_LIB SystemConfiguration)
	target_link_libraries(brainCloud ${BC_GAMEKIT_LIB} ${BC_COREFOUNDATION_LIB} ${BC_FOUNDATION_LIB} ${BC_SYSCONFIG_LIB})
	
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
              /usr/local/lib
              /usr/local/ssl/lib)
	find_library(BC_CURL_LIB curl libcurl.a)
	find_library(BC_SSL_LIB ssl libssl.a)
	find_library(BC_CRYPTO_LIB crypto libcrypto.a)
	target_link_libraries(brainCloud ${BC_CURL_LIB} ${BC_SSL_LIB} ${BC_CRYPTO_LIB})
	
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

	if (${NO_CPPREST_SDK})
		include_directories("${BC_DIR}/lib/win32/pthread-w32-2-8-0/Pre-built.2/include")
		
		add_definitions(-DWIN32 -D_LIB -DPTW32_STATIC_LIB)
		find_library(BC_PTHREADW32_LIB pthreadVCE2 "${BC_DIR}/lib/win32/pthread-w32-2-8-0/Pre-built.2/lib")
	
		add_definitions(-DCURL_STATICLIB)
		include_directories("${BC_DIR}/lib/win32/curl-7.44.0/include")	
		find_library(BC_CURL_LIB_RELEASE libcurl_a.lib "${BC_DIR}/lib/win32/curl-7.44.0/lib")
		find_library(BC_CURL_LIB_DEBUG libcurl_a_debug.lib "${BC_DIR}/lib/win32/curl-7.44.0/lib")
		target_link_libraries(brainCloud general ${BC_PTHREADW32_LIB} optimized ${BC_CURL_LIB_RELEASE} debug ${BC_CURL_LIB_DEBUG})

	else()
	
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

	endif()

elseif (${CMAKE_SYSTEM_NAME} MATCHES "WindowsStore")

elseif (${CMAKE_SYSTEM_NAME} MATCHES "WindowsPhone")

endif()

target_include_directories(brainCloud PUBLIC "${BC_DIR}/include")
