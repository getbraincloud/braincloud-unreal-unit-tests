#!/bin/bash
# switch project to unreal version - don't do this while Unreal Editor or xCode are running, right
# usage:
#     source autobuild/switch_project.bat 5.0
#     source autobuild/switch_project.bat
#     source autobuild/switch_project.bat 4.27

UE_VERSION=$1
if [ -z "${UE_VERSION}" ]; then UE_VERSION="5.1"; fi

# old intermediate files will be out of date
./autobuild/cleanupunreal.sh

# TODO: copy in config changes and re-generate xcode/vs project files

#get correct VaRest
cd Plugins/VaRest
if [ $UE_VERSION == "4.27" ];
then
	git checkout 4.27
else 
	if [ $UE_VERSION == "5.0" ];
	then
		git checkout 5.0
	else 
		git checkout develop
	fi
fi
cd ../..

echo "Updated plugin VaRest" 

if [ $UE_VERSION == "4.27" ];
then
	export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_4.27'
	export UE_EDITOR_CMD='UE4Editor-Cmd'
else 
	if [ $UE_VERSION == "5.0" ];
	then
		export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_5.0'
		export UE_EDITOR_CMD='UE4Editor-Cmd'
	else 
		export UE_INSTALL_PATH='/Users/Shared/Epic Games/UE_5.1'
		export UE_EDITOR_CMD='UnrealEditor-Cmd'
	fi
fi

echo "Updated path to ${UE_INSTALL_PATH}" 
		
# replace version in .uproject
 sed -i '' "s/\"EngineAssociation\": \".*$/\"EngineAssociation\": \"${UE_VERSION}\",/g" BCSubsystem.uproject

./autobuild/workspace-genarate.sh

echo "Project files have been modified for UE ${UE_VERSION}"
