#include "Camera.hpp"

#include "Camera.hpp"

Camera::Camera()
{
	fov = 90;

	toWorld = { glm::vec4(1,  0,  0,  0),
				glm::vec4(0,  1,  0,  0),
				glm::vec4(0,  0,  1,  0), 
				glm::vec4(0,  0,  0,  1)};
}
