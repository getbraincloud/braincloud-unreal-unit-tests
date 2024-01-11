#!/bin/bash

rm -rf Binaries
rm -rf Intermediate
rm -rf Saved
rm -rf DerivedDataCache
rm -rf Plugins/BCClient/Binaries
rm -rf Plugins/BCClient/Intermediate
if [ -z $1 ] ; then
	echo Done $PWD
fi
