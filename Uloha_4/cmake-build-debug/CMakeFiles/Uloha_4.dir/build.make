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
CMAKE_COMMAND = /snap/clion/17/bin/cmake/bin/cmake

# The command to remove a file.
RM = /snap/clion/17/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Uloha_4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Uloha_4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Uloha_4.dir/flags.make

CMakeFiles/Uloha_4.dir/test.cpp.o: CMakeFiles/Uloha_4.dir/flags.make
CMakeFiles/Uloha_4.dir/test.cpp.o: ../test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Uloha_4.dir/test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Uloha_4.dir/test.cpp.o -c "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4/test.cpp"

CMakeFiles/Uloha_4.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Uloha_4.dir/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4/test.cpp" > CMakeFiles/Uloha_4.dir/test.cpp.i

CMakeFiles/Uloha_4.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Uloha_4.dir/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4/test.cpp" -o CMakeFiles/Uloha_4.dir/test.cpp.s

CMakeFiles/Uloha_4.dir/test.cpp.o.requires:

.PHONY : CMakeFiles/Uloha_4.dir/test.cpp.o.requires

CMakeFiles/Uloha_4.dir/test.cpp.o.provides: CMakeFiles/Uloha_4.dir/test.cpp.o.requires
	$(MAKE) -f CMakeFiles/Uloha_4.dir/build.make CMakeFiles/Uloha_4.dir/test.cpp.o.provides.build
.PHONY : CMakeFiles/Uloha_4.dir/test.cpp.o.provides

CMakeFiles/Uloha_4.dir/test.cpp.o.provides.build: CMakeFiles/Uloha_4.dir/test.cpp.o


# Object files for target Uloha_4
Uloha_4_OBJECTS = \
"CMakeFiles/Uloha_4.dir/test.cpp.o"

# External object files for target Uloha_4
Uloha_4_EXTERNAL_OBJECTS =

Uloha_4: CMakeFiles/Uloha_4.dir/test.cpp.o
Uloha_4: CMakeFiles/Uloha_4.dir/build.make
Uloha_4: CMakeFiles/Uloha_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Uloha_4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Uloha_4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Uloha_4.dir/build: Uloha_4

.PHONY : CMakeFiles/Uloha_4.dir/build

CMakeFiles/Uloha_4.dir/requires: CMakeFiles/Uloha_4.dir/test.cpp.o.requires

.PHONY : CMakeFiles/Uloha_4.dir/requires

CMakeFiles/Uloha_4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Uloha_4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Uloha_4.dir/clean

CMakeFiles/Uloha_4.dir/depend:
	cd "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4" "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4" "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4/cmake-build-debug" "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4/cmake-build-debug" "/media/tomas/7CCC4C2ACC4BDD50/PA2/Uloha 4/cmake-build-debug/CMakeFiles/Uloha_4.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Uloha_4.dir/depend
