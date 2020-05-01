#pragma once
//#include <glm\glm.hpp>

#include "BudgieApp.h"

class Rectangle;
class Point;
class Line;

class p_BoxCollider 
{
public:
	float diameter;

	p_BoxCollider();
	p_BoxCollider(glm::vec3* c, float d, bool t);
	~p_BoxCollider();
	bool tracking;
	glm::vec3* center;

	bool Intersects(double rectangleMinX,
		double rectangleMinY,
		double rectangleMaxX,
		double rectangleMaxY,
		double p1X,
		double p1Y,
		double p2X,
		double p2Y);
};

class Point
{
public: float x;
		float y;
};

class Line
{
public: float XMin;
		float XMax;

		float YMin;
		float YMax;

		Point start;
		Point end;

		Line(Point a, Point b)
		{
			start = a;
			end = b;
			if (a.x < b.x)
			{
				XMin = a.x;
			}
			else
			{
				XMin = b.x;
			}

			if (a.x > b.x)
			{
				XMax = a.x;
			}
			else
			{
				XMax = b.x;
			}

			if (a.y < b.y)
			{
				YMin = a.y;
			}
			else
			{
				YMin = b.y;
			}

			if (a.y > b.y)
			{
				YMax = a.y;
			}
			else
			{
				YMax = b.y;
			}
		}

		float calculateLineSlope(Point a, Point b)
		{
			float m = (b.y - a.y) / (b.x - a.x);
			return m;
		}

		float CalculateYForX(float x, Line* l)
		{
			float slope = calculateLineSlope(l->start, l->end);
			float y = l->start.y + (slope * x);
			return y;
		}
};