#!/bin/bash
if [[ $(git diff --compact-summary) ]];
then
    echo
    echo "Warning: this project has modifications. Restore or commit before merging."
    git diff --compact-summary
    exit 1
fi

needspush=0

git checkout ue5-tests
git fetch origin

if [[ $(git log --oneline ue5-tests..origin/develop) ]]; then
    echo "ERROR: ue5-tests requires merge with develop."
    exit 2
fi


cd Plugins/BCClient
git checkout ue5-plugin
if [[ $(git log --oneline ue5-plugin..origin/develop) ]]; then
    echo "ERROR: ue5-plugin requires merge with develop."
    exit 3
fi

echo
exit 0
