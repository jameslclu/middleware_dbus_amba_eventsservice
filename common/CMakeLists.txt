cmake_minimum_required(VERSION 3.10)

set(modulename common-utils)

project(${modulename} 
  LANGUAGES C CXX
  DESCRIPTION "commmon utility library"
  VERSION 0.0.1
)
set(CMAKE_CXX_STANDARD 11)

include(../cmake/utils.cmake)
#include(../cmake/common_lib.cmake)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

list(APPEND INC_DIRS
  include
  ${JSONCPP_INCLUDE_DIRS}
)

add_library(${modulename}-objs 
  OBJECT
    source/JsonUtility.cpp
    source/popen_noshell.cpp
    source/ShellUtility.cpp
)
set_target_properties(${modulename}-objs
  PROPERTIES
    POSITION_INDEPENDENT_CODE 1
)
target_include_directories(${modulename}-objs
        PUBLIC
        ${JSONCPP_INCLUDE_DIRS}
        ${INC_DIRS} )

if (MAKE_STATIC_LIBRARY)
  add_library(${modulename}-static
    STATIC
      $<TARGET_OBJECTS:${modulename}-objs>
  )
  set_target_properties(${modulename}-static
    PROPERTIES
      OUTPUT_NAME "${modulename}"
  )
  target_include_directories(${modulename}-static PUBLIC ${INC_DIRS} )
endif()
