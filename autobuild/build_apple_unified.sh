#!/bin/bash

project_dir=../GameClientLib/GameClientLib.xcodeproj
solution_dir=../GameClientLib
workspace="GameClient.xcworkspace"
artifacts_dir=artifacts
config=Release

#temporary to switch to the beta xcode
#export DEVELOPER_DIR=/Applications/Xcode-beta.app/Contents/Developer

if [ "$config" == "Release" ]
then
  build_config=Release
fi

library_os="Apple_C++"

build_version="$1"
if [ "$build_version" == "" ]
then
  echo "build_apple_unified.sh <build_version>"
  echo ""
  echo "Must set build_version via 4 digit number"
  echo " ie \"1.6.0.1234\""
  exit 1
fi

build_internal_version=`echo $build_version | cut -d \".\" -f 4`
build_external_version=`echo $build_version | cut -d \".\" -f 1-3`


function failed()
{
    local error=${1:-Undefined error}
    echo "Failed: $error" >&2
    exit 1
}

function describe_sdks()
{
  #list the installed sdks
  echo "Available SDKs"
  xcodebuild -showsdks  
}

function describe_workspace()
{
  #describe the project workspace
  echo "Available schemes"
#  xcodebuild -list -workspace $workspace
}

function build_app()
{
  local devired_data_path="$HOME/Library/Developer/Xcode/DerivedData"

  #get the name of the workspace to be build, used as the prefix of the DerivedData directory for this build
  #local workspace_name=$(echo "$workspace" | sed -n 's/\([^\.]\{1,\}\)\.xcworkspace/\1/p')
  #build the app
  echo "Running xcodebuild > xcodebuild_output ..."

  rm -rf tmp
  mkdir tmp
  
  # ios arm/sim
  output_folder_ios="`xcodebuild -project $project_dir -scheme "GameClientLib - iOS C++11 nobitcode" -sdk "iphoneos" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "GameClientLib - iOS C++11 nobitcode" -sdk "iphoneos" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  mv "$output_folder_ios/libGameClientLib.a" "tmp/libBrainCloud_ios_nobitcode.a"

  #output_folder_ios_sim=$output_folder_ios
  output_folder_ios_sim="`xcodebuild -project $project_dir -scheme "GameClientLib - iOS C++11 nobitcode" ARCHS=x86_64 -sdk "iphonesimulator" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "GameClientLib - iOS C++11 nobitcode" ARCHS="i386 x86_64" -sdk "iphonesimulator" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  mv "$output_folder_ios_sim/libGameClientLib.a" "tmp/libBrainCloud_iossim_nobitcode.a"

  output_folder_ios="`xcodebuild -project $project_dir -scheme "GameClientLib - iOS C++11" -sdk "iphoneos" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "GameClientLib - iOS C++11" -sdk "iphoneos" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  mv "$output_folder_ios/libGameClientLib.a" "tmp/libBrainCloud_ios.a"

  #output_folder_ios_sim=$output_folder_ios
  output_folder_ios_sim="`xcodebuild -project $project_dir -scheme "GameClientLib - iOS C++11" ARCHS=x86_64 -sdk "iphonesimulator" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "GameClientLib - iOS C++11" ARCHS="i386 x86_64" -sdk "iphonesimulator" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  mv "$output_folder_ios_sim/libGameClientLib.a" "tmp/libBrainCloud_iossim.a"


  # tvos arm/sim
  output_folder_tvos="`xcodebuild -project $project_dir -scheme "GameClientLib - tvOS" ENABLE_BITCODE=YES -sdk "appletvos" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "GameClientLib - tvOS" ENABLE_BITCODE=YES -sdk "appletvos" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  mv "$output_folder_tvos/libGameClientLib.a" "tmp/libBrainCloud_tvos.a"

  #output_folder_tvos_sim=$output_folder_tvos
  output_folder_tvos_sim="`xcodebuild -project $project_dir -scheme "GameClientLib - tvOS" ARCHS=x86_64 ENABLE_BITCODE=YES -sdk "appletvsimulator" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "GameClientLib - tvOS" ARCHS=x86_64 ENABLE_BITCODE=YES -sdk "appletvsimulator" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  mv "$output_folder_tvos_sim/libGameClientLib.a" "tmp/libBrainCloud_tvossim.a"


  # mac osx
  output_folder_osx="`xcodebuild -project $project_dir -scheme "GameClientLib - OSX" -sdk "macosx" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "GameClientLib - OSX" -sdk "macosx" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi

  rm -rf brainCloud
  mkdir brainCloud
  mkdir brainCloud/include
  mkdir brainCloud/libs
  mkdir brainCloud/src
  mkdir brainCloud/thirdparty

  # create fat binaries
  lipo -create "tmp/libBrainCloud_ios.a" "tmp/libBrainCloud_iossim.a" -output brainCloud/libs/brainCloudClient_ios.a
  lipo -create "tmp/libBrainCloud_ios_nobitcode.a" "tmp/libBrainCloud_iossim_nobitcode.a" -output brainCloud/libs/brainCloudClient_ios_nobitcode.a
  lipo -create "tmp/libBrainCloud_tvos.a" "tmp/libBrainCloud_tvossim.a" -output brainCloud/libs/brainCloudClient_tvos.a
  cp "$output_folder_osx/libGameClientLib.a" brainCloud/libs/brainCloudClient_osx.a

  cp ../GameClientLib/src/ApiHeaders/*.h brainCloud/include

  # copy in the wrapper classes
  cp -r ../BrainCloudWrapper/* brainCloud/src

  # copy in the thirdparty dependencies
  cp -r ../GameClientLib/lib/jsoncpp-1.0.0 brainCloud/thirdparty
  cp -r ../GameClientLib/lib/curl_jason/curl brainCloud/thirdparty
  cp -r ../GameClientLib/lib/curl_jason/openssl brainCloud/thirdparty

  cp ../../Common/docs/README.TXT brainCloud

  zip -r $artifacts_dir/brainCloudClient_${library_os}_${build_version}.zip brainCloud

  rm -rf brainCloud
}

function clean_artifacts
{
  rm -rf $artifacts_dir
  mkdir $artifacts_dir
}

# turn on shell command logging
set -x

# turn on exit on fail 
set -e

# turn on fail if something in pipeline fails
set -o pipefail

echo "**** Clean artifacts"
clean_artifacts
echo
echo "**** Describe SDKs"
describe_sdks
echo
echo "**** Build"
build_app
echo
echo "**** Complete!"

