#pragma once

/*#include "lib\freeglut\freeglut.h"
#include <iostream>
#include <vector>*/

#include "BudgieApp.h"

class g_Wall
{

protected:


	float w_verts[4][3] = { { 0.0,0.0,0.0 } , {0.0, 0.0, 0.0} , { 0.0, 0.0, 0.0 } , { 0.0, 0.0, 0.0 } };
	float w_colour[3] = { 0.0,0.0,0.0 };




public:
	bool w_isSolid;
	bool w_isDoor;
	g_Wall* w_next;
	bool w_hasVerts;
	float startXY[2];
	float endXY[2];
	std::vector<float> getVerts1();
	std::vector<float> getVerts2();
	std::vector<float> getVerts3();
	std::vector<float> getVerts4();
	virtual void Open();
	bool opening;
	bool closing;
	void setVerts(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
	virtual void setOpening(bool x);
	g_Wall();
	~g_Wall();
};

