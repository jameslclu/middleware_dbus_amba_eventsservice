# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug

# Include any dependencies generated for this target.
include tests/lib/googletest/CMakeFiles/gtest_main.dir/depend.make

# Include the progress variables for this target.
include tests/lib/googletest/CMakeFiles/gtest_main.dir/progress.make

# Include the compile flags for this target's objects.
include tests/lib/googletest/CMakeFiles/gtest_main.dir/flags.make

tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o: tests/lib/googletest/CMakeFiles/gtest_main.dir/flags.make
tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o: ../tests/lib/googletest/src/gtest_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o"
	cd /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug/tests/lib/googletest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.o -c /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/tests/lib/googletest/src/gtest_main.cc

tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest_main.dir/src/gtest_main.cc.i"
	cd /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug/tests/lib/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/tests/lib/googletest/src/gtest_main.cc > CMakeFiles/gtest_main.dir/src/gtest_main.cc.i

tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest_main.dir/src/gtest_main.cc.s"
	cd /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug/tests/lib/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/tests/lib/googletest/src/gtest_main.cc -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.s

tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires:

.PHONY : tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires

tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides: tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires
	$(MAKE) -f tests/lib/googletest/CMakeFiles/gtest_main.dir/build.make tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides.build
.PHONY : tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides

tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides.build: tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o


# Object files for target gtest_main
gtest_main_OBJECTS = \
"CMakeFiles/gtest_main.dir/src/gtest_main.cc.o"

# External object files for target gtest_main
gtest_main_EXTERNAL_OBJECTS =

lib/libgtest_main.a: tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
lib/libgtest_main.a: tests/lib/googletest/CMakeFiles/gtest_main.dir/build.make
lib/libgtest_main.a: tests/lib/googletest/CMakeFiles/gtest_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libgtest_main.a"
	cd /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug/tests/lib/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main.dir/cmake_clean_target.cmake
	cd /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug/tests/lib/googletest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/lib/googletest/CMakeFiles/gtest_main.dir/build: lib/libgtest_main.a

.PHONY : tests/lib/googletest/CMakeFiles/gtest_main.dir/build

tests/lib/googletest/CMakeFiles/gtest_main.dir/requires: tests/lib/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires

.PHONY : tests/lib/googletest/CMakeFiles/gtest_main.dir/requires

tests/lib/googletest/CMakeFiles/gtest_main.dir/clean:
	cd /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug/tests/lib/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main.dir/cmake_clean.cmake
.PHONY : tests/lib/googletest/CMakeFiles/gtest_main.dir/clean

tests/lib/googletest/CMakeFiles/gtest_main.dir/depend:
	cd /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/tests/lib/googletest /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug/tests/lib/googletest /mnt/d/workspaces/camera/middleware_dbus_amba_eventsservice/cmake-build-debug/tests/lib/googletest/CMakeFiles/gtest_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/lib/googletest/CMakeFiles/gtest_main.dir/depend

