# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/yongheng/Study/CMake/library

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yongheng/Study/CMake/library/build

# Include any dependencies generated for this target.
include src/CMakeFiles/hello.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/hello.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/hello.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/hello.dir/flags.make

src/CMakeFiles/hello.dir/hello.o: src/CMakeFiles/hello.dir/flags.make
src/CMakeFiles/hello.dir/hello.o: /home/yongheng/Study/CMake/library/src/hello.cpp
src/CMakeFiles/hello.dir/hello.o: src/CMakeFiles/hello.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongheng/Study/CMake/library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/hello.dir/hello.o"
	cd /home/yongheng/Study/CMake/library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/hello.dir/hello.o -MF CMakeFiles/hello.dir/hello.o.d -o CMakeFiles/hello.dir/hello.o -c /home/yongheng/Study/CMake/library/src/hello.cpp

src/CMakeFiles/hello.dir/hello.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hello.dir/hello.i"
	cd /home/yongheng/Study/CMake/library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongheng/Study/CMake/library/src/hello.cpp > CMakeFiles/hello.dir/hello.i

src/CMakeFiles/hello.dir/hello.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hello.dir/hello.s"
	cd /home/yongheng/Study/CMake/library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongheng/Study/CMake/library/src/hello.cpp -o CMakeFiles/hello.dir/hello.s

# Object files for target hello
hello_OBJECTS = \
"CMakeFiles/hello.dir/hello.o"

# External object files for target hello
hello_EXTERNAL_OBJECTS =

src/OUTDIR/libhello.so.1.2: src/CMakeFiles/hello.dir/hello.o
src/OUTDIR/libhello.so.1.2: src/CMakeFiles/hello.dir/build.make
src/OUTDIR/libhello.so.1.2: src/CMakeFiles/hello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yongheng/Study/CMake/library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library OUTDIR/libhello.so"
	cd /home/yongheng/Study/CMake/library/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello.dir/link.txt --verbose=$(VERBOSE)
	cd /home/yongheng/Study/CMake/library/build/src && $(CMAKE_COMMAND) -E cmake_symlink_library OUTDIR/libhello.so.1.2 OUTDIR/libhello.so.1 OUTDIR/libhello.so

src/OUTDIR/libhello.so.1: src/OUTDIR/libhello.so.1.2
	@$(CMAKE_COMMAND) -E touch_nocreate src/OUTDIR/libhello.so.1

src/OUTDIR/libhello.so: src/OUTDIR/libhello.so.1.2
	@$(CMAKE_COMMAND) -E touch_nocreate src/OUTDIR/libhello.so

# Rule to build all files generated by this target.
src/CMakeFiles/hello.dir/build: src/OUTDIR/libhello.so
.PHONY : src/CMakeFiles/hello.dir/build

src/CMakeFiles/hello.dir/clean:
	cd /home/yongheng/Study/CMake/library/build/src && $(CMAKE_COMMAND) -P CMakeFiles/hello.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/hello.dir/clean

src/CMakeFiles/hello.dir/depend:
	cd /home/yongheng/Study/CMake/library/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yongheng/Study/CMake/library /home/yongheng/Study/CMake/library/src /home/yongheng/Study/CMake/library/build /home/yongheng/Study/CMake/library/build/src /home/yongheng/Study/CMake/library/build/src/CMakeFiles/hello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/hello.dir/depend
