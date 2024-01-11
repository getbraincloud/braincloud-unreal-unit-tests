@echo OFF

set SUBMODULE=%1
set BRANCH=%2

if [%BRANCH%]==[] (
	for /f %%i in ('git config -f .gitmodules --get submodule.%SUBMODULE:\=/%.branch') do (set BRANCH=%%i)
)

if [%BRANCH%]==[] (
	set BRANCH=master
)


pushd %SUBMODULE:/=\%

echo Checking out %BRANCH% to %SUBMODULE:/=\%
git fetch
git checkout %BRANCH%
git pull

popd