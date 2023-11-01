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

PROJECTNAME=${1}
TARGET=${2}
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

  "${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildCookRun -rocket -nocompile -game -nocompileeditor -installed -nop4 -project="$WORKSPACE/$PROJECTNAME.uproject" -cook -stage -archive -archivedirectory="$WORKSPACE/${PROJECTNAME}_${TARGET}_${UE_VERSION}" -package -clientconfig=Development -clean -pak -prereqs  ${ModeString} -nodebuginfo -targetplatform=${TARGET} -build -target=${PROJECTNAME} -utf8output

else
  "${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin -rocket -plugin="$WORKSPACE/Plugins/BCClient/BCClient.uplugin" -package="$WORKSPACE/BCClient_${TARGET}_${UE_VERSION}" -CreateSubFolder
fi