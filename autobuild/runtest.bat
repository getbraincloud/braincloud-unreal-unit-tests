@ echo OFF
:: Run commandline tests
:: usage:
::      autobuild\runtest.bat
::      autobuild\runtest.bat Authentication

::eg. Jenkins
:: 		> set UE_INSTALL_PATH=C:\ProgramFiles\UE_5.1
::      > set UE_EDITOR_CMD=UnrealEditor
:: 		> set WORKSPACE=%cd%

if not defined UE_INSTALL_PATH goto Path_Error

set TESTNAME=%1
if [%TESTNAME%]==[] set TESTNAME=Test_

:: make clean option
::cmd/c "autobuild\cleanupunreal.bat"

echo -- Generating project files.
call "%UE_INSTALL_PATH%\Engine\Binaries\DotNet\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="%WORKSPACE%\%PROJECTNAME%.uproject" -game -rocket -progress

echo "-- Building project now."
call "%UE_INSTALL_PATH%\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="%WORKSPACE%\BCSubsystem.uproject" -unrealexe=%UE_EDITOR_CMD%.exe -noP4 -platform=Win64 -serverconfig=Development -build  -WaitMutex -FromMsBuild

:: run specified test
echo -- Extecuting now. Automation RunTests %TESTNAME%
echo Report path is %WORKSPACE%\TestResults_Win64_%UE_VERSION%
echo Log path is saved\logs\TestLog_Win64_%UE_VERSION%.log
call "%UE_INSTALL_PATH%\Engine\Binaries\Win64\%UE_EDITOR_CMD%.exe" "%WORKSPACE%\BCSubsystem.uproject" -server -nosplash -unattended -nopause -nosound -NullRHI -nocontentbrowser -ExecCmds="Automation RunTests %TESTNAME%;quit" -TestExit="Automation Test Queue Empty" -ReportExportPath="%WORKSPACE%\TestResults_Win64_%UE_VERSION%" -log=TestLog_Win64_%UE_VERSION%.log

:: return code for tests
exit /B %errorlevel%

:Path_Error
echo "Set UE_INSTALL_PATH."

exit /B 1