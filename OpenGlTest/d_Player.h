#pragma once
//#include "Math.h"

//#include "p_Collider.h"
#include "p_BoxCollider.h"
#include "PhysicsEffector.h"
//#include "glm\glm.hpp"
#include "BudgieApp.h"
#include "d_Weapon.h"
#include <vector>
#include "g_floor.h"

//class p_BoxCollider;

class d_Player
{
public:
	d_Player();
	d_Player(glm::vec3* startPos);
	~d_Player();

	glm::vec3* Position;
	glm::vec3* Forward;

	g_floor* lastFloor;

	PhysicsEffector* pEffector;

	bool grounded;

	float runSpeed;
	float turnSpeed;

	std::vector<p_BoxCollider*>* d_Player::colliders;

	void d_Player::setX(float value);

	float d_Player::getX();

	void d_Player::setZ(float value);

	float d_Player::getZ();

	void d_Player::addCollider(p_BoxCollider* c);

	void d_Player::recenterCollider(p_BoxCollider* c);

	void d_Player::updateColliders();

	void d_Player::changeHealth(int change);

	void d_Player::updateWeapon();

	int d_Player::getHealth();

	std::vector<d_Weapon*>* weapons;

	d_Weapon* currWeapon;

private:
	//float x;
	//float z;
	int health;
	int ammo;
	int score;
	int lives;
};

