@ echo OFF
rmdir /S /Q  Binaries > null.txt
rmdir /S /Q  Intermediate > null.txt
rmdir /S /Q  Plugins\BCClient\Binaries > null.txt
rmdir /S /Q  Plugins\BCClient\Intermediate > null.txt
rmdir /S /Q  Plugins\VaRest\Binaries > null.txt
rmdir /S /Q  Plugins\VaRest\Intermediate > null.txt
del /s /f /q null.txt
echo Unreal build file have been removed.

exit /B 0