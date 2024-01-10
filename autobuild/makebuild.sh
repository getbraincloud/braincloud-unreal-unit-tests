#!/bin/bash
# usage:
#      autobuild/makebuild.sh

"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin -rocket -plugin="$WORKSPACE/Plugins/BCClient/BCClient.uplugin" -package="$WORKSPACE/BCClient_${UE_VERSION}" -CreateSubFolder
