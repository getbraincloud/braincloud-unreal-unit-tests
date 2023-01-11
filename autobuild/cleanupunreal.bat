@ echo OFF

::"Binaries","Intermediate","Plugins\BCClient\Binaries",Plugins\BCClient\Intermediate","Plugins\VaRest\Binaries","Plugins\VaRest\Intermediate"

for /d %%a in ("Binaries","Intermediate") do (
	if exist %%a ( 
		set found=1
		rmdir /S /Q  %%a
	)
)
if [%found]==[1] echo Unreal build file have been removed.

exit /b %errorlevel%