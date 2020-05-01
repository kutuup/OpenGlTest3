#pragma once
#include "BudgieApp.h"
#include <vector>
class g_UIElement
{
public:

	std::vector < std::vector<float>>* rect;
	
	GLuint* image;

	void setRect(std::vector<float> tl, std::vector<float> tr, std::vector<float> bl, std::vector<float> br);
	void setImage(GLuint*);
	g_UIElement();
	~g_UIElement();
};

