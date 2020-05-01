#pragma once
#include "Math.h"
#include "glm\glm.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	glm::vec3* Position;
	glm::vec3* Rotation;
	glm::vec3* Target;

	void updateTarget(glm::vec3* forward);
};

