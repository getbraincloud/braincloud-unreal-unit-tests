#APP_STL := stlport_static
APP_STL := gnustl_static
APP_PROJECT_PATH := $(shell pwd)
APP_BUILD_SCRIPT := $(APP_PROJECT_PATH)/Android.mk
APP_ABI := armeabi x86

# from cocos2dx
APP_CPPFLAGS := -frtti -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic

#NDK_DEBUG := 1
#APP_OPTIM := debug

