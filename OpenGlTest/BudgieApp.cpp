#include "BudgieApp.h"
#include "e_EventSystem.h"
#include <iostream>



BudgieEngine::BudgieEngine()
{
	this->masterTimer = new tm();
	time_t* secs = new time_t();
	time(secs);
	localtime_s(masterTimer, secs);

	updateFrequency = 30;
	lowPriorityUpdateFrequency = 4;
	lowPriorityUpdateFrameCounter = 0;

	msAtLastUpdate = new std::chrono::milliseconds();

	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
	*msAtLastUpdate = ms;

	startTime = masterTimer;
	std::cout << "BUDGIE ENGINE LAUNCH TIME: " << startTime->tm_hour << ":" << startTime->tm_min << ":" << startTime->tm_sec << ":" << ms.count() << std::endl;
	startUpActive = true;
	interimUpdateDue = true;
}


BudgieEngine::~BudgieEngine()
{
}

void BudgieEngine::checkUpdate()
{
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
	if (startUpActive)
	{
		std::cout << std::endl << "Update Loop Begin..." << std::endl;
		std::cout << "Startup Time (ms): ";
		std::cout <<(ms.count() - msAtLastUpdate->count()) << std::endl;
		startUpActive = false;
	}

	
	if(ms.count() - msAtLastUpdate->count() > updateFrequency)
	{ 
		//std::cout << std::endl << "TIME TO UPDATE! - " << msAtLastUpdate->count();
		*msAtLastUpdate = ms;
		be_e_EventSystem->Update();
		interimUpdateDue = true;

		lowPriorityUpdateFrameCounter++;
		if (lowPriorityUpdateFrameCounter == lowPriorityUpdateFrequency)
		{
			lowPriorityUpdateFrameCounter = 0;
			be_e_EventSystem->LowPriorityUpdate();;
		}
	}

	else if (ms.count() - msAtLastUpdate->count() > updateFrequency / 2 && interimUpdateDue)
	{
		//std::cout << std::endl << "TIME TO UPDATE! - " << msAtLastUpdate->count();
		be_e_EventSystem->InterimUpdate();
		interimUpdateDue = false;
	}

}
