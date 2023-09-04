#!/bin/bash

# run this in your project root folder
cd "`dirname "$0"`"/..

if [ -z $BRAINCLOUD_TOOLS ];
then
  export BRAINCLOUD_TOOLS=~/braincloud-client-master
fi

if [ -z $1 ];
then
  if [ -z $SERVER_ENVIRONMENT ];
  then
    SERVER_ENVIRONMENT=internal
  fi
else
  SERVER_ENVIRONMENT=$1
fi

${BRAINCLOUD_TOOLS}/bin/copy-ids.sh -o Source/BCSubsystem -p test -x h -s $SERVER_ENVIRONMENT
