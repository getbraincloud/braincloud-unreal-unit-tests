#!/bin/bash
# usage:
#      autobuild/makebuild.sh

# make sure to set the install path of your engine version
#       export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_4.27'
#       export UE_VERSION=5.1
#       export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_5.1'
#		 export WORKSPACE=$PWD #(this is examples root folder)

# use options nosign for android and distribution for ios

# eg. Mac+Android+IOS
TARGETS=${1:-Mac}

"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin -plugin="$WORKSPACE/Plugins/BCClient/BCClient.uplugin" -targetplatforms=$TARGETS -package="$WORKSPACE/artifacts/BCClient_${UE_VERSION}" -CreateSubFolder
