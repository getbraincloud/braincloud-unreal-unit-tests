if (MSVC)
    cmake_minimum_required (VERSION 3.16.0)
else()
    cmake_minimum_required (VERSION 3.10.0)
endif()

project (brainCloudUnitTest)

if (UNIX AND NOT APPLE)
    set(LINUX 1)
endif()

# Multi core compilation in VS
if (MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" "/MP /FS") # Issue with VS2019. Things don't build if generated from cmake without the /FS flag
endif()

################################
# Braincloud
################################

set (BC_DIR "${PROJECT_SOURCE_DIR}/..")
include_directories("${BC_DIR}/lib/jsoncpp-1.0.0")
include_directories("src")

file(GLOB_RECURSE INCS "src/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE BC_INCS "${BC_DIR}/include/*.h")

source_group(braincloud FILES ${BC_INCS})
source_group(headers FILES ${INCS})
source_group(src FILES ${SOURCES})

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_executable(bctests ${BC_INCS} ${WRAPPER_INCS} ${INCS} ${SOURCES})

if (APPLE)
	find_library(GAMEKIT_LIB GameKit)
	find_library(COREFOUNDATION_LIB CoreFoundation)
	find_library(FOUNDATION_LIB Foundation)
	find_library(SECURITY_LIB Security)
	target_link_libraries(bctests PUBLIC ${GAMEKIT_LIB} ${COREFOUNDATION_LIB} ${FOUNDATION_LIB} ${SECURITY_LIB})
endif()

################################
# GTest
################################

if (MSVC)
if (MSVC_VERSION GREATER_EQUAL 1800)
	# C++11 has tupple since at least Visual Studio 2013. and tr1 is deprecated in VS2017
	add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
endif()
endif()
add_subdirectory(gtest-1.7.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(bctests PUBLIC gtest gtest_main)

################################
# BrainCloudLib
################################

target_link_libraries(bctests PUBLIC brainCloud)
