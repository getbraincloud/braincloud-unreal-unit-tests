#!/bin/bash

cd $1

STR=$(git rev-parse --abbrev-ref HEAD)

if [ $STR == $2 ]
then
    echo "Submodule $1 is on expected branch $2."
else
    if [ $STR == "HEAD" ];
    then
        echo "Submodule $1 is detached."
    else
        echo "Warning! Submodule is on branch $STR."
    fi
fi

if [[ $(git diff --compact-summary) ]];
then
    echo "Warning! Submodule has outstanding changes."
fi

LOCAL=$(git rev-parse --verify HEAD)
echo -$LOCAL- submodule $1

REMOTE=$(git rev-parse --verify origin/$2)
echo -$REMOTE- on remote $2

if [ $LOCAL == $REMOTE ];
then
    echo Submodule $1 up to date with latest commit.
    CODE=0
else
    echo Warning! Please run: git submodule update --remote $1
    CODE=1
fi

exit $CODE
