#include "Camera.h"
#include "BudgieApp.h"

Camera::Camera()
{
	Position = new glm::vec3();
	Position->x = 0.0;
	Position->y = 0.0;
	Position->z = 0.0;
	Rotation = new glm::vec3();
	Rotation->x = 0.0;
	Rotation->y = 0.0;
	Rotation->z = 0.0;
	Target = new glm::vec3();
	Target->x = 0.0;
	Target->y = 0.0;
	Target->z = Position->z -1.0;
}


Camera::~Camera()
{
}

void Camera::updateTarget(glm::vec3* forward)
{
	Target->x = forward->x;
	Target->y = forward->y;
	Target->z = forward->z - 1.0;
}
