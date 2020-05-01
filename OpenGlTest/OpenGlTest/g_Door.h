#pragma once
#include "g_Wall.h"
class g_Door :
	public g_Wall
{
public:
	

	void Open() override;
	void setOpening(bool x) override;

	bool isOpening();
	bool isClosing();

	float openSpeed;

	g_Door();
	~g_Door();

	bool vertical;
private:




};


