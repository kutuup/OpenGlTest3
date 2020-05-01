#include "g_Wall.h"
#include "BudgieApp.h"

void g_Wall::Open()
{
	std::cout << std::endl << "Why are you trying to open a wall?";
}

void g_Wall::setOpening(bool x)
{
	
}

g_Wall::g_Wall()
{
	this->w_hasVerts = false;
	this->w_isSolid = true;
}


g_Wall::~g_Wall()
{
}

void g_Wall::setVerts(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
	this->w_verts[0][0] = x1;
	this->w_verts[0][1] = y1;
	this->w_verts[0][2] = z1;
	this->w_verts[1][0] = x2;
	this->w_verts[1][1] = y2;
	this->w_verts[1][2] = z2;
	this->w_verts[2][0] = x3;
	this->w_verts[2][1] = y3;
	this->w_verts[2][2] = z3;
	this->w_verts[3][0] = x4;
	this->w_verts[3][1] = y4;
	this->w_verts[3][2] = z4;
	this->startXY[0] = x1;
	this->startXY[1] = z1;
	this->endXY[0] = x2;
	this->endXY[1] = z2;
	this->w_next = new g_Wall();
	this->w_hasVerts = true;
}

std::vector<float> g_Wall::getVerts1()
{
	std::vector<float> ret = { w_verts[0][0], w_verts[0][1], w_verts[0][2] };
	return ret;
}

std::vector<float> g_Wall::getVerts2()
{
	std::vector<float> ret = { w_verts[1][0], w_verts[1][1], w_verts[1][2] };
	return ret;
}

std::vector<float> g_Wall::getVerts3()
{
	std::vector<float> ret = { w_verts[2][0], w_verts[2][1], w_verts[2][2] };
	return ret;
}

std::vector<float> g_Wall::getVerts4()
{
	std::vector<float> ret = { w_verts[3][0], w_verts[3][1], w_verts[3][2] };
	return ret;
}

