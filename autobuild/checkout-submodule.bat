@echo OFF

:: use command argument
set BRANCH=%1

:: if that's not set, use submodule branch in .gitmodules file
if [%BRANCH%]==[] (
	for /f %%i in ('git config -f .gitmodules --get submodule.Plugins/BCClient.branch') do (set BRANCH=%%i)
)

:: if that's not set, use the default branch
if [%BRANCH%]==[] (
	set BRANCH=master
)

:: go into submodule directory and checkout latest code
pushd Plugins\BCClient

echo Checking out %BRANCH% to %CD%
git checkout %BRANCH%
git pull

popd
