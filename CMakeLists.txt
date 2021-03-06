cmake_minimum_required( VERSION 3.5 )
set( PROJECT_NAME_STR matviz )
project( ${PROJECT_NAME_STR} C CXX)

# for gtest
find_package(Threads REQUIRED)

#
# Compiler definitions
#

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-Wall -std=c++14 -pthread )
endif()


if(MSVC)
  #vc 2012 fix for vararg templates
  set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif() 

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 ")

#
# Include files and ext folder
#

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

#
# Main executable
#

include_directories( ${COMMON_INCLUDES} )
file( GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp )
add_executable( ${PROJECT_NAME_STR} ${SRC_FILES} )


#
# Test
#

# need VERSION 3.6 cmake :(
# clang-tidy static analyzer

#if( CMAKE_CXX_CLANG_TIDY )
#  set_property( TARGET ${PROJECT_NAME_STR} PROPERTY CMAKE_CXX_CLANG_TIDY )
#endif()

# gtest

# add module source

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)

add_definitions( ${MSVC_COMPILER_DEFS} )
enable_testing()
set( PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test )
include_directories( ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES} )

file( GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp )
list( APPEND TEST_SRC_FILES ${SRC_FILES} )
list( REMOVE_ITEM TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp )

add_executable( ${PROJECT_TEST_NAME} ${TEST_SRC_FILES} )
add_dependencies( ${PROJECT_TEST_NAME} googletest )


if(NOT WIN32 OR MINGW)
  target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_LIBS_DIR}/libgtest.a ${GTEST_LIBS_DIR}/libgtest_main.a)
else()
  target_link_libraries(${PROJECT_TEST_NAME}
                        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
                        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
                       )
  target_link_libraries(${PROJECT_TEST_NAME}
                        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
                        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
                       )
endif()

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_test( gtests ${PROJECT_TEST_NAME} )
