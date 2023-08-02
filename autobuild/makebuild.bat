git submodule update --remote %PROJECTNAME%/Plugins/BCClient
rmdir /s /q %WORKSPACE%\%PROJECTNAME%_Unreal_WindowsBuild
del /q %WORKSPACE%\%PROJECTNAME%_Unreal_WindowsBuild.zip
mkdir %WORKSPACE%\%PROJECTNAME%_Unreal_WindowsBuild

"D:\Program Files\UE_5.0\Engine\Binaries\DotNet\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="%WORKSPACE%\%PROJECTNAME%\%PROJECTNAME%.uproject" -game -rocket -progress 

"D:\Program Files\UE_5.0\Engine\Build\BatchFiles\Build.bat" %PROJECTNAME% Win64 Development -Project="%WORKSPACE%\%PROJECTNAME%\%PROJECTNAME%.uproject" -WaitMutex -FromMsBuild

"D:\Program Files\UE_5.0\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -rocket -nocompile -compileeditor -installed -nop4 -project="%WORKSPACE%\%PROJECTNAME%\%PROJECTNAME%.uproject" -cook -stage -archive -archivedirectory="%WORKSPACE%\%PROJECTNAME%_Unreal_WindowsBuild" -package -clientconfig=Development -ue4exe=UE4Editor-Cmd.exe -clean -pak -prereqs -distribution -nodebuginfo -targetplatform=Win64 -build -utf8output 

:: zip this: ${PROJECTNAME}_Unreal_WindowsBuild
:: archive that: ${PROJECTNAME}_Unreal_WindowsBuild.zip