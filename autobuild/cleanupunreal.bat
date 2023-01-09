@ echo OFF
rmdir /S /Q  Binaries > nul
rmdir /S /Q  Intermediate > nul
rmdir /S /Q  Plugins\BCClient\Binaries > nul
rmdir /S /Q  Plugins\BCClient\Intermediate > nul
rmdir /S /Q  Plugins\VaRest\Binaries > nul
rmdir /S /Q  Plugins\VaRest\Intermediate > nul

echo Unreal build file have been removed.

exit /B %errorlevel%