@ echo OFF

for /d %%a in ("Binaries","Intermediate","Saved\Automation","Saved\Autosaves","Saved\Collections","Saved\Config","Saved\Crashes","Saved\SaveGames","DerivedDataCache","Plugins\BCClient\Binaries","Plugins\BCClient\Intermediate","Plugins\VaRest\Binaries","Plugins\VaRest\Intermediate") do (
	if exist %%a ( 
		rmdir /S /Q  %%a
	)
)
echo Unreal build file have been removed.

exit /b %errorlevel%