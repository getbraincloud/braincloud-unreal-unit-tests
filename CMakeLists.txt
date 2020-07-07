if (CMAKE_SYSTEM_NAME STREQUAL WindowsStore)
    set(UWP 1)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL Android)
    set(ANDROID 1)
endif()

if (UWP)
    # We require 3.4.0 for UWP generation
    cmake_minimum_required(VERSION 3.4.0)
else()
    cmake_minimum_required(VERSION 3.0.0)
endif()

project(brainCloud)

# Setup modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# Usefull flags
if (UNIX AND NOT APPLE AND NOT ANDROID)
    set(LINUX 1)
endif()

#=============================================================================
# CMake options
#=============================================================================
option(BUILD_TESTS "brainCloud Unit Tests" OFF)
option(USE_CURL "Force use libCurl on Win32" OFF)

#=============================================================================
# Definitions
#=============================================================================
add_definitions(-DUSE_IMMEDIATE_RETRY)
add_definitions(-DGAMECLIENT_DEBUGLEVEL=1)
if (UWP)
    add_definitions(-DBC_UWP)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS) # sprintf instead of sprintf_s
    if (BUILD_TESTS)
        # add_definitions(-Dgtest_force_shared_crt=ON)
        option(
            gtest_force_shared_crt
            "Use shared (DLL) run-time lib even when Google Test is built as static lib."
            ON)
    endif()
endif()

# lets use libwebsockets by default
if (NOT UWP AND NOT ANDROID)
    set(USE_LIBWEBSOCKETS 1)
endif()

#=============================================================================
# Compiler flags
#=============================================================================
# We want to use C++11 flag on the compiler
set(CMAKE_CXX_STANDARD 11)

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

# HTTP related files
if (APPLE)
    list(APPEND OS_SPECIFIC_INCS
        "include/braincloud/internal/apple/nsFileUploader.h"
        "include/braincloud/internal/apple/nsPinger.h"
        "include/braincloud/internal/apple/nsURLLoader.h")
    list(APPEND OS_SPECIFIC_SRCS
        "src/apple/nsFileUploader.mm"
        "src/apple/nsPinger.mm"
        "src/apple/nsURLLoader.mm")
elseif (MSVC AND NOT USE_CURL)
    list(APPEND OS_SPECIFIC_INCS
        "include/braincloud/internal/win/XMLHTTPRequestCallback.h"
        "include/braincloud/internal/win/XMLHTTPRequestFileUploader.h"
        "include/braincloud/internal/win/XMLHTTPRequestLoader.h"
        "include/braincloud/internal/win/XMLHTTPRequestPinger.h")
    list(APPEND OS_SPECIFIC_SRCS
        "src/win/XMLHTTPRequestCallback.cpp"
        "src/win/XMLHTTPRequestFileUploader.cpp"
        "src/win/XMLHTTPRequestLoader.cpp"
        "src/win/XMLHTTPRequestPinger.cpp")
else()
    list(APPEND OS_SPECIFIC_INCS 
        "include/braincloud/internal/nix/cURLFileUploader.h"
        "include/braincloud/internal/nix/cURLLoader.h"
        "include/braincloud/internal/nix/cURLPinger.h")
    list(APPEND OS_SPECIFIC_SRCS 
        "src/nix/cURLFileUploader.cpp"
        "src/nix/cURLLoader.cpp"
        "src/nix/cURLPinger.cpp")
endif()

# Sockets
if (USE_LIBWEBSOCKETS OR ANDROID)
    list(APPEND OS_SPECIFIC_INCS
        "include/braincloud/internal/DefaultWebSocket.h")
    list(APPEND OS_SPECIFIC_SRCS "src/DefaultWebSocket.cpp")
endif()
if (WIN32)
    list(APPEND OS_SPECIFIC_SRCS "src/win/Win32TCPSocket.cpp")
    if (UWP)
        list(APPEND OS_SPECIFIC_INCS
            "include/braincloud/internal/win/UWPWebSocket.h")
        list(APPEND OS_SPECIFIC_SRCS "src/win/UWPWebSocket.cpp")
    endif()
else()
    list(APPEND OS_SPECIFIC_SRCS "src/DefaultTCPSocket.cpp")
endif()

# Guid
if (APPLE)
    list(APPEND OS_SPECIFIC_SRCS "src/apple/GUID.mm")
