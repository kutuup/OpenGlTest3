#pragma once
//#include "d_Player.h"
#include "glm\glm.hpp"

class d_Player;
class e_EnemyBase;

class PhysicsEffector
{
public:

	d_Player* attachedObject;
	e_EnemyBase* attachedEnemy;
	float gravityScale;
	glm::vec3* velocity;
	bool active;

	void updateAttachedObject();
	void updateAttachedEnemy();
	PhysicsEffector();
	~PhysicsEffector();
};

