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
CMAKE_SOURCE_DIR = /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party

# Include any dependencies generated for this target.
include CMakeFiles/thread_pool.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/thread_pool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/thread_pool.dir/flags.make

CMakeFiles/thread_pool.dir/thr_pool.c.o: CMakeFiles/thread_pool.dir/flags.make
CMakeFiles/thread_pool.dir/thr_pool.c.o: thr_pool.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/thread_pool.dir/thr_pool.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/thread_pool.dir/thr_pool.c.o   -c /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party/thr_pool.c

CMakeFiles/thread_pool.dir/thr_pool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/thread_pool.dir/thr_pool.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party/thr_pool.c > CMakeFiles/thread_pool.dir/thr_pool.c.i

CMakeFiles/thread_pool.dir/thr_pool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/thread_pool.dir/thr_pool.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party/thr_pool.c -o CMakeFiles/thread_pool.dir/thr_pool.c.s

CMakeFiles/thread_pool.dir/thr_pool.c.o.requires:

.PHONY : CMakeFiles/thread_pool.dir/thr_pool.c.o.requires

CMakeFiles/thread_pool.dir/thr_pool.c.o.provides: CMakeFiles/thread_pool.dir/thr_pool.c.o.requires
	$(MAKE) -f CMakeFiles/thread_pool.dir/build.make CMakeFiles/thread_pool.dir/thr_pool.c.o.provides.build
.PHONY : CMakeFiles/thread_pool.dir/thr_pool.c.o.provides

CMakeFiles/thread_pool.dir/thr_pool.c.o.provides.build: CMakeFiles/thread_pool.dir/thr_pool.c.o


# Object files for target thread_pool
thread_pool_OBJECTS = \
"CMakeFiles/thread_pool.dir/thr_pool.c.o"

# External object files for target thread_pool
thread_pool_EXTERNAL_OBJECTS =

libthread_pool.a: CMakeFiles/thread_pool.dir/thr_pool.c.o
libthread_pool.a: CMakeFiles/thread_pool.dir/build.make
libthread_pool.a: CMakeFiles/thread_pool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libthread_pool.a"
	$(CMAKE_COMMAND) -P CMakeFiles/thread_pool.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/thread_pool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/thread_pool.dir/build: libthread_pool.a

.PHONY : CMakeFiles/thread_pool.dir/build

CMakeFiles/thread_pool.dir/requires: CMakeFiles/thread_pool.dir/thr_pool.c.o.requires

.PHONY : CMakeFiles/thread_pool.dir/requires

CMakeFiles/thread_pool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/thread_pool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/thread_pool.dir/clean

CMakeFiles/thread_pool.dir/depend:
	cd /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party /home/jaewoo/Desktop/casual_workspace/optimize-convolution-problem/third_party/CMakeFiles/thread_pool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/thread_pool.dir/depend

