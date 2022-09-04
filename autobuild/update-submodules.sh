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

    STR=$(git config -f .gitmodules --get submodule.$i.branch)
    STR=${STR:="default"}
    
    if [[ $(git submodule update --remote $i) ]];
    then
        if [[ $(git diff --compact-summary $i) ]];
        then
            # make sure we use ssh url to push
            fullUrl=$(git config -f .gitmodules --get submodule.$i.url)
            newUrl=$(echo "$fullUrl" | sed "s,https://github.com/,git@github.com:,g")
            pushd $i
            git remote set-url origin ${newUrl}
            popd
            
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
    git push
    code=$?
    if [[ $code != 0 ]];
    then
        echo "--- Failure: needs updating and cannot push"
    fi
fi

echo
exit $code
