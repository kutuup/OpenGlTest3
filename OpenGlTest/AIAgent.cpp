#include "AIAgent.h"
#include <chrono>



void AIAgent::changeDir()
{

	wishDir->x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (moveSpeed * 2))) - moveSpeed;
	wishDir->z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (moveSpeed * 2))) - moveSpeed;
	//wishDir->x *= -1;
	//wishDir->y *= -1;
	wishDir->y = 0;
}

void AIAgent::setInitialDir()
{
	//srand(static_cast <unsigned> (time(NULL)));
	wishDir->x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (moveSpeed * 2))) - moveSpeed;
	wishDir->z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (moveSpeed * 2))) - moveSpeed;
	//wishDir->x *= -1;
	//wishDir->y *= -1;
	wishDir->y = 0;
}

void AIAgent::SeekTarget()
{
}

AIAgent::AIAgent()
{
}


AIAgent::~AIAgent()
{
}
