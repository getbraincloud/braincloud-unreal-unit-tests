LOCAL_PATH:= $(call my-dir)

local_src_files := \
	$(wildcard $(LOCAL_PATH)/../../src/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../src/*.c) \
	$(wildcard $(LOCAL_PATH)/../../src/android/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../src/nix/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../lib/jsoncpp-1.0.0/*.cpp)

local_c_includes := \
	$(wildcard $(LOCAL_PATH)/../../include) \
	$(wildcard $(LOCAL_PATH)/../../lib/jsoncpp-1.0.0) \
	$(wildcard $(LOCAL_PATH)/../../lib/android/cocos-curl/include) 

	#$(wildcard $(LOCAL_PATH)/../../lib/android/curl-7.40.0/include) 

	#$(NDK_PROJECT_PATH) \
	#$(NDK_PROJECT_PATH)/crypto/asn1 \
	#$(NDK_PROJECT_PATH)/crypto/evp \
	#$(NDK_PROJECT_PATH)/include \
	#$(NDK_PROJECT_PATH)/include/openssl

local_c_flags := -DNO_WINDOWS_BRAINDEATH -fpermissive
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
