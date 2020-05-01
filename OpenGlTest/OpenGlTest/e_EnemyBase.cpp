#include "e_EnemyBase.h"



e_EnemyBase::e_EnemyBase()
{
	rect = new std::vector<std::vector<float>>();
	imgLib = new std::vector<GLuint*>();

	attachedAgent = new AIAgent();

	pos = new glm::vec3();
	normalDir = new glm::vec3();
	facing = new glm::vec3();

	awake = false;
	state = budgie::idle;
}

e_EnemyBase::e_EnemyBase(glm::vec3 * pos, glm::vec3 * facing, int  health, float  width, float  height)
{
	dead = false;
	rect = new std::vector<std::vector<float>>();
	this->imgLib = new std::vector<GLuint*>();

	this->physics = new PhysicsEffector();
	this->physics->attachedEnemy = this;
	this->physics->gravityScale = 0.3;

	attachedAgent = new AIAgent();
	attachedAgent->wishDir = new glm::vec3();
	attachedAgent->moveSpeed = 0.5;
	this->health = health;
	this->frameUpdateRate = 120;
	this->pos = pos;
	normalDir = new glm::vec3();
	this->facing = facing;
	this->currImg = new GLuint();

	this->width = width;
	this->height = height;

	awake = false;
	state = budgie::idle;

	//this->pos->y -= 3.5f;

	std::vector<float> v1;
	v1.push_back(pos->x - width);
	v1.push_back(pos->y + height);
	v1.push_back(pos->z);

	std::vector<float> v2;
	v2.push_back(pos->x + width);
	v2.push_back(pos->y + height);
	v2.push_back(pos->z);

	std::vector<float> v3;
	v3.push_back(pos->x - width);
	v3.push_back(pos->y - height);
	v3.push_back(pos->z);

	std::vector<float> v4;
	v4.push_back(pos->x + width);
	v4.push_back(pos->y - height);
	v4.push_back(pos->z);

	rect->push_back(v1);
	rect->push_back(v2);
	rect->push_back(v3);
	rect->push_back(v4);
	
	col = new p_BoxCollider(pos, 5, true);

	idleFrameIDs = new std::vector<float>();
	idleFrameIDs->push_back(4);
	walkingFrameIDs = new std::vector<float>();
	walkingFrameIDs->push_back(0);
	walkingFrameIDs->push_back(1);
	walkingFrameIDs->push_back(2);
	walkingFrameIDs->push_back(3);
	attackFrameIDs = new std::vector<float>();
	attackFrameIDs->push_back(10);
	attackFrameIDs->push_back(11);
	attackFrameIDs->push_back(12);
	deadFrameIDs = new std::vector<float>();
	deadFrameIDs->push_back(4);
	deadFrameIDs->push_back(5);
	deadFrameIDs->push_back(6);
	deadFrameIDs->push_back(7);
	deadFrameIDs->push_back(8);
	currentFrameCycle = new std::vector<float>();




	msAtLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());

	attachedAgent->changeDir();
	//attachedAgent->setInitialDir();
	
}


e_EnemyBase::~e_EnemyBase()
{
}

void e_EnemyBase::updateColliders()
{
	recenterCollider(col);
}

void e_EnemyBase::recenterCollider(p_BoxCollider * c)
{
	c->center = pos;
}

void e_EnemyBase::updateRect()
{
	//rect->clear();
	std::vector<float> v1;
	v1.push_back(pos->x - width);
	v1.push_back(pos->y + height);
	v1.push_back(pos->z);

	std::vector<float> v2;
	v2.push_back(pos->x + width);
	v2.push_back(pos->y + height);
	v2.push_back(pos->z);

	std::vector<float> v3;
	v3.push_back(pos->x - width);
	v3.push_back(pos->y - height);
	v3.push_back(pos->z);

	std::vector<float> v4;
	v4.push_back(pos->x + width);
	v4.push_back(pos->y - height);
	v4.push_back(pos->z);



	rect->at(0) = v1;
	rect->at(1) = v2;
	rect->at(2) = v3;
	rect->at(3) = v4;
}

void e_EnemyBase::checkImageUpdate()
{
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
	if ((ms.count() - msAtLastUpdate.count() > frameUpdateRate))
	{
		if (!dead)
		{
			if (currentFrameID == currentFrameCycle->size() - 1)
			{
				currentFrameID = 0;
				currImg = imgLib->at(currentFrameCycle->at(currentFrameID));
			}
			else if (currentFrameID < currentFrameCycle->size())
			{
				
				currImg = imgLib->at(currentFrameCycle->at(currentFrameID));
				currentFrameID++;
			}
		}
		else if (dead)
		{
			if (currentFrameID == currentFrameCycle->size() - 1)
			{
				currentFrameID = currentFrameCycle->size() - 1;
				currImg = imgLib->at(currentFrameCycle->at(currentFrameID));
			}
			else if (currentFrameID < currentFrameCycle->size())
			{
				currImg = imgLib->at(currentFrameCycle->at(currentFrameID));
				currentFrameID++;
				
			}
		}
		msAtLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());
	}
}

void e_EnemyBase::kill()
{
	dead = true;
	this->currentFrameID = 0;
	this->currentFrameCycle = deadFrameIDs;
	//this->col->diameter = 0;
	//this->col->center->x = 0;
	//this->col->center->z = 0;
}
