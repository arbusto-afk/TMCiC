# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/arb/mcbc6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arb/mcbc6/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mcbc6.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mcbc6.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mcbc6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mcbc6.dir/flags.make

CMakeFiles/mcbc6.dir/main.c.o: CMakeFiles/mcbc6.dir/flags.make
CMakeFiles/mcbc6.dir/main.c.o: ../main.c
CMakeFiles/mcbc6.dir/main.c.o: CMakeFiles/mcbc6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arb/mcbc6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mcbc6.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mcbc6.dir/main.c.o -MF CMakeFiles/mcbc6.dir/main.c.o.d -o CMakeFiles/mcbc6.dir/main.c.o -c /home/arb/mcbc6/main.c

CMakeFiles/mcbc6.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mcbc6.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arb/mcbc6/main.c > CMakeFiles/mcbc6.dir/main.c.i

CMakeFiles/mcbc6.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mcbc6.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arb/mcbc6/main.c -o CMakeFiles/mcbc6.dir/main.c.s

CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.o: CMakeFiles/mcbc6.dir/flags.make
CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.o: ../TVarInt/sharedmain.c
CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.o: CMakeFiles/mcbc6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arb/mcbc6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.o -MF CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.o.d -o CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.o -c /home/arb/mcbc6/TVarInt/sharedmain.c

CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arb/mcbc6/TVarInt/sharedmain.c > CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.i

CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arb/mcbc6/TVarInt/sharedmain.c -o CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.s

CMakeFiles/mcbc6.dir/Parser/parser.c.o: CMakeFiles/mcbc6.dir/flags.make
CMakeFiles/mcbc6.dir/Parser/parser.c.o: ../Parser/parser.c
CMakeFiles/mcbc6.dir/Parser/parser.c.o: CMakeFiles/mcbc6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arb/mcbc6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/mcbc6.dir/Parser/parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mcbc6.dir/Parser/parser.c.o -MF CMakeFiles/mcbc6.dir/Parser/parser.c.o.d -o CMakeFiles/mcbc6.dir/Parser/parser.c.o -c /home/arb/mcbc6/Parser/parser.c

CMakeFiles/mcbc6.dir/Parser/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mcbc6.dir/Parser/parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arb/mcbc6/Parser/parser.c > CMakeFiles/mcbc6.dir/Parser/parser.c.i

CMakeFiles/mcbc6.dir/Parser/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mcbc6.dir/Parser/parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arb/mcbc6/Parser/parser.c -o CMakeFiles/mcbc6.dir/Parser/parser.c.s

CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.o: CMakeFiles/mcbc6.dir/flags.make
CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.o: ../TVarInt/TVarint.c
CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.o: CMakeFiles/mcbc6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arb/mcbc6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.o -MF CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.o.d -o CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.o -c /home/arb/mcbc6/TVarInt/TVarint.c

CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arb/mcbc6/TVarInt/TVarint.c > CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.i

CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arb/mcbc6/TVarInt/TVarint.c -o CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.s

CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.o: CMakeFiles/mcbc6.dir/flags.make
CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.o: ../crossSocket/crossSocket.c
CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.o: CMakeFiles/mcbc6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arb/mcbc6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.o -MF CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.o.d -o CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.o -c /home/arb/mcbc6/crossSocket/crossSocket.c

CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arb/mcbc6/crossSocket/crossSocket.c > CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.i

CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arb/mcbc6/crossSocket/crossSocket.c -o CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.s

CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.o: CMakeFiles/mcbc6.dir/flags.make
CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.o: ../pDef_v1_12_2_2.c
CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.o: CMakeFiles/mcbc6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arb/mcbc6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.o -MF CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.o.d -o CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.o -c /home/arb/mcbc6/pDef_v1_12_2_2.c

CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arb/mcbc6/pDef_v1_12_2_2.c > CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.i

CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arb/mcbc6/pDef_v1_12_2_2.c -o CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.s

CMakeFiles/mcbc6.dir/file_io/file_io.c.o: CMakeFiles/mcbc6.dir/flags.make
CMakeFiles/mcbc6.dir/file_io/file_io.c.o: ../file_io/file_io.c
CMakeFiles/mcbc6.dir/file_io/file_io.c.o: CMakeFiles/mcbc6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arb/mcbc6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/mcbc6.dir/file_io/file_io.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mcbc6.dir/file_io/file_io.c.o -MF CMakeFiles/mcbc6.dir/file_io/file_io.c.o.d -o CMakeFiles/mcbc6.dir/file_io/file_io.c.o -c /home/arb/mcbc6/file_io/file_io.c

CMakeFiles/mcbc6.dir/file_io/file_io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mcbc6.dir/file_io/file_io.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arb/mcbc6/file_io/file_io.c > CMakeFiles/mcbc6.dir/file_io/file_io.c.i

CMakeFiles/mcbc6.dir/file_io/file_io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mcbc6.dir/file_io/file_io.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arb/mcbc6/file_io/file_io.c -o CMakeFiles/mcbc6.dir/file_io/file_io.c.s

# Object files for target mcbc6
mcbc6_OBJECTS = \
"CMakeFiles/mcbc6.dir/main.c.o" \
"CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.o" \
"CMakeFiles/mcbc6.dir/Parser/parser.c.o" \
"CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.o" \
"CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.o" \
"CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.o" \
"CMakeFiles/mcbc6.dir/file_io/file_io.c.o"

# External object files for target mcbc6
mcbc6_EXTERNAL_OBJECTS =

mcbc6: CMakeFiles/mcbc6.dir/main.c.o
mcbc6: CMakeFiles/mcbc6.dir/TVarInt/sharedmain.c.o
mcbc6: CMakeFiles/mcbc6.dir/Parser/parser.c.o
mcbc6: CMakeFiles/mcbc6.dir/TVarInt/TVarint.c.o
mcbc6: CMakeFiles/mcbc6.dir/crossSocket/crossSocket.c.o
mcbc6: CMakeFiles/mcbc6.dir/pDef_v1_12_2_2.c.o
mcbc6: CMakeFiles/mcbc6.dir/file_io/file_io.c.o
mcbc6: CMakeFiles/mcbc6.dir/build.make
mcbc6: CMakeFiles/mcbc6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arb/mcbc6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable mcbc6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mcbc6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mcbc6.dir/build: mcbc6
.PHONY : CMakeFiles/mcbc6.dir/build

CMakeFiles/mcbc6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mcbc6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mcbc6.dir/clean

CMakeFiles/mcbc6.dir/depend:
	cd /home/arb/mcbc6/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arb/mcbc6 /home/arb/mcbc6 /home/arb/mcbc6/cmake-build-debug /home/arb/mcbc6/cmake-build-debug /home/arb/mcbc6/cmake-build-debug/CMakeFiles/mcbc6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mcbc6.dir/depend
