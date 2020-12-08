cmake_minimum_required( VERSION 3.18.4 )

project(NoEucRT)

#add_subdirectory(dependencies/SFML-2.5.1)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

add_executable(NoEucRT src/main.cpp)
target_link_libraries(NoEucRT sfml-graphics sfml-window)
