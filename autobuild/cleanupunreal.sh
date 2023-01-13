#!/bin/bash
find Saved/* -type d ! -name 'logs' | xargs rm -rf
rm -rf DerivedDataCache

for i in . Plugins/BCClient Plugins/VaRest
do
	rm -rf $i/Binaries
	rm -rf $i/Intermediate
done
echo Unreal build file have been removed.

