cmake_minimum_required (VERSION 3.0)
project (brainCloudUnitTest)


################################
# Braincloud
################################

set (BC_DIR "${PROJECT_SOURCE_DIR}/..")
include_directories("${BC_DIR}/lib/jsoncpp-1.0.0")
include_directories("src")

file(GLOB_RECURSE INCS "src/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE JSONCPP_FILES "${BC_DIR}/lib/jsoncpp-1.0.0/*.*")
file(GLOB_RECURSE BC_INCS "${BC_DIR}/include/*.h")

source_group(braincloud FILES ${BC_INCS})
source_group(json FILES ${JSONCPP_FILES})
source_group(headers FILES ${INCS})
source_group(src FILES ${SOURCES})

add_executable(bctests ${BC_INCS} ${JSONCPP_FILES} ${WRAPPER_INCS} ${INCS} ${SOURCES})


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	find_library(CURL_LIB curl)
	find_library(GAMEKIT_LIB GameKit)
	find_library(COREFOUNDATION_LIB CoreFoundation)
	find_library(FOUNDATION_LIB Foundation)
    find_library(SECURITY_LIB Security)
    target_link_libraries(bctests PUBLIC ${CURL_LIB} ${GAMEKIT_LIB} ${COREFOUNDATION_LIB} ${FOUNDATION_LIB} ${SECURITY_LIB})

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	if (${NO_CPPREST_SDK})
		include_directories("${BC_DIR}/lib/win32/curl-7.44.0/include")
		
		find_library(CURL_LIB libcurl_a.lib "${BC_DIR}/lib/win32/curl-7.44.0/lib")
		target_link_libraries(bctests PUBLIC ${CURL_LIB})
		
		SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
		SET (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
		SET (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")
		
		add_custom_command(TARGET bctests POST_BUILD        # Adds a post-build event to MyTest
		    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
		        "${BC_DIR}/lib/win32/pthread-w32-2-8-0/Pre-built.2/lib/pthreadVCE2.dll"      # <--this is in-file
        		$<TARGET_FILE_DIR:bctests>)  
	endif()

endif()


################################
# GTest
################################

add_subdirectory(gtest-1.7.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(bctests PUBLIC gtest gtest_main)

################################
# BrainCloudLib
################################

target_link_libraries(bctests PUBLIC brainCloud)
