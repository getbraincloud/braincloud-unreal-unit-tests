#!/bin/bash
# switch project to unreal version
# usage:
#     autobuild/switch_project.bat 5.0
#      autobuild/switch_project.bat
#      autobuild/switch_project.bat 4.27

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

# replace version in .uproject
 sed -i '' "s/\"EngineAssociation\": \".*$/\"EngineAssociation\": \"${UE_VERSION}\",/g" BCSubsystem.uproject

echo "Project file has been modified for UE ${UE_VERSION}"
