@echo OFF

echo Working in local directory %CD%

pushd %1

for /f %%i in ('git rev-parse --verify HEAD') do set LOCAL=%%i
echo -%LOCAL%- submodule %1  
for /f %%i in ('git rev-parse --verify origin/%2') do set REMOTE=%%i
for /f "tokens=* delims= " %%a in ("%REMOTE%") do set REMOTE=%%a
REM for /l %%a in (1,1,31) do if "!REMOTE:~-1!"==" " set REMOTE=!REMOTE:~0,-1!
echo -%REMOTE%- on branch origin/%2 

if %LOCAL% == %REMOTE% (
	echo Submodule %1 up to date with latest commit.
	set CODE=0
) else (
	echo Warning! Please run: git submodule update --remote %1
	set CODE=1
) 

popd
EXIT /B %CODE%