elseif (WIN32)
    list(APPEND OS_SPECIFIC_SRCS "src/win/WindowsGUID.cpp")
elseif (LINUX)
    list(APPEND OS_SPECIFIC_SRCS "src/nix/LinuxGUID.cpp")
else()
    list(APPEND OS_SPECIFIC_SRCS "src/DefaultGUID.cpp")
endif()

# Save data helper
if (APPLE)
    list(APPEND OS_SPECIFIC_INCS
        "include/braincloud/internal/apple/AppleSaveDataHelper.h")
    list(APPEND OS_SPECIFIC_SRCS "src/apple/AppleSaveDataHelper.mm")
elseif (WIN32)
    list(APPEND OS_SPECIFIC_INCS
        "include/braincloud/internal/win/WindowsSaveDataHelper.h")
    list(APPEND OS_SPECIFIC_SRCS "src/win/WindowsSaveDataHelper.cpp")
else()
    list(APPEND OS_SPECIFIC_SRCS
        "include/braincloud/internal/DefaultSaveDataHelper.h"
        "src/DefaultSaveDataHelper.cpp")
endif()

# Device
if (APPLE)
    list(APPEND OS_SPECIFIC_SRCS "src/apple/AppleDevice.cpp")
elseif (WIN32)
    list(APPEND OS_SPECIFIC_SRCS "src/win/WindowsDevice.cpp")
elseif (LINUX)
    list(APPEND OS_SPECIFIC_SRCS "src/nix/LinuxDevice.cpp")
elseif (ANDROID)
    list(APPEND OS_SPECIFIC_SRCS "src/android/AndroidDevice.cpp")
endif()

# other platform specific srcs/includes
if (APPLE)
    list(APPEND OS_SPECIFIC_SRCS
        "lib/apple/sskeychain/SSKeychain/SSKeychain.m"
        "lib/apple/sskeychain/SSKeychain/SSKeychainQuery.m")
    include_directories("${BC_DIR}/lib/apple/sskeychain")
elseif (WIN32)
    if (UWP)
        list(APPEND OS_SPECIFIC_INCS
            "include/braincloud/internal/win/MD5.h")
        list(APPEND OS_SPECIFIC_SRCS "src/win/MD5.cpp")
    endif()
elseif (ANDROID)
    list(APPEND OS_SPECIFIC_SRCS
        "include/braincloud/internal/android/com_bitheads_braincloud_AndroidBridge.h"
        "src/android/com_bitheads_braincloud_AndroidBridge.cpp")
endif()

if (NOT UWP)
    list(APPEND OS_SPECIFIC_SRCS "src/md5x.c") # UWP doesn't like c files
endif()

list(APPEND includes PUBLIC "${BC_DIR}/include")
list(APPEND includes PUBLIC "${BC_DIR}/lib/jsoncpp-1.0.0")

