@ echo off
:: usage:
::      autobuild\makebuild.bat BCSubsystem Win64

::eg. Jenkins (no quotes, no spaces)
:: 		> set UE_INSTALL_PATH=C:\ProgramFiles\UE_5.0

if not defined UE_INSTALL_PATH goto Path_Error

set PROJECTNAME=%~1
if "%PROJECTNAME%" == "" goto Proj_Error

if "%~3%" == "-pack" goto BuildPlugin

:BuildApp
:: todo modify the GameDefaultMap in config file
call "%UE_INSTALL_PATH%\Engine\Binaries\DotNet\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="%WORKSPACE%\%PROJECTNAME%.uproject" -game -rocket -progress

call "%UE_INSTALL_PATH%\Engine\Build\BatchFiles\Build.bat" %PROJECTNAME% Win64 Development -Project="%WORKSPACE%\%PROJECTNAME%.uproject" -WaitMutex -FromMsBuild

echo -- Archive folder is %WORKSPACE%\%PROJECTNAME%_Win64_%UE_VERSION%
call "%UE_INSTALL_PATH%\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -rocket -nocompile -compileeditor -installed -nop4 -project="%WORKSPACE%\%PROJECTNAME%.uproject" -cook -stage -archive -archivedirectory="%WORKSPACE%\%PROJECTNAME%_Win64_%UE_VERSION%" -package -clientconfig=Development -clean -pak -prereqs -distribution -nodebuginfo -targetplatform=Win64 -build -utf8output

goto Done

:BuildPlugin
echo -- Plugin package is %WORKSPACE%\BCClient_Win64_%UE_VERSION%
call "%UE_INSTALL_PATH%\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -rocket -plugin="%WORKSPACE%\Plugins\BCClient\BCClient.uplugin" -package="%WORKSPACE%\BCClient_Win64_%UE_VERSION%" -CreateSubFolder

goto Done

:Done
:: return code for tests
exit /B %errorlevel%

:Proj_Error
echo "Pass project name."
exit /B 1