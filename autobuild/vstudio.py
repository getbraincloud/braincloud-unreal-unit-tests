import os
import shutil
import sys
import subprocess

#
# The default location for a Unity install
# Override by changing 

def checkPlatform():
	if not sys.platform == "win32":
		raise Exception("Visual Studio scripts are only available on windows!")
	return

#
# Method runs msbuild for the given project and targets
#
# @param in_projectPath Path to the project
# @param in_targets Semi-colon delimited list of targets to build
# @param in_configuration The build configuration to use
# @param in_switches Optional list of switches to send to msbuild
# @param in_msbuildPath Optional path to msbuild, will use default otherwise
#
def buildProject(in_projectPath, in_targets, in_configuration, in_switches=None, in_msbuildPath=None):
	checkPlatform()	

	# we assume vcvarsall.bat was called to set the path appropriately
	msbuildPath = "MSBuild.exe"

	print()
	print("Building Visual Studio Project")
	print("  Project path: " + in_projectPath)
	print("  Targets: " + in_targets)
	if not in_switches is None:
		print("  Switches: " + "".join(in_switches))
	print("  MSBuild path: " + msbuildPath)

	cmd = []
	cmd.append(msbuildPath)
	cmd.append("/m")
	
	if not in_switches is None:
		cmd.extend(in_switches)

	cmd.append("/p:Configuration=" + in_configuration)
	if not in_targets is None:
		cmd.append("/t:" + in_targets)

	cmd.append(in_projectPath)

	print(cmd)

	subprocess.check_call(cmd)
	return
