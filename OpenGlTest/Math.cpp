#include "Math.h"
#include "BudgieApp.h"


Math::Math()
{
}


Math::~Math()
{
}

glm::vec3 Math::vec3Subtract(glm::vec3* a, glm::vec3* b)
{
	glm::vec3 c;
	c.x = a->x - b->x;
	c.y = a->y - b->y;
	c.z = a->z - b->z;
	return c;
}

int Math::pointInRect(int nvert, float * vertx, float * verty, float testx, float testy)
{
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((verty[i]>testy) != (verty[j]>testy)) &&
			(testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
			c = !c;
	}
	return c;
}

/*vec3::vec3()
{
}

vec3::~vec3()
{

}*/


