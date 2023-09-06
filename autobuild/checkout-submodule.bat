@ echo off
:: && setlocal EnableDelayedExpansion

if exist "Plugins\BCClient" (
    for /f %%i in ('git config -f .gitmodules --get submodule.Plugins/BCClient.branch') do set BRANCH=%%i
    pushd Plugins/BCClient

	for /f %%i in ('git diff --compact-summary .') do set STR=%%i
    if [%STR%]==[] (
			echo "Folder has mods"
		) else (
		    if [%1]==[] git checkout %BRANCH%
		    else git checkout %1
			git pull
		)
		popd				
)
else echo "Folder not exists"

