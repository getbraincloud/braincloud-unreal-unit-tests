#!/bin/bash

set -x
set -e

if [ "$build_version" == "" ]; then
  echo "Must set build_version environment variable"
  exit 1
fi

platform_name="x86_64"
if [ "$1" == "i386" ]; then
  platform_name="i386"
fi

rm -rf artifacts
mkdir artifacts

# assumption libcurl4-openssl-dev is installed. To install...
# sudo apt-get install libcurl4-openssl-dev

# build debug/release targets

mkdir -p artifacts/linux_debug
pushd artifacts/linux_debug
cmake ../../.. -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_CXX_COMPILER=/usr/bin/g++-4.4 -DCMAKE_C_COMPILER=/usr/bin/gcc-4.4
make
popd

mkdir -p artifacts/linux_release
pushd artifacts/linux_release
cmake ../../.. -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_CXX_COMPILER=/usr/bin/g++-4.4 -DCMAKE_C_COMPILER=/usr/bin/gcc-4.4
make
popd

# and zip everything up
mkdir artifacts/brainCloud
mkdir -p artifacts/brainCloud/libs/debug
mkdir -p artifacts/brainCloud/libs/release
cp artifacts/linux_debug/*.a artifacts/brainCloud/libs/debug
cp artifacts/linux_release/*.a artifacts/brainCloud/libs/release

mkdir -p artifacts/brainCloud/thirdparty
cp -r ../lib/jsoncpp-1.0.0 artifacts/brainCloud/thirdparty

mkdir artifacts/brainCloud/include
cp -r ../include/* artifacts/brainCloud/include

cp docs/README.TXT artifacts/brainCloud
pushd artifacts/brainCloud
sed -i xxx "s/Platform: xxx/Platform: Linux C++/g" README.TXT
sed -i xxx "s/Version: x.x.x/Version: ${build_version}/g" README.TXT
rm -f README.TXTxxx
popd

pushd artifacts
zip -r "brainCloudClient_Linux_${platform_name}_C++_${build_version}.zip" brainCloud
popd

