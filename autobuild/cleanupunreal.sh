#!/bin/bash
rm -rf DerivedDataCache

for i in . Plugins/BCClient Plugins/VaRest
do
	rm -rf $i/Binaries
	rm -rf $i/Intermediate
done
echo Unreal build file have been removed.

