# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = "/Users/David/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.6603.37/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/David/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.6603.37/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device/cmake-build-ttgo-t-beam"

# Include any dependencies generated for this target.
include CMakeFiles/CO657-IoT_Device.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CO657-IoT_Device.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CO657-IoT_Device.dir/flags.make

CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.o: CMakeFiles/CO657-IoT_Device.dir/flags.make
CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device/cmake-build-ttgo-t-beam/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.o"
	/Users/David/.platformio/packages/toolchain-xtensa32/bin/xtensa-esp32-elf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.o -c "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device/src/main.cpp"

CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.i"
	/Users/David/.platformio/packages/toolchain-xtensa32/bin/xtensa-esp32-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device/src/main.cpp" > CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.i

CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.s"
	/Users/David/.platformio/packages/toolchain-xtensa32/bin/xtensa-esp32-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device/src/main.cpp" -o CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.s

# Object files for target CO657-IoT_Device
CO657__IoT_Device_OBJECTS = \
"CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.o"

# External object files for target CO657-IoT_Device
CO657__IoT_Device_EXTERNAL_OBJECTS =

CO657-IoT_Device: CMakeFiles/CO657-IoT_Device.dir/src/main.cpp.o
CO657-IoT_Device: CMakeFiles/CO657-IoT_Device.dir/build.make
CO657-IoT_Device: CMakeFiles/CO657-IoT_Device.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device/cmake-build-ttgo-t-beam/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CO657-IoT_Device"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CO657-IoT_Device.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CO657-IoT_Device.dir/build: CO657-IoT_Device

.PHONY : CMakeFiles/CO657-IoT_Device.dir/build

CMakeFiles/CO657-IoT_Device.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CO657-IoT_Device.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CO657-IoT_Device.dir/clean

CMakeFiles/CO657-IoT_Device.dir/depend:
	cd "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device/cmake-build-ttgo-t-beam" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device" "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device" "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device/cmake-build-ttgo-t-beam" "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device/cmake-build-ttgo-t-beam" "/Users/David/Documents/University of Kent/Year 3/CO657/CO657-Assignments/CO657-Assignment-2-&-3/CO657-IoT_Device/cmake-build-ttgo-t-beam/CMakeFiles/CO657-IoT_Device.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/CO657-IoT_Device.dir/depend

