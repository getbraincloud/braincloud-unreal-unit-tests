@ echo OFF
:: switch project to unreal version
:: usage:
::      autobuild\switch_project.bat 5.0
::      autobuild\switch_project.bat
::      autobuild\switch_project.bat 4.27

:: example paths
::set EPIC_LAUNCHER_PATH="C:\Program Files (x86)\Epic Games\Launcher"
::set UE_INSTALL_PATH="D:\Program Files\UE_%UE_VERSION%"
::set UE_INSTALL_PATH="C:\Program Files\Epic Games\UE_5.1"

if not defined EPIC_LAUNCHER_PATH goto Path_Error
if not defined UE_INSTALL_PATH goto Path_Error

if not defined UE_VERSION set UE_VERSION=%1
if not defined PROJECTNAME set PROJECTNAME=BCSubsystem
if not defined WORKSPACE set WORKSPACE=%cd%

:: old intermediate files will be out of date
call autobuild\cleanupunreal.bat

pushd Plugins\VaRest
if %UE_VERSION% == 4.27 (
	git checkout 4.27
) else if %UE_VERSION% == 5.0  (
	git checkout 5.0
) else (
	git checkout develop
)
popd
"%EPIC_LAUNCHER_PATH:"=%\Engine\Binaries\Win64\UnrealVersionSelector.exe" /switchversionsilent "%WORKSPACE%\%PROJECTNAME%.uproject" %UE_INSTALL_PATH%

exit /b 0

:Path_Error
echo "Set EPIC_LAUNCHER_PATH and UE_INSTALL_PATH."

exit /B 1