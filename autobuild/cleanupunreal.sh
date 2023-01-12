#!/bin/bash
rm -rf Saved/Collections
rm -rf Saved/Config
rm -rf Saved/SaveGames
rm -rf $i/DerivedDataCache

for i in . Plugins/BCClient Plugins/VaRest
do
	rm -rf $i/Binaries
	rm -rf $i/Intermediate
done
echo Unreal build file have been removed.

