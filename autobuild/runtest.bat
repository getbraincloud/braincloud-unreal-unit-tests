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
::call "autobuild\cleanupunreal.bat"

echo -- Generating project files.
::call "%UE_INSTALL_PATH%\Engine\Binaries\DotNet\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="%WORKSPACE%\BCSubsystem.uproject" -game -rocket -progress

echo "-- Building project now."
call "%UE_INSTALL_PATH%\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="%WORKSPACE%\BCSubsystem.uproject" -unrealexe=%UE_EDITOR_CMD%.exe -rocket -noP4 -platform=Win64 -clientconfig=Development -serverconfig=Development -build  -WaitMutex

:: run specified test
echo -- Executing now. Automation RunTests %TESTNAME%
echo Report path is %WORKSPACE%\artifacts\TestResults_Win64_%UE_VERSION%
echo Log path is %WORKSPACE%\artifacts\TestLog_Win64_%UE_VERSION%.log
"%UE_INSTALL_PATH%\Engine\Binaries\Win64\%UE_EDITOR_CMD%.exe" "%WORKSPACE%\BCSubsystem.uproject" -client -nosplash -unattended -nopause -nosound -NullRHI -nocontentbrowser -ExecCmds="Automation RunTests %TESTNAME%;quit" -TestExit="Automation Test Queue Empty" -ReportExportPath="%WORKSPACE%\artifacts\TestResults_Win64_%UE_VERSION%" -stdout -abslog="%WORKSPACE%\artifacts\TestLog_Win64_%UE_VERSION%.log"

:: return code for tests
exit /B %errorlevel%

:Path_Error
echo "Set UE_INSTALL_PATH."

exit /B 1