@echo OFF

set BRANCH=%1
if [%BRANCH%]==[] (
	for /f %%i in ('git config -f .gitmodules --get submodule.Plugins/BCClient.branch') do set BRANCH=%%i
		if [%BRANCH%]==[] (
		set BRANCH=master
	)
)

pushd Plugins\BCClient

echo Checking out %BRANCH% to %CD%
git checkout %BRANCH%
git pull

popd

