#pragma once
#include "e_EnemyBase.h"
class e_Soldier :
	public e_EnemyBase
{
public:
	e_Soldier();
	e_Soldier(glm::vec3* pos, glm::vec3* facing, int health, float width, float height);
	~e_Soldier();
};

