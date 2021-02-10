cmake_minimum_required( VERSION 3.18.4 )

project(NoEucRT)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

set(glm_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm-0.9.9.8/cmake/glm)
find_package(glm REQUIRED)

add_executable(NoEucRT src/main.cpp
			   src/NoEucEngine.hpp src/NoEucEngine.cpp
			   src/Renderer.hpp src/Renderer.cpp
			   src/Camera.hpp src/Camera.cpp
			   src/Scene.hpp src/Scene.cpp
			   src/Ray.hpp src/Ray.cpp
			   src/Model.hpp src/Model.cpp
			   src/Triangle.hpp src/Triangle.cpp
			   src/AABB.hpp src/AABB.cpp
			   src/BVH.hpp src/BVH.cpp
			   src/BVHNode.hpp src/BVHNode.cpp)
target_link_libraries(NoEucRT sfml-graphics sfml-window glm::glm)
