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

### Update:

You can check which version of the plugin is installed under Edit > Plugins or by referring to the text file BCClient.uplugin.

To make sure you have the latest version of the plugin and to update the SHA1 of the Plugin submodule:

```
$ cd braincloud-unreal
$ git submodule update --remote
```

To work with a branch of the plugin

```
$ cd braincloud-unreal/Plugins/BCClient
$ git checkout develop
```

### Build:

Open the uproject file in UE 4.27. It will inform that VaRest and BCClient modules are missing or unbuilt. Click YES to build. Click Show Log to see progress.

### Run:

Select Windows > Developer Tools > Session Frontend. Find tests on Automation tab under Project > Functional Tests. Make sure to include **ids.txt** file to define input params.
