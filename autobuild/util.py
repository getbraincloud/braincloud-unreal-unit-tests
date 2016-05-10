import fnmatch
import os
import zipfile

# 
# Zips a directory into a zipfile
#
# @param srcPath The path to the directory to zip
# @param zip The ZipFile object
# @param dstPath The destination path (ie the relative parent in the zip)
# @param ignorePaths A list of relative paths to ignore (ie from srcPath)
# @param ignoreFileMatches An fnmatch (unix) style wildcard match for files to ignore
#
def zipdir(srcPath, zip, dstPath=None, ignorePaths=None, ignoreFileMatches=None):
	#relroot = os.path.abspath(os.path.join(srcPath, os.pardir))
	relroot = os.path.abspath(srcPath)
	for root, dirs, files in os.walk(srcPath):
		for file in files:
			skipFile = False
			if dstPath is None:
				arcname = os.path.join(os.path.relpath(root, relroot), file)
			else:
				arcname = os.path.join(dstPath + os.sep + os.path.relpath(root, relroot), file)

			# see if we should ignore files in this path
			if ignorePaths is not None:
				for ignorePath in ignorePaths:
					# add trailing path sep to both paths
					filePathToCheck = root + os.sep
					ignorePathToCheck = ignorePath
					if not ignorePathToCheck.endswith(os.sep):
						ignorePathToCheck += os.sep
					#print(ignorePathToCheck)
					#print(filePathToCheck)
					if filePathToCheck.startswith(ignorePathToCheck):
						#print("ignoring...")
						skipFile = True
						continue

			if not skipFile and ignoreFileMatches is not None:
				for ignoreFileEntry in ignoreFileMatches:
					if fnmatch.fnmatch(file, ignoreFileEntry):
						skipFile = True
						continue
			if not skipFile:
				zip.write(os.path.join(root, file), arcname)

	return

