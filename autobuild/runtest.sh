#!/bin/bash
# usage:
#      autobuild/runtest.sh /Volumes/Project/BrainCloudUnreal/tests-unreal-dev/ RunSet

export UNREAL_BIN="/Users/Shared/Epic Games/UE_4.27/Engine/Binaries/Mac"
export PROJECT_NAME="BCSubsystem"
export WORKSPACE=${1}
export TEST_NAME=${2}

# need to build c++ source code here

"$UNREAL_BIN/ue4Editor-Cmd" "$WORKSPACE/$PROJECT_NAME.uproject" -game -nosplash -nosound -unattended -nopause -nocontentbrowser -NullRHI -ExecCmds=\"Automation RunTests $TEST_NAME\" -testexit=\"Automation Test Queue Empty\" -log=RunTests.log -ReportExportPath=\"$WORKSPACE/Artifacts\"


