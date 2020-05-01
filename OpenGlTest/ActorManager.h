#pragma once
#include "BudgieApp.h"
#include "e_EnemyBase.h"
#include "e_Soldier.h"
#include "d_Player.h"
#include "d_WAD.h"
#include <string.h>
//#include <vector>


class ActorManager
{
public:

	d_WAD* wadStream;

	std::vector<d_Player*>* activeActors;
	std::vector<d_Player*>* inactiveActors;

	std::vector<e_EnemyBase*>* activeEnemies;
	std::vector<e_EnemyBase*>* inactiveEnemies;

	void GenerateEnemy(std::string, glm::vec3* pos);

	ActorManager();
	~ActorManager();
};