add_library(brainCloud STATIC
    # public headers
    include/braincloud/AuthenticationType.h
    include/braincloud/BrainCloudAppStore.h
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
    include/braincloud/BrainCloudGlobalFile.h
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
    include/braincloud/BrainCloudRTT.h
    include/braincloud/BrainCloudS3Handling.h
    include/braincloud/BrainCloudScript.h
    include/braincloud/BrainCloudSocialLeaderboard.h
    include/braincloud/BrainCloudSteam.h
    include/braincloud/BrainCloudTime.h
    include/braincloud/BrainCloudTournament.h
    include/braincloud/BrainCloudCustomEntity.h
    include/braincloud/BrainCloudItemCatalog.h
    include/braincloud/BrainCloudUserItems.h
    include/braincloud/BrainCloudTypes.h
    include/braincloud/BrainCloudVirtualCurrency.h
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
    include/braincloud/internal/Device.h
    include/braincloud/internal/Mutex.h
    include/braincloud/internal/GUID.h
    include/braincloud/internal/IBrainCloudComms.h
    include/braincloud/internal/IFileUploader.h
    include/braincloud/internal/IPinger.h
    include/braincloud/internal/ITCPSocket.h
    include/braincloud/internal/DefaultBrainCloudComms.h
    include/braincloud/internal/JsonUtil.h
    include/braincloud/internal/RTTComms.h
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
    src/BrainCloudAppStore.cpp
    src/BrainCloudAsyncMatch.cpp
    src/BrainCloudAuthentication.cpp
    src/BrainCloudChat.cpp
    src/BrainCloudClient.cpp
    src/BrainCloudDataStream.cpp
    src/BrainCloudEntity.cpp
    src/BrainCloudEvent.cpp
    src/BrainCloudFile.cpp
    src/BrainCloudFriend.cpp
    src/BrainCloudGamification.cpp
    src/BrainCloudGlobalApp.cpp
    src/BrainCloudGlobalEntity.cpp
    src/BrainCloudGlobalFile.cpp
    src/BrainCloudGlobalStatistics.cpp
    src/BrainCloudGroup.cpp
    src/BrainCloudIdentity.cpp
    src/BrainCloudLobby.cpp
    src/BrainCloudMail.cpp
    src/BrainCloudMatchmaking.cpp
    src/BrainCloudMessaging.cpp
    src/BrainCloudOneWayMatch.cpp
    src/BrainCloudPlaybackStream.cpp
    src/BrainCloudPlayerState.cpp
    src/BrainCloudPlayerStatistics.cpp
    src/BrainCloudPlayerStatisticsEvent.cpp
    src/BrainCloudPresence.cpp
    src/BrainCloudProduct.cpp
    src/BrainCloudProfanity.cpp
    src/BrainCloudPushNotification.cpp
    src/BrainCloudRedemptionCode.cpp
    src/BrainCloudRTT.cpp
    src/BrainCloudS3Handling.cpp
    src/BrainCloudScript.cpp
    src/BrainCloudSocialLeaderboard.cpp
    src/BrainCloudSteam.cpp
    src/BrainCloudTime.cpp
    src/BrainCloudTournament.cpp
    src/BrainCloudCustomEntity.cpp
    src/BrainCloudItemCatalog.cpp
    src/BrainCloudUserItems.cpp
    src/BrainCloudVirtualCurrency.cpp
    src/BrainCloudWrapper.cpp
    src/DefaultBrainCloudComms.cpp
    src/FriendPlatform.cpp
    src/GUID.cpp
    src/IBrainCloudComms.cpp
    src/JsonUtil.cpp
    src/OperationParam.cpp
    src/Platform.cpp
    src/RTTComms.cpp
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

    ${OS_SPECIFIC_INCS}
    ${OS_SPECIFIC_SRCS}
    ${JSONCPP_FILES}
)

# Set files to be "consume windows runtime exceptions" to build them with CX
if (UWP)
    set_source_files_properties(
        "src/win/WindowsSaveDataHelper.cpp"
        "src/win/UWPWebSocket.cpp"
        PROPERTIES COMPILE_FLAGS "/ZW")
endif()

#=============================================================================
# Libraries
#=============================================================================
if (APPLE)
    find_library(BC_GAMEKIT_LIB GameKit)
    find_library(BC_COREFOUNDATION_LIB CoreFoundation)
    find_library(BC_FOUNDATION_LIB Foundation)
    find_library(BC_SYSCONFIG_LIB SystemConfiguration)
    find_library(BC_SECURITY_LIB Security)
    list(APPEND libs 
        ${BC_GAMEKIT_LIB}
        ${BC_COREFOUNDATION_LIB}
        ${BC_FOUNDATION_LIB}
        ${BC_SYSCONFIG_LIB}
        ${BC_SECURITY_LIB})
elseif (LINUX)
    find_package(CURL REQUIRED)
    list(APPEND includes PUBLIC ${CURL_INCLUDE_DIRS})

    find_package(UUID REQUIRED)
    list(APPEND includes PUBLIC ${UUID_INCLUDE_DIRS})

    list(APPEND libs
        ${CURL_LIBRARIES}
        ${UUID_LIBRARIES})
elseif (ANDROID)
    list(APPEND includes PUBLIC "${BC_DIR}/lib/android/include/${ANDROID_ABI}")

    SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
    find_library(BC_CURL_LIB NAMES curl HINTS "${BC_DIR}/lib/android/libs/${ANDROID_ABI}")
    find_library(BC_LWS_LIB NAMES websockets HINTS "${BC_DIR}/lib/android/libs/${ANDROID_ABI}")
    find_library(BC_UV_LIB NAMES uv_a HINTS "${BC_DIR}/lib/android/libs/${ANDROID_ABI}")
    find_library(BC_CRYPTO_LIB NAMES crypto HINTS "${BC_DIR}/lib/android/libs/${ANDROID_ABI}")
    find_library(BC_SSL_LIB NAMES ssl HINTS "${BC_DIR}/lib/android/libs/${ANDROID_ABI}")
    find_package(ZLIB REQUIRED)

    list(APPEND libs PUBLIC 
        ${BC_CURL_LIB} 
        ${BC_LWS_LIB} 
        ${BC_UV_LIB} 
        ${BC_SSL_LIB} 
        ${BC_CRYPTO_LIB} 
        ${ZLIB_LIBRARIES}
    )
