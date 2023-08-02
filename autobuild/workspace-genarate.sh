#!/bin/bash

# SET VARS:
# export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_5.1'
# export WORKSPACE=$PWD

"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh" -projectfiles -project="${WORKSPACE}/BCSubsystem.uproject" -editor -progress 
