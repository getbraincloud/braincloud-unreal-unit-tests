@ echo off
:: usage:
::      autobuild\makebuild.bat

::eg. Jenkins (no quotes, no spaces)
:: 		> set UE_INSTALL_PATH=C:\ProgramFiles\UE_5.0

if not defined UE_INSTALL_PATH goto Path_Error

set TARGETS=%1
if [%TARGETS%]==[] set TARGETS=Win64

:BuildPlugin
echo -- Plugin package is %WORKSPACE%\artifacts\BCClient_%UE_VERSION%
if [%UE_VERSION%]==[4.27] set OPTS=-vs2019
call "%UE_INSTALL_PATH%\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -plugin="%WORKSPACE%\Plugins\BCClient\BCClient.uplugin" -targetplatforms=%TARGETS% %OPTS% -package="%WORKSPACE%\artifacts\BCClient_%UE_VERSION%" -CreateSubFolder

goto Done

:Done
:: return code for tests
exit /B %errorlevel%

:Path_Error
echo Please set UE_INSTALL_PATH.
exit /B 1

