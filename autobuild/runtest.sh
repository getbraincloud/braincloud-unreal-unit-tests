export UNREAL_BIN="/Users/Shared/Epic Games/UE_4.27/Engine/Binaries/Mac"
export PROJECT_NAME="BCSubsystem"
export WORKSPACE="/Volumes/Project/release-4.11/websock/braincloud-unreal"
export TEST_NAME="_TestRun"

"$UNREAL_BIN/UE4Editor-Cmd" "$WORKSPACE/$PROJECT_NAME.uproject" -game -nosplash -nosound -unattended -nopause -nocontentbrowser -NullRHI -ExecCmds=\"Automation RunTests $TEST_NAME\" -testexit=\"Automation Test Queue Empty\" -log -log=RunTests.log -ReportExportPath=\"$WORKSPACE/Saved/UnitTestsReport\"

