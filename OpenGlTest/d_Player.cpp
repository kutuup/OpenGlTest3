#include "d_Player.h"
#include "BudgieApp.h"

float d_Player::getX()
{
	return Position->x;
}

float d_Player::getZ()
{
	return Position->z;
}

void d_Player::setX(float value)
{
	Position->x = value;
}

void d_Player::setZ(float value)
{
	Position->z = value;
}

void d_Player::changeHealth(int change)
{
	health += change;
}

int d_Player::getHealth()
{
	return health;
}

d_Player::d_Player()
{

}

d_Player::d_Player(glm::vec3* startPos)
{
	health = 100;

	Position = new glm::vec3();
	Position->x = startPos->x;
	Position->y = startPos->y + 1;
	Position->z = startPos->z;
	Forward = new glm::vec3();
	Forward->x = startPos->x;
	Forward->y = startPos->y + 1;
	Forward->z = startPos->z;
	colliders = new std::vector<p_BoxCollider*>();
	weapons = new std::vector<d_Weapon*>();
}


d_Player::~d_Player()
{
}

void d_Player::addCollider(p_BoxCollider* c)
{
	colliders->push_back(c);
	std::cout << std::endl << "Player Colliders: " << colliders->size();
}

void d_Player::updateColliders()
{
	for (int count = 0; count < colliders->size(); count++)
	{
		recenterCollider(colliders->at(count));
	}
}

void d_Player::recenterCollider(p_BoxCollider* c)
{
	if (c->tracking == true)
	{
		c->center = Position;
	}
}

void d_Player::updateWeapon()
{
	currWeapon->checkUpdate();
}
