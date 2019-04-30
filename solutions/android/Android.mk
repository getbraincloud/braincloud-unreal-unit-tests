LOCAL_PATH:= $(call my-dir)

local_src_files := \
	$(LOCAL_PATH)/../../src/AuthenticationType.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudAppStore.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudAsyncMatch.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudAuthentication.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudChat.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudClient.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudDataStream.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudEntity.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudEvent.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudFile.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudFriend.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudGamification.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudGlobalApp.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudGlobalEntity.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudGlobalStatistics.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudGroup.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudIdentity.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudLobby.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudMail.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudMatchmaking.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudMessaging.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudOneWayMatch.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudPlaybackStream.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudPlayerState.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudPlayerStatistics.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudPlayerStatisticsEvent.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudPresence.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudProduct.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudProfanity.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudPushNotification.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudRedemptionCode.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudRTT.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudS3Handling.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudScript.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudSocialLeaderboard.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudSteam.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudTime.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudTournament.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudVirtualCurrency.cpp \
    $(LOCAL_PATH)/../../src/BrainCloudWrapper.cpp \
    $(LOCAL_PATH)/../../src/DefaultBrainCloudComms.cpp \
    $(LOCAL_PATH)/../../src/DefaultGUID.cpp \
    $(LOCAL_PATH)/../../src/DefaultSaveDataHelper.cpp \
    $(LOCAL_PATH)/../../src/DefaultTCPSocket.cpp \
    $(LOCAL_PATH)/../../src/FriendPlatform.cpp \
    $(LOCAL_PATH)/../../src/GUID.cpp \
    $(LOCAL_PATH)/../../src/IBrainCloudComms.cpp \
    $(LOCAL_PATH)/../../src/JsonUtil.cpp \
    $(LOCAL_PATH)/../../src/md5x.c \
    $(LOCAL_PATH)/../../src/OperationParam.cpp \
    $(LOCAL_PATH)/../../src/Platform.cpp \
    $(LOCAL_PATH)/../../src/RTTComms.cpp \
    $(LOCAL_PATH)/../../src/SaveDataHelper.cpp \
    $(LOCAL_PATH)/../../src/ServerCall.cpp \
    $(LOCAL_PATH)/../../src/ServiceName.cpp \
    $(LOCAL_PATH)/../../src/ServiceOperation.cpp \
    $(LOCAL_PATH)/../../src/StringUtil.cpp \
    $(LOCAL_PATH)/../../src/TimeUtil.cpp \
    $(LOCAL_PATH)/../../src/TimerCallback.cpp \
    $(LOCAL_PATH)/../../src/URLLoader.cpp \
    $(LOCAL_PATH)/../../src/URLLoaderClient.cpp \
    $(LOCAL_PATH)/../../src/URLRequest.cpp \
    $(LOCAL_PATH)/../../src/URLRequestHeader.cpp \
    $(LOCAL_PATH)/../../src/URLRequestMethod.cpp \
    $(LOCAL_PATH)/../../src/URLResponse.cpp \
	$(LOCAL_PATH)/../../src/android/AndroidDevice.cpp \
	$(LOCAL_PATH)/../../src/android/AndroidWebSocket.cpp \
	$(LOCAL_PATH)/../../src/android/com_bitheads_braincloud_AndroidBridge.cpp \
    $(LOCAL_PATH)/../../src/nix/cURLFileUploader.cpp \
    $(LOCAL_PATH)/../../src/nix/cURLLoader.cpp \
	$(wildcard $(LOCAL_PATH)/../../src/android/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../lib/jsoncpp-1.0.0/*.cpp)

local_c_includes := \
	$(wildcard $(LOCAL_PATH)/../../include) \
	$(wildcard $(LOCAL_PATH)/../../lib/jsoncpp-1.0.0) \
	$(wildcard $(LOCAL_PATH)/../../lib/android/include) 

	#$(wildcard $(LOCAL_PATH)/../../lib/android/curl-7.40.0/include) 

	#$(NDK_PROJECT_PATH) \
	#$(NDK_PROJECT_PATH)/crypto/asn1 \
	#$(NDK_PROJECT_PATH)/crypto/evp \
	#$(NDK_PROJECT_PATH)/include \
	#$(NDK_PROJECT_PATH)/include/openssl

local_c_flags := -DNO_WINDOWS_BRAINDEATH -DUSE_CURL -DUSE_PTHREAD -fpermissive
local_cpp_features := exceptions
#local_ldlibs := -lz -lssl -lcrypto -lcurl
#local_ldflags := -L$(LOCAL_PATH)/../Android/libs/armeabi
#local_ldflags += -L$(LOCAL_PATH)/../Android/libs/x86

#######################################

# shared library
include $(CLEAR_VARS)
LOCAL_SRC_FILES += $(local_src_files)
LOCAL_CFLAGS += $(local_c_flags)
LOCAL_C_INCLUDES += $(local_c_includes)
#LOCAL_LDLIBS += $(local_ldlibs)
#LOCAL_LDFLAGS += $(local_ldflags)
#LOCAL_SHARED_LIBRARIES += -lssl -lcrypto -lcurl -lblah
#LOCAL_STATIC_LIBRARIES += -lz -lssl -lcrypto -lcurl
LOCAL_CPP_FEATURES += $(local_cpp_features)
LOCAL_SRC_FILES += $(non_arm_src_files)
LOCAL_MODULE:= libbraincloud
include $(BUILD_STATIC_LIBRARY)

# static library
#include $(CLEAR_VARS)
#LOCAL_SRC_FILES += $(local_src_files)
#LOCAL_CFLAGS += $(local_c_flags)
#LOCAL_C_INCLUDES += $(local_c_includes)
#LOCAL_LDLIBS += $(local_ldlibs)
#LOCAL_LDFLAGS += $(local_ldflags)
##LOCAL_SHARED_LIBRARIES += -lssl -lcrypto -lcurl -lblah
#LOCAL_CPP_FEATURES += $(local_cpp_features)
#LOCAL_SRC_FILES += $(non_arm_src_files)
#LOCAL_MODULE:= libbraincloud_static
#include $(BUILD_STATIC_LIBRARY)

########################################
## host shared library
#ifeq ($(WITH_HOST_DALVIK),true)
#    include $(CLEAR_VARS)
#    include $(LOCAL_PATH)/../android-config.mk
#    LOCAL_SRC_FILES += $(local_src_files)
#    LOCAL_CFLAGS += $(local_c_flags) -DPURIFY
#    LOCAL_C_INCLUDES += $(local_c_includes)
#    LOCAL_SRC_FILES += $(non_arm_src_files)
#    LOCAL_LDLIBS += -ldl
#    LOCAL_MODULE_TAGS := optional
#    LOCAL_MODULE:= libcrypto
#    include $(BUILD_SHARED_LIBRARY)
#endif
#
#########################################
## host static library, which is used by some SDK tools.
#
##include $(CLEAR_VARS)
#include $(LOCAL_PATH)/../android-config.mk
#LOCAL_SRC_FILES += $(local_src_files)
#LOCAL_CFLAGS += $(local_c_flags) -DPURIFY
#LOCAL_C_INCLUDES += $(local_c_includes)
#LOCAL_SRC_FILES += $(non_arm_src_files)
#LOCAL_LDLIBS += -ldl
#LOCAL_MODULE_TAGS := optional
#LOCAL_MODULE:= libcrypto_static
#include $(BUILD_STATIC_LIBRARY)
