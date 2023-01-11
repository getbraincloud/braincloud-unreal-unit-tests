#!/bin/bash
# usage:
#      autobuild/runtest.sh RunSet

TEST_NAME=${1}

"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/Mac/Build.sh" BCSubsystemEditor Mac Development -Project="$WORKSPACE/BCSubsystem.uproject" 

# need to build c++ source code here
"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildCookRun -project="$WORKSPACE/BCSubsystem.uproject"   -noP4 -platform=Mac -clientconfig=Development -build 
 #"$UNREAL_Build" -ModuleWithSuffix=$PROJECT_NAME,8348 $PROJECT_NAME Mac Development -Project="$WORKSPACE/$PROJECT_NAME.uproject" "$WORKSPACE/$PROJECT_NAME.uproject"  -IgnoreJunk

# run specified test
"${UE_INSTALL_PATH}/Engine/Binaries/Mac/${UE_EDITOR_CMD}" "$WORKSPACE/BCSubsystem.uproject" -game -nosplash -nosound -unattended -nopause -nocontentbrowser -NullRHI -ExecCmds=\"Automation RunTests $TEST_NAME\" -testexit=\"Automation Test Queue Empty\" -log=RunTests.log -ReportExportPath=\"$WORKSPACE/Artifacts\"


