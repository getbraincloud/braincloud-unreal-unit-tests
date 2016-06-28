#!/bin/bash

set -x
set -e

if [ "$build_version" == "" ]; then
  echo "Must set build_version environment variable"
  exit 1
fi

if [ "$ANDROID_NDK_HOME" == "" ]; then
  echo "Must set ANDROID_NDK_HOME environment variable"
  exit 1
fi

rm -rf artifacts
mkdir artifacts

# compile braincloud
pushd ../solutions/android
"$ANDROID_NDK_HOME/ndk-build" clean
"$ANDROID_NDK_HOME/ndk-build" 
popd

# and zip everything up
mkdir artifacts/brainCloud
mkdir -p artifacts/brainCloud/libs/armeabi
mkdir -p artifacts/brainCloud/libs/x86
cp ../lib/android/cocos-curl/libs/armeabi/*.a artifacts/brainCloud/libs/armeabi
cp ../lib/android/cocos-curl/libs/x86/*.a artifacts/brainCloud/libs/x86

mkdir -p artifacts/brainCloud/thirdparty/curl/include
cp -r ../lib/android/cocos-curl/include/curl artifacts/brainCloud/thirdparty/curl/include
cp -r ../lib/jsoncpp-1.0.0 artifacts/brainCloud/thirdparty

cp ../solutions/android/obj/local/armeabi/libbraincloud.a artifacts/brainCloud/libs/armeabi
cp ../solutions/android/obj/local/x86/libbraincloud.a artifacts/brainCloud/libs/x86

mkdir -p artifacts/brainCloud/include/braincloud
cp -r ../include/braincloud/* artifacts/brainCloud/include/braincloud

mkdir artifacts/brainCloud/javasrc
cp -r ../solutions/android/java/ artifacts/brainCloud/javasrc

cp docs/README.TXT artifacts/brainCloud
pushd artifacts/brainCloud
sed -i xxx "s/Platform: xxx/Platform: Android C++/g" README.TXT
sed -i xxx "s/Version: x.x.x/Version: ${build_version}/g" README.TXT
rm -f README.TXTxxx
popd

pushd artifacts
zip -r "brainCloudClient_Android_C++_${build_version}.zip" brainCloud

popd

