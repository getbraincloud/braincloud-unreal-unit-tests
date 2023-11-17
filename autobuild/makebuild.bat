@ echo off
:: usage:
::      autobuild\makebuild.bat

::eg. Jenkins (no quotes, no spaces)
:: 		> set UE_INSTALL_PATH=C:\ProgramFiles\UE_5.0

:BuildPlugin
echo -- Plugin package is %WORKSPACE%\BCClient_%UE_VERSION%
call "%UE_INSTALL_PATH%\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -rocket -plugin="%WORKSPACE%\Plugins\BCClient\BCClient.uplugin" -package="%WORKSPACE%\BCClient_%UE_VERSION%" -CreateSubFolder

goto Done

:Done
:: return code for tests
exit /B %errorlevel%
