cmake_minimum_required( VERSION 3.18.4 )

project(NoEucRT)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

set(glm_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm-0.9.9.8/cmake/glm")
find_package(glm REQUIRED)

add_executable(NoEucRT src/main.cpp)
target_link_libraries(NoEucRT sfml-graphics sfml-window glm)
