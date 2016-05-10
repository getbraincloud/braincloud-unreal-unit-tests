setlocal
@echo off

rmdir /s /q artifacts

if "%build_version%" == "" goto set_version
if "%VS100COMNTOOLS%" == "" goto set_vspaths
if "%VS140COMNTOOLS%" == "" goto set_vspaths
if not "%build_quick%"  == "" echo "QUICK BUILD: INCREMENTAL BUILD OF X86 DEBUG"

if "%build_quick%" == "" (
    set FLAGS="/t:rebuild"
) else (
    set FLAGS="/t:rebuild"    
)

mkdir artifacts
mkdir artifacts\brainCloud

pushd ..\solutions\marmalade

rem ############## visual studio 2015 ##################### 

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

goto :skip2010
rem ############## visual studio 2010 #####################

call "%VS100COMNTOOLS%\vsvars32.bat" || goto :error
set SLN=brainCloud_vc10x.sln
call cmd /c mkb --non-interactive --buildenv VC10X --no-ide brainCloud.mkb || goto :error
cd build_braincloud_vc10x
devenv.exe brainCloud_vc10x.vcxproj /build
msbuild.exe %SLN% %FLAGS% /p:Configuration="GCC AARCH64 Debug" || goto :error
rem %MSBUILD_VS10% %SLN% %FLAGS% /p:Configuration="GCC AARCH64 Release" || goto :error
rem %MSBUILD_VS10% %SLN% %FLAGS% /p:Configuration="GCC ARM Debug" || goto :error
rem %MSBUILD_VS10% %SLN% %FLAGS% /p:Configuration="GCC ARM Release" || goto :error
rem %MSBUILD_VS10% %SLN% %FLAGS% /p:Configuration="GCC X86 ANDROID Debug" || goto :error
rem %MSBUILD_VS10% %SLN% %FLAGS% /p:Configuration="GCC X86 ANDROID Release" || goto :error
rem %MSBUILD_VS10% %SLN% %FLAGS% /p:Configuration="GCC X86_64 NaCL Debug" || goto :error
rem %MSBUILD_VS10% %SLN% %FLAGS% /p:Configuration="GCC X86_64 NaCL Release" || goto :error
rem %MSBUILD_VS10% %SLN% %FLAGS% /p:Configuration="x86 Debug" || goto :error
rem %MSBUILD_VS10% %SLN% %FLAGS% /p:Configuration="x86 Release" || goto :error
cd ..
:skip2010

popd

cd artifacts

xcopy /y /i ..\..\solutions\marmalade\brainCloud.mkb brainCloud
xcopy /y /i ..\..\solutions\marmalade\brainCloud_package.mkf brainCloud
xcopy /y /i ..\..\solutions\marmalade\README.txt brainCloud
xcopy /s /i /y ..\..\solutions\marmalade\lib brainCloud\lib
xcopy /s /i /y ..\..\include brainCloud\include

move brainCloud\brainCloud_package.mkf brainCloud\brainCloud.mkf
move brainCloud\include brainCloud\h

"C:\Program Files (x86)\7-Zip\7z.exe" a "brainCloudClient_Marmalade_C++_%build_version%.zip" brainCloud

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