
#include "ActorManager.h"
#include "BudgieApp.h"




ActorManager::ActorManager()
{
	activeActors = new std::vector<d_Player*>();
	inactiveActors = new std::vector<d_Player*>();
	activeEnemies = new std::vector<e_EnemyBase*>();
	inactiveEnemies = new std::vector<e_EnemyBase*>();
}


ActorManager::~ActorManager()
{
}

void ActorManager::GenerateEnemy(std::string type, glm::vec3* pos)
{
	if (type == "soldier")
	{

		glm::vec3* newPos = new glm::vec3();
		newPos->x = pos->x;
		newPos->y = pos->y;
		newPos->z = pos->z;
		e_Soldier* s = new e_Soldier(newPos, new glm::vec3(), 100, 2.5f, 2.5f);
		s->attachedAgent->moveSpeed = 0.1f;
		s->imgLib->push_back(wadStream->renderer->texLib->at(15));
		s->imgLib->push_back(wadStream->renderer->texLib->at(16));
		s->imgLib->push_back(wadStream->renderer->texLib->at(17));
		s->imgLib->push_back(wadStream->renderer->texLib->at(18));
		s->imgLib->push_back(wadStream->renderer->texLib->at(19));
		s->imgLib->push_back(wadStream->renderer->texLib->at(20));
		s->imgLib->push_back(wadStream->renderer->texLib->at(21));
		s->imgLib->push_back(wadStream->renderer->texLib->at(22));
		s->imgLib->push_back(wadStream->renderer->texLib->at(23));
		s->currentFrameCycle = s->walkingFrameIDs;
		s->currentFrameID = 0;
		//s->currImg = s->imgLib->at(s->currentFrameCycle->at(s->currentFrameID));
		activeEnemies->push_back(s);
		std::cout << std::endl << "1 Soldier Added.";
	}
}