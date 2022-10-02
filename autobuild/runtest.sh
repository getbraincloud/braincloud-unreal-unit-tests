export UNREAL_BIN="/Users/Shared/Epic Games/UE_4.27/Engine/Binaries/Mac"
export PROJECT_NAME="BCSubsystem"
export WORKSPACE=${1}
export TEST_NAME=${2}

"$UNREAL_BIN/UnrealEditor-Cmd" "$WORKSPACE/$PROJECT_NAME.uproject" -game -nosplash -nosound -unattended -nopause -nocontentbrowser -NullRHI -ExecCmds=\"Automation RunTests $TEST_NAME\" -testexit=\"Automation Test Queue Empty\" -log=RunTests.log -ReportExportPath=\"$WORKSPACE/Artifacts\"


