#!/bin/bash

# https://gist.github.com/949831
# http://blog.carbonfive.com/2011/05/04/automated-ad-hoc-builds-using-xcode-4/

# command line OTA distribution references and examples
# http://nachbaur.com/blog/how-to-automate-your-iphone-app-builds-with-hudson
# http://nachbaur.com/blog/building-ios-apps-for-over-the-air-adhoc-distribution
# http://blog.octo.com/en/automating-over-the-air-deployment-for-iphone/
# http://www.neat.io/posts/2010/10/27/automated-ota-ios-app-distribution.html

project_dir=../GameClientLib/GameClientLib.xcodeproj
solution_dir=../GameClientLib
artifacts_dir=artifacts

config=Release
#config=Adhoc

sdk=iphoneos
sdk_sim=iphonesimulator

if [ "$config" == "Release" ]
then
  build_config=Release
  #project_derived_data_path="$solution_dir/build/Release-iphoneos"
  mobileprovision="$solution_dir/Eggies_Development.mobileprovision"
  provisioning_profile="iPhone Developer"
fi

if [ "$config" == "Adhoc" ]
then
  build_config="Ad-hoc Distribution"
  #project_derived_data_path="$solution_dir/build/Ad-hoc Distribution-iphoneos"
  mobileprovision="$solution_dir/Eggies_Adhoc.mobileprovision"
  provisioning_profile="iPhone Distribution"
fi

scheme="$1"
if [ "$scheme" == "" ]
then
  echo "build_ios.sh <scheme> <build_version>"
  echo ""
  echo "Must set scheme variable"
  echo "  ie \"GameClientLib - iOS\""
  echo "  or \"GameClientLib - iOS C++11\""
  exit 1
fi

library_os="iOS_C++"
if [[ "$scheme" == *C++11 ]]
then
  library_os="iOS_C++11"
fi

build_version="$2"
if [ "$build_version" == "" ]
then
  echo "build_ios.sh <scheme> <build_version>"
  echo ""
  echo "Must set build_version via 4 digit number"
  echo " ie \"1.6.0.1234\""
fi

build_internal_version=`echo $build_version | cut -d \".\" -f 4`
build_external_version=`echo $build_version | cut -d \".\" -f 1-3`


# Configuration
environment_name="dist"
keychain="login"
keychain_password="1309Carling"
workspace="project.xcworkspace"
info_plist="$solution_dir/Info-Eggies.plist"
product_name="Eggies"

#unused
environment_plist="$environment_name.plist"
environment_info_plist="$environment_name-Info.plist"
display_image_name="Icon-57.png"
full_size_image_name="Icon-512.png"

project_app=Eggies.app
project_ipa=$project_app-$build_version.ipa
project_dsym_zip=$project_app-$build_version.dSYM.zip

function failed()
{
    local error=${1:-Undefined error}
    echo "Failed: $error" >&2
    exit 1
}

