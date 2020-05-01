#include "g_Door.h"

void g_Door::Open()
{
	if (w_verts[0][0] == w_verts[1][0])
	{
		if (this->opening && w_verts[1][2] < w_verts[0][2])
		{
			setVerts(w_verts[0][0], w_verts[0][1], w_verts[0][2], w_verts[1][0], w_verts[1][1], w_verts[1][2] + openSpeed, w_verts[2][0], w_verts[2][1], w_verts[2][2], w_verts[3][0], w_verts[3][1], w_verts[3][2] + openSpeed);
		}
		else if (this->opening && w_verts[1][2] >= w_verts[0][2])
		{
			this->opening = false;
			this->w_isSolid = false;
		}
	}
	else if (w_verts[0][2] == w_verts[1][2])
	{
		if (this->opening && w_verts[0][0] < w_verts[2][0])
		{
			setVerts(w_verts[0][0], w_verts[0][1], w_verts[0][2], w_verts[1][0] + openSpeed, w_verts[1][1], w_verts[1][2], w_verts[2][0], w_verts[2][1], w_verts[2][2], w_verts[3][0] + openSpeed, w_verts[3][1], w_verts[3][2]);
		}
		else if (this->opening && w_verts[1][0] >= w_verts[0][0])
		{
			this->opening = false;
			this->w_isSolid = false;
		}
	}
}

void g_Door::setOpening(bool x)
{
	this->opening = x;
}

bool g_Door::isOpening()
{
	return opening;
}

bool g_Door::isClosing()
{
	return closing;
}

g_Door::g_Door()
{
	openSpeed = 0.10;
	w_isSolid = true;
}


g_Door::~g_Door()
{
}
