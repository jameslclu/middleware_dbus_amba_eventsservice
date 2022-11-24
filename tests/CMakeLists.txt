# set minimum cmake version
cmake_minimum_required(VERSION 3.10)

set(modulename tests)

project(${modulename}
        LANGUAGES C CXX
        DESCRIPTION "Test Service"
        VERSION 0.0.1)

#### Google Test #####
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lrt")
set(CMAKE_C++_FLAGS "${CMAKE_C++_FLAGS} -lrt")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

### search required libaries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED gio-2.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GIO_UNIX REQUIRED IMPORTED_TARGET gio-unix-2.0)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

# common
list(APPEND common_src
        ../common/source/JsonUtility.cpp
        ../common/source/popen_noshell.cpp
        ../common/source/ShellUtility.cpp)

list(APPEND common_include_dir
        ../common/include)

# system
list(APPEND system_src
        ../system/source/misc/MISCServiceProxy.cpp)

list(APPEND system_include_dir
        ../system/include/misc)

# ai
list(APPEND ai_src
        ../ai/source/AIServiceProxy.cpp)

list(APPEND ai_include_dir
        ../ai/include
        ../ai/include/common)

# recording
list(APPEND recording_src
        ../recording/source/RecordingServiceProxy.cpp)

list(APPEND recording_include_dir
        ../recording/include)

# events
list(APPEND events_src
        ../events/source/EventsServiceStub.cpp
        ../events/source/EventsServiceProxy.cpp)

list(APPEND events_include_dir
        ../events/include
        ../events/source)

add_executable(${modulename}
    ${common_include_dir}
    ${system_src}
    ${ai_src}
    ${recording_src}
    ${events_src}
    integration/EventsServiceStubProxyTest.cpp)

find_package(Threads)

list(APPEND all_include
        ${common_include_dir}
        ${system_include_dir}
        ${ai_include_dir}
        ${recording_include_dir}
        ${events_include_dir})

target_include_directories(${modulename} PUBLIC
        ${GIO_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS}
        ${GIO_UNIX_INCLUDE_DIRS} ${JSONCPP_INCLUDE_DIRS}
        ${PROJECT_BINARY_DIR} ${all_include})

target_link_libraries(${modulename} PUBLIC
        ${GIO_LIBRARIES} ${GLIB_LIBRARIES}
        ${GIO_UNIX_LIBRARIES} ${JSONCPP_LIBRARIES}
        gtest gtest_main gmock Threads::Threads)

add_subdirectory(lib)

#add_subdirectory(ModelTest)
#add_subdirectory(UnitTest)
#add_subdirectory(ModelTest)
#add_subdirectory(SystemTest)
#add_subdirectory(IntegrationTest)
#add_subdirectory(AcceptanceTest)