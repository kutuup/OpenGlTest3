#include "g_Roof.h"
#include "BudgieApp.h"


g_Roof::g_Roof()
{
}


g_Roof::~g_Roof()
{
}

void g_Roof::setVerts(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
	this->r_verts[0][0] = x1;
	this->r_verts[0][1] = y1;
	this->r_verts[0][2] = z1;
	this->r_verts[1][0] = x2;
	this->r_verts[1][1] = y2;
	this->r_verts[1][2] = z2;
	this->r_verts[2][0] = x3;
	this->r_verts[2][1] = y3;
	this->r_verts[2][2] = z3;
	this->r_verts[3][0] = x4;
	this->r_verts[3][1] = y4;
	this->r_verts[3][2] = z4;
	this->r_next = new g_Roof();
}

std::vector<float> g_Roof::getVerts1()
{
	std::vector<float> ret = { r_verts[0][0], r_verts[0][1], r_verts[0][2] };
	return ret;
}

std::vector<float> g_Roof::getVerts2()
{
	std::vector<float> ret = { r_verts[1][0], r_verts[1][1], r_verts[1][2] };
	return ret;
}

std::vector<float> g_Roof::getVerts3()
{
	std::vector<float> ret = { r_verts[2][0], r_verts[2][1], r_verts[2][2] };
	return ret;
}

std::vector<float> g_Roof::getVerts4()
{
	std::vector<float> ret = { r_verts[3][0], r_verts[3][1], r_verts[3][2] };
	return ret;
}