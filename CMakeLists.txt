# set minimum cmake version
cmake_minimum_required(VERSION 3.10)

# project name and language
project(fxn_middleware_events)
set(CMAKE_CXX_STANDARD 11)

#add_subdirectory(common)
add_subdirectory(events)
add_subdirectory(tests)