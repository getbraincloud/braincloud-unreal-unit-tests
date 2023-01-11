#!/bin/bash
# usage:
#      autobuild/runtest.sh RunSet

export UNREAL_RunUAT="/Users/Shared/Epic Games/UE_5.1"
export UNREAL_Build="/Users/Shared/Epic Games/UE_5.1/Engine/Build/BatchFiles/Mac/Build.sh"
#export UNREAL_EditorCmd="/Users/Shared/Epic Games/UE_4.27/Engine/Binaries/Mac/ue4Editor-Cmd"
export UNREAL_EditorCmd="/Users/Shared/Epic Games/UE_5.1/Engine/Binaries/Mac/UnrealEditor-Cmd"
export WORKSPACE=$PWD
export TEST_NAME=${1}

"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/Mac/Build.sh" BCSubsystem Mac Development -Project="$WORKSPACE/BCSubsystem.uproject" 

# need to build c++ source code here
"${UE_INSTALL_PATH}/Engine/Build/BatchFiles/RunUAT.sh" BuildCookRun -project="$WORKSPACE/BCSubsystem.uproject"   -noP4 -platform=Mac -clientconfig=Development -build 
 #"$UNREAL_Build" -ModuleWithSuffix=$PROJECT_NAME,8348 $PROJECT_NAME Mac Development -Project="$WORKSPACE/$PROJECT_NAME.uproject" "$WORKSPACE/$PROJECT_NAME.uproject"  -IgnoreJunk

# run specified test
"${UE_INSTALL_PATH}/Engine/Binaries/Mac/UnrealEditor-Cmd" "$WORKSPACE/BCSubsystem.uproject" -game -nosplash -nosound -unattended -nopause -nocontentbrowser -NullRHI -ExecCmds=\"Automation RunTests $TEST_NAME\" -testexit=\"Automation Test Queue Empty\" -log=RunTests.log -ReportExportPath=\"$WORKSPACE/Artifacts\"


