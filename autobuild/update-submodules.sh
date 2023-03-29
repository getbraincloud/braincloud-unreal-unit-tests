#!/bin/bash
if [[ $(git diff --compact-summary) ]];
then
    if [[ $1 != "--force" ]];
    then
        if [[ $1 != "--ignore" ]];
        then
            echo
            echo "Warning: this project has modifications. These files will be ignored in push. To continue update use --ignore."
            git diff --compact-summary
            exit 1
        fi
    fi
fi

needspush=0

for i in Plugins/BCClient
do
    echo
    git submodule status $i
    
    if [[ $(git diff --compact-summary $i) ]];
    then
        if [[ $1 != "--force" ]];
        then
            echo
            echo "--- Skipping $i SHA1 has been modified. This may mean another branch or tag has been checked out and/or the code has been modified. To overwrite SHA1 use --force."
            continue
        fi
    fi
    
    if [[ ${1} == "master" ]] ; then
        git submodule set-branch --default $i
        git add .gitmodules
    else
        if [[ ${1} != "" ]] ; then
            git submodule set-branch ${1} $i
            git add .gitmodules
        fi
    fi
    
    STR=$(git config -f .gitmodules --get submodule.$i.branch)
    STR=${STR:="default"}
    
    if [[ $(git submodule update --remote $i) ]];
    then
        if [[ $(git diff --compact-summary $i) ]];
        then
            git add $i
            git commit -m "automatic submodules update" .

            needspush=1

            git submodule status $i
            echo "--- $i updated on branch $STR"
         else
            git submodule status $i
            echo "--- $i is up to date on branch $STR local copy has been updated"
         fi
    else
        if [[ $(git diff --compact-summary $i) ]];
        then
            git add $i
            git commit -m "automatic submodules update" .

            needspush=1
            echo "--- $i local is already up to date updating branch $STR"
        else
            echo "--- $i is already up to date on branch $STR"
        fi
    fi
done

if [[ $needspush != 0 ]];
then
    echo "--- ATTENTION REQUIRED! Update pending. Please run command: git push"
fi

echo
exit 0
