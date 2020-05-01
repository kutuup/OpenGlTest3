#include "PhysicsEffector.h"
#include "d_Player.h"
#include "e_EnemyBase.h"


PhysicsEffector::PhysicsEffector()
{
	velocity = new glm::vec3();
}


PhysicsEffector::~PhysicsEffector()
{
}

void PhysicsEffector::updateAttachedObject()
{
	if (!attachedObject->grounded)
	{
		attachedObject->Position->y -= gravityScale;
		attachedObject->updateColliders();
	}
	attachedObject->Position->y += velocity->y;
	attachedObject->Position->x += velocity->x;
	attachedObject->Position->z += velocity->z;
}

void PhysicsEffector::updateAttachedEnemy()
{
	if (!attachedEnemy->grounded)
	{
		attachedEnemy->pos->y -= gravityScale;
		attachedEnemy->updateColliders();
	}
	attachedEnemy->pos->y += velocity->y;
	attachedEnemy->pos->x += velocity->x;
	attachedEnemy->pos->z += velocity->z;
}
