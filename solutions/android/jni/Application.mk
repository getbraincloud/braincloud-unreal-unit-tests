# Android NDK: APP_STL gnustl_static is no longer supported. Please switch to either c++_static or c++_shared. See https://developer.android.com/ndk/guides/cpp-support.html for more information.
#APP_STL := stlport_static
#APP_STL := gnustl_static
# APP_STL := c++_shared
APP_STL := c++_static

APP_PROJECT_PATH := $(shell pwd)
APP_BUILD_SCRIPT := $(APP_PROJECT_PATH)/Android.mk

#  The armeabi ABI is no longer supported. Use armeabi-v7a.
# APP_ABI := armeabi x86
APP_ABI := armeabi-v7a x86

# from cocos2dx
APP_CPPFLAGS := -frtti -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic

#NDK_DEBUG := 1
#APP_OPTIM := debug

