#pragma once
#include "BudgieApp.h"
#include "p_BoxCollider.h"
#include "AIAgent.h"
#include "PhysicsEffector.h"
#include "g_floor.h"


namespace budgie
{
const int ENEMYWALKFRAME1 = 0;
const int ENEMYWALKFRAME2 =1;
const int ENEMYWALKFRAME3 =2;
const int ENEMYWALKFRAME4 =3;
const int ENEMYIDLEFRAME1 =4;
const int ENEMYATTACKFRAME1 =10;
const int ENEMYATTACKFRAME2 =11;
const int ENEMYATTACKFRAME3 =12;
const int ENEMYDEATHFRAME1 = 4;
const int ENEMYDEATHFRAME2 = 5;
const int ENEMYDEATHFRAME3 = 6;
const int ENEMYDEATHFRAME4 = 7;
const int ENEMYDEATHFRAME5 = 8;
	enum EnemyState { idle, patrol, attack };
}

class e_EnemyBase
{
public:

	AIAgent* attachedAgent;
	g_floor* lastFloor;
	PhysicsEffector* physics;
	p_BoxCollider* col;
	glm::vec3* pos;
	glm::vec3* normalDir;
	glm::vec3* facing;
	budgie::EnemyState state;
	bool awake;
	bool dead;
	bool grounded;

	int health;
	int dirFramOffset;
	int frameUpdateRate;
	int currentFrameID;

	std::chrono::milliseconds msAtLastUpdate;

	float width;
	float height;

	std::vector < std::vector<float>>* rect;
	std::vector <GLuint*>* imgLib;
	GLuint* currImg;

	e_EnemyBase();
	e_EnemyBase(glm::vec3* pos, glm::vec3* facing, int health, float width, float height);
	~e_EnemyBase();

	void updateColliders();
	void recenterCollider(p_BoxCollider* c);
	void updateRect();
	void checkImageUpdate();
	void kill();

	std::vector<float>* currentFrameCycle;
	std::vector<float>* walkingFrameIDs;
	std::vector<float>* idleFrameIDs;
	std::vector<float>* attackFrameIDs;
	std::vector<float>* deadFrameIDs;
};



