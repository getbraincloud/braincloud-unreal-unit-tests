#!/bin/bash
# usage:
#      autobuild/runtest.sh Test_
#      autobuild/runtest.sh Authentication

# SET VARS:
# export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_5.1'
# export UE_EDITOR_CMD='UnrealEditor-Cmd'
# export WORKSPACE=$PWD

echo UE_INSTALL_PATH is $UE_INSTALL_PATH
echo UE_EDITOR_CMD is $UE_EDITOR_CMD
echo WORKSPACE is $WORKSPACE
echo UE_VERSION is $UE_VERSION

TEST=${1:-Test_}


# need to build c++ source code here
#"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/Mac/Build.sh" BCSubsystemEditor Mac Development -Project="$WORKSPACE/BCSubsystem.uproject"

# need to build project here
"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildCookRun -project="$WORKSPACE/BCSubsystem.uproject" -noP4 -platform=Mac -clientconfig=Development -build

# option: list all tests
if [[ "$TEST" == "ListAllTests" ]];
then
  # tests are under: Project.Functional Tests.AutomatedTestMaps
  "${UE_INSTALL_PATH}/Engine/Binaries/Mac/${UE_EDITOR_CMD}" "$WORKSPACE/BCSubsystem.uproject" -game -nosplash -unattended -nopause -nosound -NullRHI -nocontentbrowser -ExecCmds="Automation List;quit" -log
  exit 0
fi

# run specified test
"${UE_INSTALL_PATH}/Engine/Binaries/Mac/${UE_EDITOR_CMD}" "$WORKSPACE/BCSubsystem.uproject" -game -nosplash -unattended -nopause -nosound -NullRHI -nocontentbrowser -ExecCmds="Automation RunTests $TEST;quit" -testexit="Automation Test Queue Empty" -ReportExportPath="$WORKSPACE/TestResults_Mac_$UE_VERSION" -log -stdout
#-abslog=$WORKSPACE/Saved/logs/TestLog_Mac_$UE_VERSION.log
