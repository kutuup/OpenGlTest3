#pragma once
#include <string>
#include "g_Wall.h"
#include "g_floor.h"
#include "g_Roof.h"
#include "g_Door.h"
#include "r_Draw.h"
//#include "g_floor.h"
//#include "g_Roof.h"
//#include "Math.h"
//#include <vector>
//#include "glm\glm.hpp"*/

#include "BudgieApp.h"

class g_Wall;
class g_floor;
class g_Roof;

class d_WAD
{
private:

	int d_wallCount;
	int d_floorCount;
	int d_roofCount;

	g_Wall* d_rootWall;
	g_floor* d_rootFloor;
	g_Roof* d_rootRoof;


public:
	d_WAD();
	~d_WAD();
	std::vector<g_Wall*>* d_WAD::dumpWalls();
	std::vector<g_Roof*>* d_WAD::dumpRoofs();
	std::vector<g_floor*>* d_WAD::dumpFloors();
	std::vector<g_Wall*>* d_WAD::walls;
	std::vector<g_Roof*>* d_WAD::roofs;
	std::vector<g_floor*>* d_WAD::floors;
	std::vector<e_EnemyBase*>* d_WAD::enemies;
	bool d_WAD::ReadWAD(std::string fileName);
	std::vector<float> d_WAD::stringToVector(std::string x);
	glm::vec3* d_WAD::playerStart;

	r_Draw* renderer;
};

