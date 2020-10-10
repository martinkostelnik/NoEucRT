cmake_minimum_required( VERSION 3.18.4 )

project( NoEucRT )

find_package( OpenGL REQUIRED )

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

add_subdirectory( glfw-3.3.2 )

add_executable( NoEucRT src/main.cpp)
target_link_libraries( NoEucRT glfw )
