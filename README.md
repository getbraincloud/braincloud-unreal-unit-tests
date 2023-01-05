# brainCloud Unreal Subsystem

This repository contains automated tests for all functionality of brainCloud. Find the latest releases of the Unreal brainCloud client plugin [here](https://github.com/getbraincloud/braincloud-unreal-plugin-src).

## Instructions

### Clone:

The project includes the required plugins VaRest and BCClient as git submodules.

```
$ git clone --recurse-submodules git@github.com:getbraincloud/braincloud-unreal.git
```

If you are updating an existing repository, or forget to --recurse-submodules, then just update the modules. 
Make sure you've done this if you get "missing plugin" error on load.

```
$ cd braincloud-unreal
$ git submodule update --init --recursive
```

### Build:

Open the uproject file in Unreal Engine. It will inform that VaRest and BCClient modules are missing or unbuilt. Click YES to build. Click Show Log to see progress.

### Run:

Select Windows > Developer Tools > Session Frontend. Find tests on Automation tab under Project > Functional Tests. Make sure to modify **ids.h** file to define input params.

### Commandline
Use autobuild/generate-ids script to set server and app info in the ids.h header file. See autobuild/runtest script for commandline arguments to build and run tests (eg. for continuous integration or nightly tests on Jenkins).

### UE Version (4.27, 5.0, 5.1):

Switch between versions using the right-click option on BCSubsystem.uproject. BCClient will load/build for any version. Make sure that VaRest is the correct version. You can get this third-party plugin through MarketPlace or GitHub. For ease of setup, the GitHub submodule is included in this project. Just checkout the branch for the version you require: 4.27, 5.0 or default (develop) for 5.1.

```
cd Plugins/VaRest
git checkout 5.0
```

Open BCSubsystem.uproject by double-clicking or within engine. Build at command-line by exporting the correct paths in autobuild/runtest.sh or autobuild/runtest.bat.
