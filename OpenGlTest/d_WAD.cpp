#include "d_WAD.h"
#include <fstream>
#include <sstream>
#include <string.h>
#include "BudgieApp.h"

d_WAD::d_WAD()
{
	this->d_rootWall = new g_Wall();
	this->walls = new std::vector<g_Wall*>();
	this->roofs = new std::vector<g_Roof*>();
	this->floors = new std::vector<g_floor*>();
	this->enemies = new std::vector<e_EnemyBase*>();
	playerStart = new glm::vec3();
	d_wallCount = 0;
}


d_WAD::~d_WAD()
{
}

std::vector<float> d_WAD::stringToVector(std::string x)
{
	std::vector<float> vect;

	std::stringstream ss(x);

	float i;

	while (ss >> i)
	{
		vect.push_back(i);

		if (ss.peek() == ',')
			ss.ignore();
	}

	return vect;
}

std::vector<g_Wall*>* d_WAD::dumpWalls()
{
	return walls;
}
std::vector<g_Roof*>* d_WAD::dumpRoofs()
{
	return roofs;
}
std::vector<g_floor*>* d_WAD::dumpFloors()
{
	return floors;
}

bool d_WAD::ReadWAD(std::string fileName)
{	
	std::cout << std::endl << std::endl << "READ WAD BEGIN..." << std::endl;
	std::ifstream d_inFile;
	d_inFile.open(fileName, std::ios::in);
	std::string currentLine = "";

	while (std::getline(d_inFile, currentLine))
	{
		if (currentLine[0] == 'w' || currentLine[0] == 'p' && currentLine[1] != 's')
		{
			char mode = currentLine[0];
			currentLine.erase(0, 1);
			std::vector<float> vertsString = this->stringToVector(currentLine);
			g_Wall* newWall = new g_Wall();
			newWall->w_isDoor = false;
			newWall->setVerts(vertsString[0], vertsString[1], vertsString[2], vertsString[3], vertsString[4], vertsString[5], vertsString[6], vertsString[7], vertsString[8], vertsString[9], vertsString[10], vertsString[11]);
			if (mode == 'w')
			{
				newWall->w_isSolid = true;
			}
			if (mode == 'p')
			{
				newWall->w_isSolid = false;
			}
			walls->push_back(newWall);
			d_wallCount++;
			std::cout << std::endl << "Reading Wall: " << d_wallCount << " - data: " << currentLine;
		}
		if (currentLine[0] == 'd')
		{
			currentLine.erase(0, 1);
			std::vector<float> vertsString = this->stringToVector(currentLine);
			g_Door* newDoor = new g_Door();
			newDoor->w_isDoor = true;
			newDoor->setVerts(vertsString[0], vertsString[1], vertsString[2], vertsString[3], vertsString[4], vertsString[5], vertsString[6], vertsString[7], vertsString[8], vertsString[9], vertsString[10], vertsString[11]);

			walls->push_back(newDoor);
			d_wallCount++;
			std::cout << std::endl << "Reading Door: " << d_wallCount << " - data: " << currentLine;
		}
		if (currentLine[0] == 'p' && currentLine[1] == 's')
		{
			currentLine.erase(0, 2);
			std::vector<float> vertsString = this->stringToVector(currentLine);
			playerStart->x = vertsString[0];
			playerStart->y = vertsString[1];
			playerStart->z = vertsString[2];
			std::cout << std::endl << "Player Start = " << playerStart->x << "," << playerStart->y;
	}
		if (currentLine[0] == 'e' && currentLine[1] == 's')
		{
			currentLine.erase(0, 2);
			char temp = currentLine[0];
			std::string enemyName;
			switch (temp)
			{
			case '1':
				enemyName = "soldier";
				break;
			}
			currentLine.erase(0, 1);
			std::vector<float> vertsString = this->stringToVector(currentLine);
			glm::vec3* start = new glm::vec3();
			start->x = vertsString[0];
			start->y = vertsString[1];
			start->z = vertsString[2];
			
			renderer->actorMan->GenerateEnemy(enemyName, start);
			std::cout << std::endl << "Reading Enemy - data: " << currentLine;
		}
		if (currentLine[0] == 'f')
		{
			currentLine.erase(0, 1);
			std::vector<float> vertsString = this->stringToVector(currentLine);
			g_floor* newFloor = new g_floor();
			newFloor->setVerts(vertsString[0], vertsString[1], vertsString[2], vertsString[3], vertsString[4], vertsString[5], vertsString[6], vertsString[7], vertsString[8], vertsString[9], vertsString[10], vertsString[11]);
			floors->push_back(newFloor);
			d_floorCount++;
			std::cout << std::endl << "Reading Floor: " << d_floorCount << " - data: " << currentLine;
		}
		if (currentLine[0] == 'r')
		{
			currentLine.erase(0, 1);
			std::vector<float> vertsString = this->stringToVector(currentLine);
			g_Roof* newRoof = new g_Roof();
			newRoof->setVerts(vertsString[0], vertsString[1], vertsString[2], vertsString[3], vertsString[4], vertsString[5], vertsString[6], vertsString[7], vertsString[8], vertsString[9], vertsString[10], vertsString[11]);
			roofs->push_back(newRoof);
			d_roofCount++;
			std::cout << std::endl << "Reading Roof: " << d_roofCount << " - data: " << currentLine;
		}
	}

	std::cout << std::endl << std::endl << "WAD READ SUCCESS. " << std::endl << "MAP WALL COUNT: " << walls->size() << std::endl << std::endl;

	return true;
}