#pragma once

#include "BudgieApp.h"
#include "Math.h"

class AIAgent
{
public:

	float moveSpeed;

	glm::vec3* targetPos;
	glm::vec3* wishDir;

	void AIAgent::changeDir();
	void setInitialDir();
	void AIAgent::SeekTarget();

	AIAgent();
	~AIAgent();
};

