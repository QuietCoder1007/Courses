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
CMAKE_SOURCE_DIR = "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\transHexagon.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\transHexagon.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\transHexagon.dir\flags.make

CMakeFiles\transHexagon.dir\transHexagon.cpp.obj: CMakeFiles\transHexagon.dir\flags.make
CMakeFiles\transHexagon.dir\transHexagon.cpp.obj: ..\transHexagon.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/transHexagon.dir/transHexagon.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\transHexagon.dir\transHexagon.cpp.obj /FdCMakeFiles\transHexagon.dir\ /FS -c "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\transHexagon.cpp"
<<

CMakeFiles\transHexagon.dir\transHexagon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/transHexagon.dir/transHexagon.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe > CMakeFiles\transHexagon.dir\transHexagon.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\transHexagon.cpp"
<<

CMakeFiles\transHexagon.dir\transHexagon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/transHexagon.dir/transHexagon.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\transHexagon.dir\transHexagon.cpp.s /c "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\transHexagon.cpp"
<<

CMakeFiles\transHexagon.dir\utils.cpp.obj: CMakeFiles\transHexagon.dir\flags.make
CMakeFiles\transHexagon.dir\utils.cpp.obj: ..\utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/transHexagon.dir/utils.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\transHexagon.dir\utils.cpp.obj /FdCMakeFiles\transHexagon.dir\ /FS -c "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\utils.cpp"
<<

CMakeFiles\transHexagon.dir\utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/transHexagon.dir/utils.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe > CMakeFiles\transHexagon.dir\utils.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\utils.cpp"
<<

CMakeFiles\transHexagon.dir\utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/transHexagon.dir/utils.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\transHexagon.dir\utils.cpp.s /c "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\utils.cpp"
<<

# Object files for target transHexagon
transHexagon_OBJECTS = \
"CMakeFiles\transHexagon.dir\transHexagon.cpp.obj" \
"CMakeFiles\transHexagon.dir\utils.cpp.obj"

# External object files for target transHexagon
transHexagon_EXTERNAL_OBJECTS =

..\bin\transHexagon.exe: CMakeFiles\transHexagon.dir\transHexagon.cpp.obj
..\bin\transHexagon.exe: CMakeFiles\transHexagon.dir\utils.cpp.obj
..\bin\transHexagon.exe: CMakeFiles\transHexagon.dir\build.make
..\bin\transHexagon.exe: CMakeFiles\transHexagon.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ..\bin\transHexagon.exe"
	"C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\transHexagon.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\mt.exe --manifests  -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\transHexagon.dir\objects1.rsp @<<
 /out:..\bin\transHexagon.exe /implib:transHexagon.lib /pdb:"C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\bin\transHexagon.pdb" /version:0.0  /machine:x64 /debug /INCREMENTAL /subsystem:console   -LIBPATH:C:\Users\lqlas\OneDrive\DOCUME~1\YCP_20~1\Fall\2020\CS370-~1\Labs\CS370_~3\lib\Win  opengl32.lib glfw3.lib glew32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\transHexagon.dir\build: ..\bin\transHexagon.exe

.PHONY : CMakeFiles\transHexagon.dir\build

CMakeFiles\transHexagon.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\transHexagon.dir\cmake_clean.cmake
.PHONY : CMakeFiles\transHexagon.dir\clean

CMakeFiles\transHexagon.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03" "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03" "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\cmake-build-debug" "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\cmake-build-debug" "C:\Users\lqlas\OneDrive\Documents\YCP_2018-2022\Fall\2020\CS 370-102\Labs\CS370_Lab03\cmake-build-debug\CMakeFiles\transHexagon.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\transHexagon.dir\depend

