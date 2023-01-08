@ echo OFF
del /s /f /q Binaries > null.txt
del /s /f /q Intermediate > null.txt
del /s /f /q Plugins\BCClient\Binaries > null.txt
del /s /f /q Plugins\BCClient\Intermediate > null.txt
del /s /f /q Plugins\VaRest\Binaries > null.txt
del /s /f /q Plugins\VaRest\Intermediate > null.txt
echo Unreal build file have been removed.
