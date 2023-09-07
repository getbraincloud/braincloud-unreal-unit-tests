#!/bin/bash
# usage:
#      autobuild/makebuild.sh RelayTestApp MAC
#      autobuild/makebuild.sh RelayTestApp IOS
#      autobuild/makebuild.sh RelayTestApp ANDROID

# make sure to set the install path of your engine version
#       export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_4.27'
#       export UE_VERSION=5.1
#       export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_5.1'
#		 export WORKSPACE=$PWD #(this is examples root folder)

# use options nosign for android and distribution for ios

PROJECTNAME=${1}
TARGET=${2}
ARTIFACTS=${3:-artifacts}

if [[ $UE_VERSION == "4.27" ]];
then
	UE4String='-ue4exe="${UE_INSTALL_PATH}/Engine/Binaries/Mac/UE4Editor.app/Contents/MacOS/UE4Editor"'
fi
if [[ "$2" ==  "IOS" ]];
then
	ModeString='-distribution'
fi

mkdir -p "$WORKSPACE/$ARTIFACTS/"
mkdir -p "$WORKSPACE/$ARTIFACTS/${PROJECTNAME}-${TARGET}"

# replace GameDefaultMap in .uproject
sed -i '' "s/GameDefaultMap=.*$/GameDefaultMap=\/Game\/AndroidTest.AndroidTest/g" $WORKSPACE/Config/DefaultEngine.ini

#"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh" -projectfiles -project="$WORKSPACE/$PROJECTNAME.uproject" -game  -progress

"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/Mac/Build.sh" ${PROJECTNAME}Editor Mac Development -Project="$WORKSPACE/$PROJECTNAME.uproject"

"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildCookRun -rocket -nocompile -compileeditor -installed -nop4 -project="$WORKSPACE/$PROJECTNAME.uproject" -cook -stage -archive -archivedirectory="$WORKSPACE/artifacts/${PROJECTNAME}-${TARGET}" -package -clientconfig=Development -clean -pak -prereqs  ${ModeString} -nodebuginfo -targetplatform=${TARGET} -build -target=${PROJECTNAME} -utf8output

sed -i '' "s/GameDefaultMap=.*$/GameDefaultMap=\/Game\/EmptyWorld.EmptyWorld/g" $WORKSPACE/Config/DefaultEngine.ini
