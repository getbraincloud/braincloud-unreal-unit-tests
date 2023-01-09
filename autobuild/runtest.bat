@ echo OFF
:: Run commandline tests
:: usage:
::      autobuild\runtest.bat Test_
::      autobuild\runtest.bat RunSet
::      autobuild\runtest.bat Authentication

:: set UE_RUNUAT_PATH="D:\Program Files\UE_5.0\Engine\Build\BatchFiles\RunUAT.bat"
:: set UE_EDITOR_PATH="D:\Program Files\UE_5.0\Engine\Binaries\Win64\UE4Editor-cmd.exe"

set PROJECTNAME=BCSubsystem
set WORKSPACE=%cd%
set TESTNAME=%1

:: todo make clean option
if %2 == clean call "autobuild\cleanupunreal.bat"

:: todo specify engine path

:: need to build c++ source code here
%UE_RUNUAT_PATH% BuildCookRun -project="%WORKSPACE%\%PROJECTNAME%.uproject" -noP4 -platform=Win64 -clientconfig=Development -build 

:: run specified test
%UE_EDITOR_PATH% "%WORKSPACE%\%PROJECTNAME%.uproject" -nosplash -Unattended -nopause -nosound -NullRHI -nocontentbrowser -ExecCmds="Automation RunTests "%TESTNAME%";quit" -TestExit="Automation Test Queue Empty" -ReportOutputPath="%WORKSPACE%\TestResults" -log -Log="RunTests.log

:: todo return code for tests
exit /B %errorlevel%