elseif (WIN32)
    if (USE_CURL)
        include_directories(
            "${BC_DIR}/lib/win32/pthread-w32-2-8-0/Pre-built.2/include")

        add_definitions(-DWIN32 -D_LIB -DPTW32_STATIC_LIB)
        find_library(BC_PTHREADW32_LIB pthreadVCE2
            "${BC_DIR}/lib/win32/pthread-w32-2-8-0/Pre-built.2/lib")

        add_definitions(-DCURL_STATICLIB)
        include_directories("${BC_DIR}/lib/win32/curl-7.44.0/include")
        find_library(BC_CURL_LIB_RELEASE libcurl_a.lib
            "${BC_DIR}/lib/win32/curl-7.44.0/lib")
        find_library(BC_CURL_LIB_DEBUG libcurl_a_debug.lib
            "${BC_DIR}/lib/win32/curl-7.44.0/lib")
        list(APPEND libs general
            ${Socket_LIBRARIES}
            ${BC_PTHREADW32_LIB}
            optimized ${BC_CURL_LIB_RELEASE}
            debug ${BC_CURL_LIB_DEBUG})
    else()
        find_package(Socket)
        list(APPEND libs msxml6 ${Socket_LIBRARIES})
    endif()
endif()

if (USE_LIBWEBSOCKETS)
    # TLS
    option(ENABLE_TESTING "" OFF)
    option(ENABLE_PROGRAMS "" OFF)
    add_subdirectory(./lib/mbedtls/)
    list(APPEND libs PUBLIC mbedtls mbedx509 mbedcrypto)
    list(APPEND includes 
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/lib/mbedtls/include/)
    option(LWS_WITH_MBEDTLS "" ON)
    set(LWS_MBEDTLS_INCLUDE_DIRS
        "${CMAKE_CURRENT_BINARY_DIR}/lib/mbedtls/include/")
    if (UNIX AND NOT CMAKE_GENERATOR STREQUAL Xcode)
        set(LWS_MBEDTLS_LIBRARIES
            "${CMAKE_CURRENT_BINARY_DIR}/lib/mbedtls/library/libmbedtls.a"
            "${CMAKE_CURRENT_BINARY_DIR}/lib/mbedtls/library/libmbedcrypto.a"
            "${CMAKE_CURRENT_BINARY_DIR}/lib/mbedtls/library/libmbedx509.a")
    else()
        set(LWS_MBEDTLS_LIBRARIES 
            "${CMAKE_CURRENT_BINARY_DIR}/lib/mbedtls/library/")
    endif()
    
    # LibWebSockets
    option(LWS_WITHOUT_SERVER "" ON)
    option(LWS_WITHOUT_TESTAPPS "" ON)
    option(LWS_WITHOUT_TEST_SERVER "" ON)
    option(LWS_WITHOUT_TEST_SERVER_EXTPOLL "" ON)
    option(LWS_WITHOUT_TEST_PING "" ON)
    option(LWS_WITHOUT_TEST_CLIENT "" ON)
    option(LWS_WITH_SHARED "" OFF)
    add_subdirectory(./lib/libwebsockets/)
    list(APPEND libs websockets)
    list(APPEND includes 
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/lib/libwebsockets/include/)
endif()

# Setup includes and linked libraries
target_include_directories(brainCloud PUBLIC "${BC_DIR}/include" ${includes})
target_link_libraries(brainCloud PUBLIC ${libs})

# Compile flags
if (WIN32 AND NOT UWP)
    target_compile_options(brainCloud PRIVATE 
        /MP     # Multi-core compilation
    )
elseif (UWP)
    target_compile_options(brainCloud PRIVATE
        /MP     # Multi-core compilation
        /wd4996 # DEPRECATED throws error without this
    )
endif()
