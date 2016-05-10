#!/bin/bash

project_dir=../GameClientLib/GameClientLib.xcodeproj
solution_dir=../GameClientLib
workspace="GameClient.xcworkspace"
artifacts_dir=artifacts
config=Release
sdk=appletvos
sdk_sim=appletvsimulator
scheme="GameClientLib - tvOS"

#temporary to switch to the beta xcode
#export DEVELOPER_DIR=/Applications/Xcode-beta.app/Contents/Developer

if [ "$config" == "Release" ]
then
  build_config=Release
fi

library_os="AppleTV_C++"

build_version="$1"
if [ "$build_version" == "" ]
then
  echo "build_appletv.sh <scheme> <build_version>"
  echo ""
  echo "Must set build_version via 4 digit number"
  echo " ie \"1.6.0.1234\""
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

  # create arm version of the library
  output_folder="`xcodebuild -project $project_dir -scheme "$scheme" -sdk "$sdk" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "$scheme" -sdk "$sdk" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi

  output_folder_sim="`xcodebuild -project $project_dir -scheme "$scheme" -sdk "$sdk_sim" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "$scheme" -sdk "$sdk_sim" -configuration "$build_config" clean build 
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

  cp "$output_folder/libGameClientLib.a" brainCloud/libs/libBrainCloudClient.a
  cp "$output_folder_sim/libGameClientLib.a" brainCloud/libs/libBrainCloudClient_sim.a
  cp ../GameClientLib/src/ApiHeaders/*.h brainCloud/include

  # copy in the wrapper classes
  cp -r ../BrainCloudWrapper/* brainCloud/src

  # copy in the thirdparty dependencies
  cp -r ../GameClientLib/lib/jsoncpp-1.0.0 brainCloud/thirdparty
  cp -r ../GameClientLib/lib/curl_jason/curl brainCloud/thirdparty
  cp -r ../GameClientLib/lib/curl_jason/openssl brainCloud/thirdparty

  # remove other ios/mac platforms
  rm -f brainCloud/thirdparty/curl/lib/libcurl_iOS.a
  rm -f brainCloud/thirdparty/curl/lib/libcurl_Mac.a
  rm -rf brainCloud/thirdparty/openssl/iOS
  rm -rf brainCloud/thirdparty/openssl/Mac

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

