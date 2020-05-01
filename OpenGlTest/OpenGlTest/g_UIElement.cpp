#include "g_UIElement.h"



g_UIElement::g_UIElement()
{
	this->rect = new std::vector<std::vector<float>>();
}

void g_UIElement::setImage(GLuint* img)
{
	this->image = img;
}

void g_UIElement::setRect(std::vector<float> tl, std::vector<float> tr, std::vector<float> bl, std::vector<float> br)
{
	rect->push_back(tl);
	rect->push_back(tr);
	rect->push_back(br);
	rect->push_back(bl);
}

g_UIElement::~g_UIElement()
{
}
