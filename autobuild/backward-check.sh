#!/bin/bash

ASSETS=$(find Content -type f -name "*.uasset")
MAPS=$(find Content -type f -name "*.umap")

needspush=0

flagged=0
for i in $ASSETS
do
    if [[ $(strings $i | grep ++UE5+) ]];
    then
        if [[ $flagged == 0 ]];
        then
            echo "--- ATTENTION REQUIRED! The following assets are not backwards compatible:"
        fi    
       flagged=$flagged+1
       needpush=1
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
            echo "--- ATTENTION REQUIRED! The following levels are not backwards compatible:"
        fi    
       flagged=$flagged+1
       needpush=1
       echo $i
    fi
done

if [[ $(strings BCSubsystem.uproject | grep "\"EngineAssociation\": \"4.27\",") ]];
then
    echo Project file is ok.
else
    needspush=1
    echo "--- ATTENTION REQUIRED! Check EngineAssociation in project:"
    echo BCSubsystem.uproject
fi

echo
exit $needspush
