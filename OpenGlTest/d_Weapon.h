#pragma once
#include "BudgieApp.h"
#include <string.h>
#include <vector>

class d_Weapon
{
public:

	std::string name;
	int id;
	int rateOfFire;
	float damage;
	float spread;
	bool firing;
	bool repeating;
	int fireFrame;
	e_EventSystem* eventSystem;


	int frameIndex;
	std::vector<GLuint*>* frames;
	int frameUpdateRate;
	GLuint* currFrame;

	std::chrono::milliseconds msAtLastUpdate;

	void Fire();
	void checkUpdate();

	d_Weapon();
	~d_Weapon();
};

