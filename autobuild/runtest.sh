#!/bin/bash
# usage:
#      autobuild/runtest.sh RunSet

export UNREAL_RunUAT="/Users/Shared/Epic Games/UE_5.1/Engine/Build/BatchFiles/RunUAT.sh"
export UNREAL_Build="/Users/Shared/Epic Games/UE_5.1/Engine/Build/BatchFiles/Mac/Build.sh"
#export UNREAL_EditorCmd="/Users/Shared/Epic Games/UE_4.27/Engine/Binaries/Mac/ue4Editor-Cmd"
export UNREAL_EditorCmd="/Users/Shared/Epic Games/UE_5.1/Engine/Binaries/Mac/UnrealEditor-Cmd"
export PROJECT_NAME="BCSubsystem"
export WORKSPACE=$PWD
export TEST_NAME=${1}

./autobuild/cleanupunreal.sh

# need to build c++ source code here
"$UNREAL_RunUAT" BuildGame -project="$WORKSPACE/$PROJECT_NAME.uproject" -compile
 #"$UNREAL_Build" -ModuleWithSuffix=$PROJECT_NAME,8348 $PROJECT_NAME Mac Development -Project="$WORKSPACE/$PROJECT_NAME.uproject" "$WORKSPACE/$PROJECT_NAME.uproject"  -IgnoreJunk

# run specified test
"$UNREAL_EditorCmd" "$WORKSPACE/$PROJECT_NAME.uproject" -game -nosplash -nosound -unattended -nopause -nocontentbrowser -NullRHI -ExecCmds=\"Automation RunTests $TEST_NAME\" -testexit=\"Automation Test Queue Empty\" -log=RunTests.log -ReportExportPath=\"$WORKSPACE/Artifacts\"


