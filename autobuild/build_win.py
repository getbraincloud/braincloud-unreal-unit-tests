import sys
import os
import shutil
import zipfile
import glob
import subprocess
import argparse
import re

import vstudio
import util


def cleanArtifacts(in_artifactsPath):
	print()
	print("Cleaning artifacts")
	if os.path.exists(in_artifactsPath):
		shutil.rmtree(in_artifactsPath)
	os.mkdir(in_artifactsPath)
	return

def createVersionNumber():
    output = os.getenv("BUILD_NUMBER", "dev")
    return output

def stampReadme(in_platform, in_version):
	readmefile = "docs/README.TXT"; 
	with open("readme.tmp", "wt") as fout:
		with open(readmefile, "rt") as fin:
			for line in fin:
				line = re.sub(r"Platform\:.*", "Platform: " + in_platform, line);
				line = re.sub(r"Version\:.*", "Version: " + in_version, line);
				fout.write(line)

	# this will fail if file is read-only
	shutil.move("readme.tmp", "artifacts" + os.sep + "README.TXT")
	return


def buildWinDesktop(artifacts, version, rebuild):

	# msbuild vars
	projectPath = os.path.abspath("..")
	projectFile = projectPath + os.sep + "solutions" + os.sep + "windowsDesktop_vc120" + os.sep + "brainCloud_winDesktop.sln"

	if rebuild:
		targets = "Rebuild"
	else:
		targets = "Build"

	print()
	print("Building windows api project")
	print()
	sys.stdout.flush()
	switches = []
	switches.append("/p:Platform=Win32")

	# build release version of lib
	config = "Release"
	vstudio.buildProject(projectFile, targets, config, in_switches=switches)

	# build debug version of lib
	config = "Debug"
	vstudio.buildProject(projectFile, targets, config, in_switches=switches)

	switches = []
	switches.append("/p:Platform=x64")

	# build release version of lib
	config = "Release"
	vstudio.buildProject(projectFile, targets, config, in_switches=switches)

	# build debug version of lib
	config = "Debug"
	vstudio.buildProject(projectFile, targets, config, in_switches=switches)
	
	print()
	print("Zipping library")

	rootPath = os.path.abspath("..")
	binPath = projectPath + os.sep + "solutions" + os.sep + "windowsDesktop_vc120" + os.sep + "bin"

	# zip up build directly from source files	
	with zipfile.ZipFile("artifacts" + os.sep + "brainCloudClient_WindowsDesktop_" + version + ".zip", "w", compression=zipfile.ZIP_DEFLATED) as myzip:
		
		for fname in glob.iglob(binPath + os.sep + "Win32" + os.sep + "Release" + os.sep + "*.*"):
			myzip.write(fname, "lib" + os.sep + "win32" + os.sep + "release" + os.sep + os.path.basename(fname))

		for fname in glob.iglob(binPath + os.sep + "Win32" + os.sep + "Debug" + os.sep + "*.*"):
			myzip.write(fname, "lib" + os.sep + "win32" + os.sep + "debug" + os.sep + os.path.basename(fname))

		for fname in glob.iglob(binPath + os.sep + "x64" + os.sep + "Release" + os.sep + "*.*"):
			myzip.write(fname, "lib" + os.sep + "x64" + os.sep + "release" + os.sep + os.path.basename(fname))

		for fname in glob.iglob(binPath + os.sep + "x64" + os.sep + "Debug" + os.sep + "*.*"):
			myzip.write(fname, "lib" + os.sep + "x64" + os.sep + "debug" + os.sep + os.path.basename(fname))
		
		util.zipdir(rootPath + os.sep + "include" + os.sep, myzip, "include")
		util.zipdir(rootPath + os.sep + "lib" + os.sep + "jsoncpp-1.0.0", myzip, "thirdparty" + os.sep + "jsoncpp-1.0.0")
		util.zipdir(rootPath + os.sep + "lib" + os.sep + "win32" + os.sep + "cpprestsdk-static" + os.sep + "Release" + os.sep + "include", myzip, "thirdparty" + os.sep + "casablanca" + os.sep + "include")

		myzip.write("artifacts" + os.sep + "README.TXT", "README.TXT")
	return


def buildWinStore(artifacts, version, rebuild):

	print()
	print("Building windows store project")
	print()
	sys.stdout.flush()

	projectPath = os.path.abspath("..")
	projectFile = projectPath + os.sep + "solutions" + os.sep + "windowsStore_vc120" + os.sep + "brainCloud_winstore.sln"

