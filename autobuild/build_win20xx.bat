setlocal
rmdir /s /q artifacts

if "%build_version%" == "" goto set_version
if "%vc_version%" == "" goto set_vc_version

mkdir artifacts
cd artifacts
mkdir build
cd build

mkdir debug
cd debug
cmake -D USE_CPPREST:BOOL=0 -D BUILD_TESTS:BOOL=0 -D gtest_force_shared_crt:BOOL=1 -DCMAKE_BUILD_TYPE=Debug -G "NMake Makefiles" ..\..\..\..
if %errorlevel% neq 0 exit /b %errorlevel%
nmake
if %errorlevel% neq 0 exit /b %errorlevel%

cd ..
mkdir release
cd release
cmake -D USE_CPPREST:BOOL=0 -D BUILD_TESTS:BOOL=0 -D gtest_force_shared_crt:BOOL=1 -DCMAKE_BUILD_TYPE=Release -G "NMake Makefiles" ..\..\..\..
if %errorlevel% neq 0 exit /b %errorlevel%
nmake
if %errorlevel% neq 0 exit /b %errorlevel%

cd ..\..
mkdir brainCloud
mkdir brainCloud\include
mkdir brainCloud\lib
mkdir brainCloud\src
mkdir brainCloud\thirdparty

xcopy /s /i /y ..\..\include\* brainCloud\include
copy build\release\brainCloud.lib brainCloud\lib
copy build\debug\brainCloud.lib brainCloud\lib\brainCloud_debug.lib
copy ..\..\lib\win32\pthread-w32-2-8-0\Pre-built.2\lib\pthreadVCE2.dll brainCloud\lib\pthreadVCE2.dll
copy ..\..\lib\win32\curl-7.44.0_win32\libcurl_a.lib brainCloud\lib\libcurl_a.lib
copy ..\..\lib\win32\curl-7.44.0_win32\libcurl_a.lib brainCloud\lib\libcurl_a_debug.lib
rem xcopy /y /i ..\..\BrainCloudWrapper\BrainCloudWrapper.* brainCloud\src
xcopy /s /i /y ..\..\lib\jsoncpp-1.0.0 brainCloud\thirdparty\jsoncpp-1.0.0
mkdir brainCloud\thirdparty\curl-7.44.0
mkdir brainCloud\thirdparty\curl-7.44.0\include
xcopy /s /i /y ..\..\lib\win32\curl-7.44.0\include brainCloud\thirdparty\curl-7.44.0\include

copy /y ..\docs\README.txt brainCloud
cd brainCloud
powershell -Command "(Get-Content README.txt) | ForEach-Object { $_ -replace \"Platform: xxx\", \"Platform: C++ (VC %vc_version%)\" } | Set-Content README.txt"
powershell -Command "(Get-Content README.txt) | ForEach-Object { $_ -replace \"Version: x.x.x\", \"Version: %build_version%\" } | Set-Content README.txt"
cd ..

"C:\Program Files (x86)\7-Zip\7z.exe" a "brainCloudClient_Win32_VC%vc_version%_C++_%build_version%.zip" brainCloud
del /f brainCloud\README.txt 

goto eof

:set_version
echo "You must set a build_version environment variable"
exit /b 1

:set_vc_version
echo "You must set a vc_version environment variable"
exit /b 1

:eof
endlocal
