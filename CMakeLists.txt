cmake_minimum_required( VERSION 3.18.4 )

project(NoEucRT)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window main REQUIRED)

set(glm_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm-0.9.9.8/cmake/glm)
find_package(glm REQUIRED)

if (MSVC)
	add_compile_options(/openmp:experimental /O2 /Ob2 /Ot)
endif()

add_executable(NoEucRT src/main.cpp
			   src/NoEucEngine.hpp src/NoEucEngine.cpp
			   src/MovementHandler.hpp src/MovementHandler.cpp
			   src/Renderer.hpp src/Renderer.cpp
			   src/Camera.hpp src/Camera.cpp
			   src/Scene.hpp src/Scene.cpp
			   src/Ray.hpp src/Ray.cpp
			   src/Model.hpp src/Model.cpp
			   src/Portal.hpp src/Portal.cpp
			   src/WarpedTunnel.hpp src/WarpedTunnel.cpp
			   src/ShrinkTunnel.hpp src/ShrinkTunnel.cpp
			   src/RotationTunnel.hpp src/RotationTunnel.cpp
			   src/Triangle.hpp src/Triangle.cpp
			   src/AABB.hpp src/AABB.cpp
			   src/Light.hpp src/Light.cpp
			   src/Shader.hpp src/Shader.cpp
			   src/LambertianShader.hpp src/LambertianShader.cpp
			   src/PhongShader.hpp src/PhongShader.cpp
			   src/Material.hpp src/Material.cpp
			   src/Skybox.hpp src/Skybox.cpp)
target_link_libraries(NoEucRT sfml-graphics sfml-window glm::glm)
				
add_custom_command(
        TARGET NoEucRT POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/resources/
                ${CMAKE_CURRENT_BINARY_DIR}/Release/resources/)
				
add_custom_command(
        TARGET NoEucRT POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/resources/
                ${CMAKE_CURRENT_BINARY_DIR}/resources/)
