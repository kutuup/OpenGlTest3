#include "g_floor.h"
#include "BudgieApp.h"


g_floor::g_floor()
{
}


g_floor::~g_floor()
{
}

void g_floor::setVerts(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
	this->f_verts[0][0] = x1;
	this->f_verts[0][1] = y1;
	this->f_verts[0][2] = z1;
	this->f_verts[1][0] = x2;
	this->f_verts[1][1] = y2;
	this->f_verts[1][2] = z2;
	this->f_verts[2][0] = x3;
	this->f_verts[2][1] = y3;
	this->f_verts[2][2] = z3;
	this->f_verts[3][0] = x4;
	this->f_verts[3][1] = y4;
	this->f_verts[3][2] = z4;
	this->f_next = new g_floor();
}

std::vector<float> g_floor::getVerts1()
{
	std::vector<float> ret = { f_verts[0][0], f_verts[0][1], f_verts[0][2] };
	return ret;
}

std::vector<float> g_floor::getVerts2()
{
	std::vector<float> ret = { f_verts[1][0], f_verts[1][1], f_verts[1][2] };
	return ret;
}

std::vector<float> g_floor::getVerts3()
{
	std::vector<float> ret = { f_verts[2][0], f_verts[2][1], f_verts[2][2] };
	return ret;
}

std::vector<float> g_floor::getVerts4()
{
	std::vector<float> ret = { f_verts[3][0], f_verts[3][1], f_verts[3][2] };
	return ret;
}
