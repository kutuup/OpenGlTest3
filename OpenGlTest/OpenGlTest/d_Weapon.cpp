#include "d_Weapon.h"
#include "e_EventSystem.h"


d_Weapon::d_Weapon()
{
	frameIndex = 0;
	frameUpdateRate = 120;
	frames = new std::vector<GLuint*>();
	msAtLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
	
}


d_Weapon::~d_Weapon()
{
}

void d_Weapon::Fire()
{
	if (!firing)
	{
		firing = true;
		msAtLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());
		frameIndex = 1;
	}
}

void d_Weapon::checkUpdate()
{
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
	if ((ms.count() - msAtLastUpdate.count() > frameUpdateRate) && firing)
	{

		if (frameIndex == fireFrame)
		{
			e_EnemyBase* e = eventSystem->traceBullet();
			if (e != NULL)
			{
				e->health -= damage;
				if (e->health <= 0)
				{
					e->kill();
				}
			}
		}
		if (frameIndex == frames->size())
		{
			frameIndex = 1;
			currFrame = frames->at(frameIndex);
			firing = false;
		}
		else if (frameIndex < frames->size())
		{
			frameIndex++;
			currFrame = frames->at(frameIndex -1);
		}
		msAtLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());
	}
	if (!firing)
	{
		currFrame = frames->at(0);
	}
}
