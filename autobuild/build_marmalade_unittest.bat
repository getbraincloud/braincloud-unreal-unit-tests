setlocal
@echo off

rmdir /s /q artifacts

if "%build_version%" == "" goto set_version
rem if "%VS100COMNTOOLS%" == "" goto set_vspaths
if "%VS140COMNTOOLS%" == "" goto set_vspaths
if not "%build_quick%"  == "" echo "QUICK BUILD: INCREMENTAL BUILD OF X86 DEBUG"

if "%build_quick%" == "" (
    set FLAGS="/t:rebuild"
) else (
    set FLAGS="/t:build"    
)

mkdir artifacts
mkdir artifacts\brainCloud

pushd ..\solutions\marmalade

rem ############## brainCloud -- vs2015 ##################### 

call "%VS140COMNTOOLS%\vsvars32.bat" || goto :error
set SLN=brainCloud_vc14x.sln
call cmd /c mkb --non-interactive --buildenv VC14X --no-ide brainCloud.mkb || goto :error
cd build_braincloud_vc14x

if "%build_quick%" == "" (
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC AARCH64 Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC AARCH64 Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC ARM Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC ARM Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86 ANDROID Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86 ANDROID Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86_64 NaCL Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86_64 NaCL Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="x86 Release" || goto :error
)

msbuild.exe %SLN% %FLAGS% /p:Configuration="x86 Debug" || goto :error
cd ..

rem ############## googletest -- vs2015 ##################### 

cd googletest
set SLN=googletest_vc14x.sln
call cmd /c mkb --non-interactive --buildenv VC14X --no-ide googletest.mkb || goto :error
cd build_googletest_vc14x

if "%build_quick%" == "" (
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC AARCH64 Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC AARCH64 Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC ARM Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC ARM Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86 ANDROID Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86 ANDROID Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86_64 NaCL Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86_64 NaCL Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="x86 Release" || goto :error
)

msbuild.exe %SLN% %FLAGS% /p:Configuration="x86 Debug" || goto :error
cd ..\..

rem ############## unittest -- vs2015 ##################### 

set SLN=brainCloudUnitTest_vc14x.sln
call cmd /c mkb --non-interactive --buildenv VC14X --no-ide brainCloudUnitTest.mkb || goto :error
cd build_brainCloudUnitTest_vc14x

if "%build_quick%" == "" (
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC AARCH64 Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC AARCH64 Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC ARM Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC ARM Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86 ANDROID Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86 ANDROID Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86_64 NaCL Debug" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC X86_64 NaCL Release" || goto :error
    msbuild.exe %SLN% %FLAGS% /p:Configuration="x86 Release" || goto :error
)

msbuild.exe %SLN% %FLAGS% /p:Configuration="x86 Debug" || goto :error
cd ..

popd

cd artifacts
xcopy /y /i ..\..\solutions\marmalade\build_braincloudunittest_vc14x\brainCloudUnitTest_vc14x_debug.via .
"C:\Program Files (x86)\7-Zip\7z.exe" a "brainCloudClient_Marmalade_C++_UnitTest_%build_version%.zip" brainCloudUnitTest_vc14x_debug.via

rem call "%S3E_DIR%\win32\s3e_simulator_debug.exe" -via:"c:\p4\projMetagame\Development\Client\C++GameClient\solutions\marmalade\build_braincloudunittest_vc14x\brainCloudUnitTest_vc14x_debug.via"
goto eof

goto eof

:set_version
echo "You must set a build_version environment variable"
exit /b 1

:set_version
echo "You must have visual studio paths set"
exit /b 1

:error
echo Failed with error #%errorlevel%.
exit /b %errorlevel%

:eof
endlocal