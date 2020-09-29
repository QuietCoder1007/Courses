cmake_minimum_required(VERSION 3.16)   # CMake version check
project(RollinTrain)                        # Create project "RollinTrain"
set(CMAKE_CXX_STANDARD 11)             # Enable c++11 standard
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#add include and link directories
if(APPLE)
    find_library(cf_lib CoreFoundation)
    find_library(cg_lib CoreGraphics)
    find_library(cocoa_lib Cocoa)
    find_library(io_lib IOKit)
    link_directories(${CMAKE_SOURCE_DIR}/lib/MacOSX)
elseif(WIN32)
	file(COPY ${CMAKE_SOURCE_DIR}/lib/Win/glew32.dll DESTINATION ${CMAKE_SOURCE_DIR}/bin)
	file(COPY ${CMAKE_SOURCE_DIR}/lib/Win/glfw3.dll DESTINATION ${CMAKE_SOURCE_DIR}/bin)
    link_directories(${CMAKE_SOURCE_DIR}/lib/Win)
endif()

#Main
set(SOURCE_FILES RollinTrain.cpp objloader.cpp utils.cpp)
add_executable(RollinTrain ${SOURCE_FILES})

if(APPLE)
    # Add Apple frameworks
    target_link_libraries(RollinTrain ${cf_lib})
    target_link_libraries(RollinTrain ${cg_lib})
    target_link_libraries(RollinTrain ${cocoa_lib})
    target_link_libraries(RollinTrain ${io_lib})

    # Add GLFW and GLEW libraries
    target_link_libraries(RollinTrain ${OPENGL_gl_LIBRARY})
    target_link_libraries(RollinTrain glfw3)
    target_link_libraries(RollinTrain glew)
elseif(WIN32)
    # Add GLFW and GLEW libraries
    target_link_libraries(RollinTrain ${OPENGL_gl_LIBRARY})
    target_link_libraries(RollinTrain glfw3)
    target_link_libraries(RollinTrain glew32)
else()
    target_link_libraries(RollinTrain OpenGL::GL)
    target_link_libraries(RollinTrain glfw)
    target_link_libraries(RollinTrain GLEW)
endif()

add_custom_target(MAKE_ZIP DEPENDS output)
add_custom_command(OUTPUT output
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMAND ${CMAKE_COMMAND} -E tar cfv ${CMAKE_SOURCE_DIR}/solution.zip --format=zip --files-from=${CMAKE_SOURCE_DIR}/submit.txt
)



