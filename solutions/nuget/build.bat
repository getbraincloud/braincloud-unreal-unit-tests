set TARGET=Clean;Rebuild

setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
pushd ..\windowsUniversal_vc140
nuget restore
cd brainCloud
call :build Win32 Debug brainCloud.vcxproj 	|| goto :fail
call :build Win32 Release brainCloud.vcxproj 	|| goto :fail
call :build x64 Debug brainCloud.vcxproj 	|| goto :fail
call :build x64 Release brainCloud.vcxproj 	|| goto :fail
call :build ARM Debug brainCloud.vcxproj 	|| goto :fail
call :build ARM Release brainCloud.vcxproj 	|| goto :fail
popd
endlocal

goto :eof

:build
msbuild /t:%TARGET% /P:Platform=%1 /P:Configuration=%2 %3 || goto :fail

goto :eof

:fail
exit /b 1

pause
