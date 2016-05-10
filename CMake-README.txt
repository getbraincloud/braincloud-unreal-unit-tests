Here are some quick instructions on how to build for windows:

1) Fetch the cpprestsdk source
- Create a "git" directory in C++GameClient
- navigate to that directory using your git bash shell
- do the following command:
git clone https://git01.codeplex.com/casablanca

2) Compile the library:
- open the git/casablance/cpprestsdk120.sln
- for both "Debug" and "Release" configurations of "Win32" platform: 
-- right click cpprestsdk120 and select properties
-- go to General and set "Configuration Type" to "Static Library"
-- go to C/C++ | Preprocessor and remove "_MBSC" from the list of definitions
- build "Debug | Win32" and "Release | Win32" of "cpprestsdk120" project only

3) Open CMake window and make sure to toggle on "gtest_force_shared_crt" flag

You should now be able to build.

Note that if you get warnings about not being able to find winhttp.lib, crypt32.lib or bcrypt.lib:

verify that this var is set appropriate inside of GameClientLib/CMakeList.txt
set (WIN_PLATFORM_DIR "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x86")

(you can find the correct path by doing a system wide find for "winhttp.lib")
