@ echo off

:: run this in your project root folder

::if not defined %BRAINCLOUD_TOOLS% goto Path_Error

set SERVER_ENVIRONMENT=internal
  
pushd %~dp0\..

set WORKSPACE=%CD%

call %BRAINCLOUD_TOOLS%\bin\copy-ids.bat Source\BCSubsystem test h %SERVER_ENVIRONMENT%

popd

exit /B 0

:Path_Error
echo "Must set BRAINCLOUD_TOOLS=~/braincloud-client-master"
exit /B 1