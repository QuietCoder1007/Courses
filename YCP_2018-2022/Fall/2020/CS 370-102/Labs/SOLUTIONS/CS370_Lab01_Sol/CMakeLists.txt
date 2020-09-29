cmake_minimum_required(VERSION 3.16)   # CMake version check
project(basicGeometry)                        # Create project "basicGeometry"
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
set(SOURCE_FILES basicGeometry.cpp utils.cpp)
add_executable(basicGeometry ${SOURCE_FILES})

if(APPLE)
    # Add Apple frameworks
    target_link_libraries(basicGeometry ${cf_lib})
    target_link_libraries(basicGeometry ${cg_lib})
    target_link_libraries(basicGeometry ${cocoa_lib})
    target_link_libraries(basicGeometry ${io_lib})

    # Add GLFW and GLEW libraries
    target_link_libraries(basicGeometry ${OPENGL_gl_LIBRARY})
    target_link_libraries(basicGeometry glfw3)
    target_link_libraries(basicGeometry glew)
elseif(WIN32)
    # Add GLFW and GLEW libraries
    target_link_libraries(basicGeometry ${OPENGL_gl_LIBRARY})
    target_link_libraries(basicGeometry glfw3)
    target_link_libraries(basicGeometry glew32)
else()
    target_link_libraries(basicGeometry OpenGL::GL)
    target_link_libraries(basicGeometry glfw)
    target_link_libraries(basicGeometry GLEW)
endif()



