::@ echo OFF
:: switch project to unreal version
:: usage:
::      autobuild\switch_project.bat 5.1 "C:\Program Files (x86)\Epic Games\Launcher" "C:\Program Files\Epic Games\UE_5.1"
::      autobuild\switch_project.bat 5.0 "D:\Program Files\UE_5.0"
::      autobuild\switch_project.bat 4.27 "C:\Program Files (x86)\Epic Games\Launcher" "C:\Program Files\Epic Games\UE_4.27"

set UE_INSTALL_DIR=%3
set UE_BRANCH=%1
set EPIC_LAUNCHER_DIR=%2
set PROJECTNAME=BCSubsystem
set WORKSPACE=%cd%

::autobuild\cleanupunreal.bat

cd Plugins\VaRest
if %UE_BRANCH% == 4.27 (
	git checkout 4.27
) else if %UE_BRANCH% == 5.0  (
	git checkout 5.0
) else (
	git checkout develop
)
cd ..\..

"%EPIC_LAUNCHER_DIR:"=%\Engine\Binaries\Win64\UnrealVersionSelector.exe" /switchversionsilent "%WORKSPACE%\%PROJECTNAME%.uproject" %UE_INSTALL_DIR%
