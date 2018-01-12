setlocal
rmdir /s /q artifacts

mkdir artifacts
cd artifacts
mkdir build
cd build

mkdir debug
cd debug
cmake ..\..\..\..
if %errorlevel% neq 0 exit /b %errorlevel%
cmake --build . --config Debug
if %errorlevel% neq 0 exit /b %errorlevel%

cd ..
mkdir release
cd release
cmake ..\..\..\..
if %errorlevel% neq 0 exit /b %errorlevel%
cmake --build . --config Release
if %errorlevel% neq 0 exit /b %errorlevel%

cd ..\..
mkdir brainCloud
mkdir brainCloud\include
mkdir brainCloud\lib
mkdir brainCloud\src
mkdir brainCloud\thirdparty

xcopy /s /i /y ..\..\include\* brainCloud\include
xcopy /s /i /y ..\..\lib\jsoncpp-1.0.0 brainCloud\thirdparty\jsoncpp-1.0.0

endlocal
