#!/bin/bash

if [[ -d Plugins/BCClient  ]];
then

	STR=$(git config -f .gitmodules --get submodule.Plugins/BCClient.branch)
	if [ -z $STR ];
	then
     STR=$(git remote show origin| sed -n '/HEAD branch/s/.*: //p')
	 fi
  pushd Plugins/BCClient
   if [[ $(git diff --compact-summary .) ]];
   then
   echo "Folder has mods"
  else
   echo "Checking out ${1:-$STR}"
   git checkout ${1:-$STR}
   git pull
  fi
  popd
else
	echo "Folder not exists"
fi 
