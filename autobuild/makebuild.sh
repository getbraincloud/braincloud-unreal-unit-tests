#!/bin/bash
# usage:
#      autobuild/makebuild.sh BCSubsystem MAC
#      autobuild/makebuild.sh BCSubsystem MAC -pack
#      autobuild/makebuild.sh BCSubsystem IOS
#      autobuild/makebuild.sh BCSubsystem ANDROID
#      autobuild/makebuild.sh BCSubsystem ANDROID AndroidTest

# make sure to set the install path of your engine version
#       export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_4.27'
#       export UE_VERSION=5.1
#       export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_5.1'
#		 export WORKSPACE=$PWD #(this is examples root folder)

# use options nosign for android and distribution for ios

PROJECTNAME=${1:-BCSubsystem}
TARGET=${2:-MAC}
GAMEMAP=${3:-AndroidTest}

if [[ $UE_VERSION == "4.27" ]];
then
	UE4String='-ue4exe="${UE_INSTALL_PATH}/Engine/Binaries/Mac/UE4Editor.app/Contents/MacOS/UE4Editor"'
fi
if [[ "$2" ==  "IOS" ]];
then
	ModeString='-distribution'
fi

if [[ "$3" != "-pack" ]];
then
  # optional: add commandline args for the game exe (saved in UECommandlLine.txt)
  # eg. -cmdline="${GAMEMAP} -Messaging"
  "${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildCookRun -rocket -nocompile -installed -nop4 -project="$WORKSPACE/$PROJECTNAME.uproject" -map=${GAMEMAP} -cook -stage -archive -archivedirectory="$WORKSPACE/${PROJECTNAME}_${TARGET}_${UE_VERSION}" -package -clientconfig=Development -clean -pak -prereqs  ${ModeString} -nodebuginfo -targetplatform=${TARGET} -build -target=${PROJECTNAME} -utf8output
else
  "${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin -rocket -plugin="$WORKSPACE/Plugins/BCClient/BCClient.uplugin" -package="$WORKSPACE/BCClient_${TARGET}_${UE_VERSION}" -CreateSubFolder
  # todo: copy Readme etc into folder
fi
