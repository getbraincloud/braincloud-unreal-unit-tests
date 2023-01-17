#!/bin/bash
# usage:
#      autobuild/runtest.sh RunSet

# SET VARS:
# export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_5.1'
# export UE_EDITOR_CMD='UnrealEditor-Cmd'
# export WORKSPACE=$PWD

echo UE_INSTALL_PATH is $UE_INSTALL_PATH
echo UE_EDITOR_CMD is $UE_EDITOR_CMD
echo WORKSPACE is $WORKSPACE

TEST=${1}

# need to build c++ source code here
"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/Mac/Build.sh" BCSubsystemEditor Mac Development -Project="$WORKSPACE/BCSubsystem.uproject" 

# need to build project here
"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildCookRun -project="$WORKSPACE/BCSubsystem.uproject"   -noP4 -platform=Mac -clientconfig=Development -build 

# run specified test
"${UE_INSTALL_PATH}/Engine/Binaries/Mac/${UE_EDITOR_CMD}" "$WORKSPACE/BCSubsystem.uproject" -game -nosplash -nosound -unattended -nopause -nocontentbrowser -NullRHI -ExecCmds=\"Automation RunTests $TEST\" -testexit=\"Automation Test Queue Empty\" -log=RunTests.log -ReportOutputPath=\"${WORKSPACE}/TestResults\" -ue4exe=\"/Users/Shared/Epic Games/UE_4.27/Engine/Binaries/Mac/UE4Editor.app/Contents/MacOS/UE4Editor\"