function validate_keychain()
{
  # unlock the keychain containing the provisioning profile's private key and set it as the default keychain
  security unlock-keychain -p "$keychain_password" "$HOME/Library/Keychains/$keychain.keychain"
  security default-keychain -s "$HOME/Library/Keychains/$keychain.keychain"
  
  #describe the available provisioning profiles
  echo "Available provisioning profiles"
  security find-identity -p codesigning -v

  #verify that the requested provisioning profile can be found
  (security find-certificate -a -c "$provisioning_profile" -Z | grep ^SHA-1) || failed provisioning_profile  
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

function increment_version()
{
  #cd "MyApp"
  #pushd $project_dir
  pushd $solution_dir
  agvtool -noscm new-version -all $build_external_version

  # for some reason the tool above fails to set ver in plist...
  # so force it below
  defaults write `pwd`/Info-Eggies CFBundleVersion $build_external_version
  defaults read `pwd`/Info-Eggies CFBundleVersion
  
  popd
  #cd ..
}

function stamp_version()
{
  echo "$build_version" >../content/config/version.txt
}

function set_environment()
{
  echo "Skipping set_environment"

  #copy the info plist for the selected environment into place
#  cp -v "MyApp/$environment_info_plist" $info_plist || failed environment_plist
  #copy the environment settings plist into place
#  cp -v "MyApp/$environment_plist" "MyApp/environment.plist" || failed environment

  #extract settings from the Info.plist file
#  info_plist_domain=$(ls $info_plist | sed -e 's/\.plist//')
#echo INFO_PLIST_DOMAIN: $info_plist_domain
#  short_version_string=$(defaults read "$info_plist_domain" CFBundleShortVersionString)
#  bundle_identifier=$(defaults read "$info_plist_domain" CFBundleIdentifier)
#  echo "Environment set to $bundle_identifier at version $short_version_string"
}

function build_app()
{
  local devired_data_path="$HOME/Library/Developer/Xcode/DerivedData"

  #get the name of the workspace to be build, used as the prefix of the DerivedData directory for this build
  local workspace_name=$(echo "$workspace" | sed -n 's/\([^\.]\{1,\}\)\.xcworkspace/\1/p')
  #build the app
  echo "Running xcodebuild > xcodebuild_output ..."

#  disabled overriding PRODUCT_NAME, setting applies to all built targets in Xcode 4 which renames static library target dependencies and breaks linking
#  xcodebuild -verbose -workspace "$workspace" -scheme "$scheme" -sdk iphoneos -configuration Release clean build PRODUCT_NAME="$product_name" >| xcodebuild_output
#  xcodebuild -verbose -workspace "$workspace" -scheme "$scheme" -sdk iphoneos -configuration Release clean build >| xcodebuild_output


  # create arm version of the library
  #cp ../GameClientLib/build/Release-iphoneos/libGameClientLib.a ./libGameClientLib_ios.a
  output_folder="`xcodebuild -project $project_dir -scheme "$scheme" -sdk "$sdk" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "$scheme" -sdk "$sdk" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  cp "$output_folder/libGameClientLib.a" ./libGameClientLib_ios.a

  # create i386/simulator version of the library
  output_folder="`xcodebuild -project $project_dir -scheme "$scheme" -sdk "$sdk_sim" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "$scheme" -sdk "$sdk_sim" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  cp "$output_folder/libGameClientLib.a" ./libGameClientLib_i386.a

  # smash arm + i386 versions into a single lib file
  lipo -create libGameClientLib_ios.a libGameClientLib_i386.a -output libGameClientLib.a

  rm -rf brainCloud
  mkdir brainCloud
  mkdir brainCloud/include
  mkdir brainCloud/libs
  mkdir brainCloud/src
  mkdir brainCloud/thirdparty

  mv libGameClientLib.a brainCloud/libs/libBrainCloudClient.a
  cp ../GameClientLib/lib/curl/iOScURL-7.39.0/libcurl.a brainCloud/libs
  cp ../GameClientLib/src/ApiHeaders/*.h brainCloud/include

  # copy in the wrapper classes
  cp -r ../BrainCloudWrapper/* brainCloud/src

  # copy in the thirdparty dependencies
  cp -r ../GameClientLib/lib/jsoncpp-1.0.0 brainCloud/thirdparty
  mkdir brainCloud/thirdparty/iOScURL-7.39.0
  cp -r ../GameClientLib/lib/curl/iOScURL-7.39.0/iOScURL/curl brainCloud/thirdparty/iOScURL-7.39.0

  cp ../../Common/docs/README.TXT brainCloud

  zip -r $artifacts_dir/brainCloudClient_${library_os}_${build_version}.zip brainCloud

  rm libGameClientLib*.a
  rm -rf brainCloud
}

function clean_artifacts
{
  rm -rf $artifacts_dir
  mkdir $artifacts_dir
}

function output_header
{
  echo
  echo "TeamCity Build # $build_version"
  echo
}

# turn on shell command logging
set -x

# turn on exit on fail 
set -e

# turn on fail if something in pipeline fails
set -o pipefail

output_header
echo "**** Clean artifacts"
clean_artifacts
echo
echo "**** Describe SDKs"
describe_sdks
echo
echo "**** Describe Workspace"
describe_workspace
echo
echo "**** Set Environment"
set_environment
echo
echo "**** Increment Bundle Version"
#increment_version
echo
echo "**** Stamp version file"
#stamp_version
echo
echo "**** Build"
build_app
echo
echo "**** Complete!"

