#pragma once

#include <math.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <chrono>

#include "lib\glew\glew.h"
#include "GLFW\glfw3.h"
#include "lib\freeglut\freeglut.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"


#include <SDL.h>
class ActorManager;
class e_EventSystem;
class r_Draw;
class d_WAD;

class BudgieEngine
{
public:
	ActorManager* be_ActorManager;
	e_EventSystem* be_e_EventSystem;
	r_Draw* be_r_Draw;
	d_WAD* be_d_WAD;
	tm* masterTimer;
	tm* startTime;
	bool startUpActive;
	bool interimUpdateDue;
	int lowPriorityUpdateFrequency;
	int lowPriorityUpdateFrameCounter;
	int updateFrequency;
	std::chrono::milliseconds* msAtLastUpdate;

	void checkUpdate();
	BudgieEngine();
	~BudgieEngine();
};

