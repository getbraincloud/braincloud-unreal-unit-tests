#!/bin/bash

PROJECT_NAME=BCSubsystem
PROJECT_ROOT=.
ASSETS=$(find ${PROJECT_ROOT}/Content -type f -name "*.uasset")
MAPS=$(find ${PROJECT_ROOT}/Content -type f -name "*.umap")

needspush=0

flagged=0
for i in $ASSETS
do
    if [[ $(strings $i | grep ++UE5+) ]];
    then
        if [[ $flagged == 0 ]];
        then
            echo "--- ATTENTION REQUIRED! The following assets in ${PROJECT_NAME} are not UE4 compatible:"
        fi    
       flagged=$flagged+1
       needspush=1
       echo $i
    fi
done

flagged=0
for i in $MAPS
do
    if [[ $(strings $i | grep ++UE5+) ]];
    then
        if [[ $flagged == 0 ]];
        then
            echo "--- ATTENTION REQUIRED! The following levels in ${PROJECT_NAME} are not UE4 compatible:"
        fi    
       flagged=$flagged+1
       needspush=1
       echo $i
    fi
done

if [[ $(strings ${PROJECT_NAME}.uproject | grep "\"EngineAssociation\": \"5") ]];
then
    needspush=1
    echo "--- ATTENTION REQUIRED! Check EngineAssociation in project file:"
    echo ${PROJECT_NAME}.uproject
fi

if [[ $needspush == 0 ]];
then
    echo "--- Project ${PROJECT_NAME} verified UE4 compatible."
else
    echo "--- UE4 CHECK FAILED: Please review git history and make necessary changes in UE4 editor."    
fi

exit $needspush