# winstore
	if rebuild:
		targets = "brainCloud_winstore:Rebuild"
	else:
		targets = "brainCloud_winstore"

	configs = []
	configs.append("Debug")
	configs.append("Release")

	platforms = []
	platforms.append("Win32")
	platforms.append("ARM")
	platforms.append("x64")

	for platform in platforms:
		for config in configs:
			print()
			print("BUILDING FOR PLATFORM: " + platform + " CONFIG: " + config)
			switches = []
			switches.append("/p:Platform=" + platform)
			vstudio.buildProject(projectFile, targets, config, in_switches=switches)

# winphone 8.1
	if rebuild:
		targets = "brainCloud_wp:Rebuild"
	else:
		targets = "brainCloud_wp"

	configs = []
	configs.append("Debug")
	configs.append("Release")

	platforms = []
	platforms.append("Win32")
	platforms.append("ARM")

	for platform in platforms:
		for config in configs:
			print()
			print("BUILDING FOR PLATFORM: " + platform + " CONFIG: " + config)
			switches = []
			switches.append("/p:Platform=" + platform)
			vstudio.buildProject(projectFile, targets, config, in_switches=switches)

# winphone 8.0
	if rebuild:
		targets = "brainCloud_wp8:Rebuild"
	else:
		targets = "brainCloud_wp8"

	configs = []
	configs.append("Debug")
	configs.append("Release")

	platforms = []
	platforms.append("Win32")
	platforms.append("ARM")

	for platform in platforms:
		for config in configs:
			print()
			print("BUILDING FOR PLATFORM: " + platform + " CONFIG: " + config)
			switches = []
			switches.append("/p:Platform=" + platform)
			vstudio.buildProject(projectFile, targets, config, in_switches=switches)

			
	print()
	print("Zipping library files")

	rootPath = os.path.abspath("..")
	binPath = projectPath + os.sep + "solutions" + os.sep + "windowsStore_vc120" + os.sep + "bin" 

	# zip up build directly from source files	
	with zipfile.ZipFile("artifacts" + os.sep + "brainCloudClient_WindowsStore_" + version + ".zip", "w", compression=zipfile.ZIP_DEFLATED) as myzip:
		util.zipdir(rootPath + os.sep + "include" + os.sep, myzip, "include")

		util.zipdir(binPath, myzip, "lib")
		util.zipdir(rootPath + os.sep + "lib" + os.sep + "jsoncpp-1.0.0", myzip, "thirdparty" + os.sep + "jsoncpp-1.0.0")
		util.zipdir(rootPath + os.sep + "lib" + os.sep + "win32" + os.sep + "cpprestsdk-static" + os.sep + "Release" + os.sep + "include", myzip, "thirdparty" + os.sep + "casablanca" + os.sep + "include")

		myzip.write("artifacts" + os.sep + "README.TXT", "README.TXT")
	return


