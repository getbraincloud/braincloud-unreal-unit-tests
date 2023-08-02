#!/bin/bash

if [[ -d Plugins/BCClient  ]];
then
		STR=$(git config -f .gitmodules --get submodule.Plugins/BCClient.branch)
	    pushd Plugins/BCClient 
	    if [[ $(git diff --compact-summary .) ]];
    	then
			echo "Folder has mods"
		else
			git checkout ${1:-$STR}
			git pull
		fi
		popd				
else
	echo "Folder not exists"
fi 
