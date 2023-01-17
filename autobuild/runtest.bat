@ echo OFF
:: Run commandline tests
:: usage:
::      autobuild\runtest.bat
::      autobuild\runtest.bat RunSet
::      autobuild\runtest.bat Authentication clean

:: set UE_RUNUAT_PATH="D:\Program Files\UE_5.0\Engine\Build\BatchFiles\RunUAT.bat"
:: set UE_EDITOR_PATH="D:\Program Files\UE_5.0\Engine\Binaries\Win64\UE4Editor-cmd.exe"

if not defined UE_RUNUAT_PATH goto Path_Error
if not defined UE_INSTALL_PATH goto Path_Error

set PROJECTNAME=BCSubsystem
if not defined WORKSPACE set WORKSPACE=%cd%
if not defined TESTNAME (
	set TESTNAME=%1
	if [%TESTNAME%]==[] set TESTNAME=Test_
)
:: make clean option
::cmd/c "autobuild\cleanupunreal.bat"

:: need to build c++ source code here
cmd /c "%UE_RUNUAT_PATH%" BuildCookRun -project="%WORKSPACE%\%PROJECTNAME%.uproject" -noP4 -platform=Win64 -clientconfig=Development -build 

:: run specified test
cmd /c "%UE_EDITOR_PATH%" "%WORKSPACE%\%PROJECTNAME%.uproject" -nosplash -Unattended -nopause -nosound -NullRHI -nocontentbrowser -ExecCmds="Automation RunTests "%TESTNAME%";quit" -TestExit="Automation Test Queue Empty" -ReportOutputPath="%WORKSPACE%\TestResults" -log -Log="RunTests.log

:: return code for tests
exit /B %errorlevel%

:Path_Error
echo "Set EPIC_LAUNCHER_PATH and UE_INSTALL_PATH."

exit /B 1