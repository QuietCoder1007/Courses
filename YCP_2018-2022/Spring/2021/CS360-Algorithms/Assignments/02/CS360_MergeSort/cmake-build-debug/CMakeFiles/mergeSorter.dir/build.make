# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\mergeSorter.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\mergeSorter.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\mergeSorter.dir\flags.make

CMakeFiles\mergeSorter.dir\mergeSorter.cpp.obj: CMakeFiles\mergeSorter.dir\flags.make
CMakeFiles\mergeSorter.dir\mergeSorter.cpp.obj: ..\mergeSorter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mergeSorter.dir/mergeSorter.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\mergeSorter.dir\mergeSorter.cpp.obj /FdCMakeFiles\mergeSorter.dir\ /FS -c C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort\mergeSorter.cpp
<<

CMakeFiles\mergeSorter.dir\mergeSorter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mergeSorter.dir/mergeSorter.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\mergeSorter.dir\mergeSorter.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort\mergeSorter.cpp
<<

CMakeFiles\mergeSorter.dir\mergeSorter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mergeSorter.dir/mergeSorter.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\mergeSorter.dir\mergeSorter.cpp.s /c C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort\mergeSorter.cpp
<<

# Object files for target mergeSorter
mergeSorter_OBJECTS = \
"CMakeFiles\mergeSorter.dir\mergeSorter.cpp.obj"

# External object files for target mergeSorter
mergeSorter_EXTERNAL_OBJECTS =

..\bin\mergeSorter.exe: CMakeFiles\mergeSorter.dir\mergeSorter.cpp.obj
..\bin\mergeSorter.exe: CMakeFiles\mergeSorter.dir\build.make
..\bin\mergeSorter.exe: CMakeFiles\mergeSorter.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\bin\mergeSorter.exe"
	"C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\mergeSorter.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\mt.exe --manifests  -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\mergeSorter.dir\objects1.rsp @<<
 /out:..\bin\mergeSorter.exe /implib:mergeSorter.lib /pdb:C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort\bin\mergeSorter.pdb /version:0.0  /machine:x64 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\mergeSorter.dir\build: ..\bin\mergeSorter.exe

.PHONY : CMakeFiles\mergeSorter.dir\build

CMakeFiles\mergeSorter.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mergeSorter.dir\cmake_clean.cmake
.PHONY : CMakeFiles\mergeSorter.dir\clean

CMakeFiles\mergeSorter.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort\cmake-build-debug C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort\cmake-build-debug C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Spring\2021\CS360-Algorithms\Assignments\02\CS360_MergeSort\cmake-build-debug\CMakeFiles\mergeSorter.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\mergeSorter.dir\depend
