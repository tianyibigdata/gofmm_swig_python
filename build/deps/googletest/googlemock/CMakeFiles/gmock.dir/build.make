# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build

# Include any dependencies generated for this target.
include deps/googletest/googlemock/CMakeFiles/gmock.dir/depend.make

# Include the progress variables for this target.
include deps/googletest/googlemock/CMakeFiles/gmock.dir/progress.make

# Include the compile flags for this target's objects.
include deps/googletest/googlemock/CMakeFiles/gmock.dir/flags.make

deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o: deps/googletest/googlemock/CMakeFiles/gmock.dir/flags.make
deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o: ../deps/googletest/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o"
	cd /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o -c /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/deps/googletest/googletest/src/gtest-all.cc

deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.i"
	cd /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/deps/googletest/googletest/src/gtest-all.cc > CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.i

deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.s"
	cd /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/deps/googletest/googletest/src/gtest-all.cc -o CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.s

deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o.requires:

.PHONY : deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o.requires

deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o.provides: deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o.requires
	$(MAKE) -f deps/googletest/googlemock/CMakeFiles/gmock.dir/build.make deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o.provides.build
.PHONY : deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o.provides

deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o.provides.build: deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o


deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o: deps/googletest/googlemock/CMakeFiles/gmock.dir/flags.make
deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o: ../deps/googletest/googlemock/src/gmock-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o"
	cd /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock.dir/src/gmock-all.cc.o -c /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/deps/googletest/googlemock/src/gmock-all.cc

deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock.dir/src/gmock-all.cc.i"
	cd /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/deps/googletest/googlemock/src/gmock-all.cc > CMakeFiles/gmock.dir/src/gmock-all.cc.i

deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock.dir/src/gmock-all.cc.s"
	cd /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/deps/googletest/googlemock/src/gmock-all.cc -o CMakeFiles/gmock.dir/src/gmock-all.cc.s

deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o.requires:

.PHONY : deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o.requires

deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o.provides: deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o.requires
	$(MAKE) -f deps/googletest/googlemock/CMakeFiles/gmock.dir/build.make deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o.provides.build
.PHONY : deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o.provides

deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o.provides.build: deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o


# Object files for target gmock
gmock_OBJECTS = \
"CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o" \
"CMakeFiles/gmock.dir/src/gmock-all.cc.o"

# External object files for target gmock
gmock_EXTERNAL_OBJECTS =

deps/googletest/googlemock/libgmock.a: deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o
deps/googletest/googlemock/libgmock.a: deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
deps/googletest/googlemock/libgmock.a: deps/googletest/googlemock/CMakeFiles/gmock.dir/build.make
deps/googletest/googlemock/libgmock.a: deps/googletest/googlemock/CMakeFiles/gmock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libgmock.a"
	cd /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock.dir/cmake_clean_target.cmake
	cd /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gmock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/googletest/googlemock/CMakeFiles/gmock.dir/build: deps/googletest/googlemock/libgmock.a

.PHONY : deps/googletest/googlemock/CMakeFiles/gmock.dir/build

deps/googletest/googlemock/CMakeFiles/gmock.dir/requires: deps/googletest/googlemock/CMakeFiles/gmock.dir/__/googletest/src/gtest-all.cc.o.requires
deps/googletest/googlemock/CMakeFiles/gmock.dir/requires: deps/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o.requires

.PHONY : deps/googletest/googlemock/CMakeFiles/gmock.dir/requires

deps/googletest/googlemock/CMakeFiles/gmock.dir/clean:
	cd /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock.dir/cmake_clean.cmake
.PHONY : deps/googletest/googlemock/CMakeFiles/gmock.dir/clean

deps/googletest/googlemock/CMakeFiles/gmock.dir/depend:
	cd /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1 /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/deps/googletest/googlemock /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock /home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest/googlemock/CMakeFiles/gmock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/googletest/googlemock/CMakeFiles/gmock.dir/depend
