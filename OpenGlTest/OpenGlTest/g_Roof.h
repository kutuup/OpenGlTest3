#pragma once

/*#include "lib\glew\glew.h"
//#include "lib\freeglut\freeglut.h"
#include <iostream>*/

#include "BudgieApp.h"


class g_Roof
{
private:
	float r_verts[4][3] = { { 0.0,0.0,0.0 } ,{ 0.0, 0.0, 0.0 } ,{ 0.0, 0.0, 0.0 } ,{ 0.0, 0.0, 0.0 } };
	float r_colour[3] = { 0.0,0.0,0.0 };
	bool r_isSolid;
	g_Roof* r_next;

public:
	g_Roof();
	~g_Roof();
	std::vector<float> getVerts1();
	std::vector<float> getVerts2();
	std::vector<float> getVerts3();
	std::vector<float> getVerts4();
	void setVerts(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
};

