# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jonathan/Desktop/inf8601/lab_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jonathan/Desktop/inf8601/lab_1/build

# Utility rule file for run-pthread.

# Include any custom commands dependencies for this target.
include CMakeFiles/run-pthread.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/run-pthread.dir/progress.make

CMakeFiles/run-pthread:
	cd /home/jonathan/Desktop/inf8601/lab_1 && time /home/jonathan/Desktop/inf8601/lab_1/build/pipeline --directory /home/jonathan/Desktop/inf8601/lab_1/data --pipeline pthread

run-pthread: CMakeFiles/run-pthread
run-pthread: CMakeFiles/run-pthread.dir/build.make
.PHONY : run-pthread

# Rule to build all files generated by this target.
CMakeFiles/run-pthread.dir/build: run-pthread
.PHONY : CMakeFiles/run-pthread.dir/build

CMakeFiles/run-pthread.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/run-pthread.dir/cmake_clean.cmake
.PHONY : CMakeFiles/run-pthread.dir/clean

CMakeFiles/run-pthread.dir/depend:
	cd /home/jonathan/Desktop/inf8601/lab_1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jonathan/Desktop/inf8601/lab_1 /home/jonathan/Desktop/inf8601/lab_1 /home/jonathan/Desktop/inf8601/lab_1/build /home/jonathan/Desktop/inf8601/lab_1/build /home/jonathan/Desktop/inf8601/lab_1/build/CMakeFiles/run-pthread.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/run-pthread.dir/depend