def buildWinUwp(artifacts, version, rebuild):

	# msbuild vars
	projectPath = os.path.abspath("..")
	projectFile = projectPath + os.sep + "solutions" + os.sep + "windowsUniversal_vc140" + os.sep + "brainCloud_uwp.sln"

	if rebuild:
		targets = "brainCloud:Rebuild"
	else:
		targets = "brainCloud"

	print()
	print("Building windows universal project")
	print()
	sys.stdout.flush()

	# first restore nuget packages
	cwd = projectPath + os.sep + "solutions" + os.sep + "windowsUniversal_vc140"
	cmd = []
	cmd.append("nuget")
	cmd.append("restore")
	print("Restoring nuget packages...")
	subprocess.check_call(cmd, cwd=cwd)
	
	# now build it
	switches = []
	switches.append("/p:Platform=x86")

	# build release version of lib
	config = "Release"
	vstudio.buildProject(projectFile, targets, config, in_switches=switches)

	# build debug version of lib
	config = "Debug"
	vstudio.buildProject(projectFile, targets, config, in_switches=switches)

	switches = []
	switches.append("/p:Platform=x64")

	# build release version of lib
	config = "Release"
	vstudio.buildProject(projectFile, targets, config, in_switches=switches)

	# build debug version of lib
	config = "Debug"
	vstudio.buildProject(projectFile, targets, config, in_switches=switches)
	
	switches = []
	switches.append("/p:Platform=ARM")

	# build release version of lib
	config = "Release"
	vstudio.buildProject(projectFile, targets, config, in_switches=switches)

	# build debug version of lib
	config = "Debug"
	vstudio.buildProject(projectFile, targets, config, in_switches=switches)
	
	print()
	print("Zipping library")

	rootPath = os.path.abspath("..")
	binPath = projectPath + os.sep + "solutions" + os.sep + "windowsUniversal_vc140" + os.sep + "brainCloud" + os.sep + "Output"

	# zip up build directly from source files	
	with zipfile.ZipFile("artifacts" + os.sep + "brainCloudClient_WindowsUniversal_" + version + ".zip", "w", compression=zipfile.ZIP_DEFLATED) as myzip:
		
		for fname in glob.iglob(binPath + os.sep + "ARM" + os.sep + "Release" + os.sep + "*.*"):
			myzip.write(fname, "lib" + os.sep + "ARM" + os.sep + "release" + os.sep + os.path.basename(fname))

		for fname in glob.iglob(binPath + os.sep + "ARM" + os.sep + "Debug" + os.sep + "*.*"):
			myzip.write(fname, "lib" + os.sep + "ARM" + os.sep + "debug" + os.sep + os.path.basename(fname))
		
		for fname in glob.iglob(binPath + os.sep + "Win32" + os.sep + "Release" + os.sep + "*.*"):
			myzip.write(fname, "lib" + os.sep + "win32" + os.sep + "release" + os.sep + os.path.basename(fname))

		for fname in glob.iglob(binPath + os.sep + "Win32" + os.sep + "Debug" + os.sep + "*.*"):
			myzip.write(fname, "lib" + os.sep + "win32" + os.sep + "debug" + os.sep + os.path.basename(fname))

		for fname in glob.iglob(binPath + os.sep + "x64" + os.sep + "Release" + os.sep + "*.*"):
			myzip.write(fname, "lib" + os.sep + "x64" + os.sep + "release" + os.sep + os.path.basename(fname))

		for fname in glob.iglob(binPath + os.sep + "x64" + os.sep + "Debug" + os.sep + "*.*"):
			myzip.write(fname, "lib" + os.sep + "x64" + os.sep + "debug" + os.sep + os.path.basename(fname))
		
		util.zipdir(rootPath + os.sep + "include" + os.sep, myzip, "include")
		util.zipdir(rootPath + os.sep + "lib" + os.sep + "jsoncpp-1.0.0", myzip, "thirdparty" + os.sep + "jsoncpp-1.0.0")
		
		myzip.write("artifacts" + os.sep + "README.TXT", "README.TXT")
	return
	
	
def main():

	parser = argparse.ArgumentParser(description="Run the build")
	parser.add_argument("--winDesktop", dest="buildWinDesktop", action="store_true", help="Build for win7 + win8 + win10 desktop")
	parser.add_argument("--winStore", dest="buildWinStore", action="store_true", help="Build for windows store apps (and phone 8.0/8.1)")
	parser.add_argument("--winUwp", dest="buildWinUwp", action="store_true", help="Build for windows universal apps (win10)")
	parser.add_argument("--baseVersion", dest="baseVersion", action="store", required=True, help="Set the library version ie 2.23.0")
	parser.add_argument("--rebuild", dest="rebuild", action="store_true", help="Rebuild solution instead of just build")
	args = parser.parse_args()

	# general vars
	scmRev = createVersionNumber()
	version = args.baseVersion + "." + scmRev

	# general vars
	artifacts = os.path.abspath("artifacts")

	# clean up old builds
	cleanArtifacts(artifacts)

	if args.buildWinDesktop:
		stampReadme("Windows Desktop", version)
		buildWinDesktop(artifacts, version, args.rebuild)

	if args.buildWinStore:
		stampReadme("Windows Store", version)
		buildWinStore(artifacts, version, args.rebuild)

	if args.buildWinUwp:
		stampReadme("Windows Universal", version)
		buildWinUwp(artifacts, version, args.rebuild)
	
	return

def test():
	with zipfile.ZipFile("x.zip", "w", compression=zipfile.ZIP_DEFLATED) as myzip:
		util.zipdir("tmp", myzip, "thirdparty" + os.sep + "casablanca", ["tmp/ignore"], ["*.meta"])
	return

#test()
main()

