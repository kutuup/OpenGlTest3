#pragma once

#include "BudgieApp.h"

class Math
{
public:
	Math();
	~Math();

	static glm::vec3 vec3Subtract(glm::vec3* a, glm::vec3* b);
	static int Math::pointInRect(int nvert, float *vertx, float *verty, float testx, float testy);
	
};



