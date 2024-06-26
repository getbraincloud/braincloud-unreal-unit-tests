# brainCloud Unreal Subsystem

This repository contains automated tests for all functionality of brainCloud. Find the latest releases of the Unreal brainCloud client plugin [here](https://github.com/getbraincloud/braincloud-unreal-plugin).

## Instructions

### Clone:

The project includes the required plugins VaRest and BCClient as git submodules.

```
$ git clone --recurse-submodules https://github.com/getbraincloud/braincloud-unreal-unit-tests.git
```

If you are updating an existing repository, or forget to --recurse-submodules, then just update the modules. 
Make sure you've done this if you get "missing plugin" error on load.

```
$ cd braincloud-unreal-unit-tests
$ git submodule update --init --recursive
```

### Update:

You can check which version of the plugin is installed under Edit > Plugins or by referring to the text file BCClient.uplugin.

To make sure you have the latest version of the plugin and to update the SHA1 of the Plugin submodule:

```
$ cd braincloud-unreal-unit-tests
$ git submodule update --remote
```

To work with a branch of the plugin

```
$ cd braincloud-unreal-unit-tests/Plugins/BCClient
$ git checkout develop
```

### Build:

Open the uproject file in Unreal Engine. It will inform that BCClient modules are missing or unbuilt. Click YES to build. Click Show Log to see progress.

### Run:

Select Windows > Developer Tools > Session Frontend. Find tests on Automation tab under Project > Functional Tests. Make sure to modify **BrainCloudSettings.ini** file to define input params.

### Commandline:
See autobuild/runtest script for commandline arguments to build and run tests (eg. for continuous integration or nightly tests on Jenkins).

### UE Version (5.3):

This project will not open in older versions of Unreal Engine (assets will appear to be missing). Make sure that VaRest is the correct version. You can get this third-party plugin through MarketPlace or GitHub.

Open BCSubsystem.uproject by double-clicking or within engine. Build at command-line by exporting the correct paths in autobuild/runtest.sh or autobuild/runtest.bat.

#### Older Versions:
There is a examples-unreal branch on github that runs in UE 4.27 using the same brainCloud plugin. https://github.com/getbraincloud/examples-unreal

The brainCloud plugin can be pre-built for any engine version.  https://github.com/getbraincloud/braincloud-unreal-plugin
