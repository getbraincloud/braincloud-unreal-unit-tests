#!/bin/bash
if [[ $(git diff --compact-summary) ]];
then
    echo
    echo "Warning: this project has modifications. Restore or commit before merging."
    git diff --compact-summary
    exit 1
fi

needspush=0

git checkout $1
git fetch origin
git merge --no-commit origin/develop

CONFLICTS=$(git ls-files -u | wc -l)
if [ "$CONFLICTS" -gt 0 ] ; then
   echo "There is a merge conflict. Aborting"
   git merge --abort
   exit 2
fi

if [[ $(cat .git/MERGE_HEAD) ]];
then
    needspush=1
    git add --all
    git commit -m "merging changes from develop into $1"
fi

if [[ $needspush != 0 ]];
then
    echo "--- ATTENTION REQUIRED! Update pending. Please run command: git push"
else
    echo "---- $1 is already up to date with develop."
fi

echo
exit 0
