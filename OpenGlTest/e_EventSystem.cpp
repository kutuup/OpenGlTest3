#pragma once

#include "e_EventSystem.h"
#include "BudgieApp.h"
#include "glm\glm.hpp"
#include <vector>

ActorManager* e_EventSystem::actorMan;
r_Draw* e_EventSystem::renderer;
d_Player* e_EventSystem::player;
a_Audio* e_EventSystem::audio;
Camera* e_EventSystem::cam;
double e_EventSystem::lastMouseX;
double e_EventSystem::lastMouseY;
glm::vec3 e_EventSystem::wishDir;
std::vector<g_Wall*>* e_EventSystem::walls;
std::vector<g_floor*>* e_EventSystem::floors;
std::vector<g_UIElement*>* e_EventSystem::uiElements;
bool e_EventSystem::keys[349];
bool e_EventSystem::fireHeld;

bool e_EventSystem::mouseRotEnabled;
Math math;

struct Point2D
{
	int x;
	int y;
};


//WHAT FUCKING SORCERY IS THIS???
int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy)
{
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((verty[i]>testy) != (verty[j]>testy)) &&
			(testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
			c = !c;
	}
	return c;
}

void e_EventSystem::UpdateWalls()
{
	for (int count = 0; count < walls->size(); count++)
	{
		if (walls->at(count)->opening)
			walls->at(count)->Open();
	}
}



// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(glm::vec3 p, glm::vec3 q, glm::vec3 r)
{
	if (q.x <= glm::max(p.x, r.x) && q.x >= glm::min(p.x, r.x) &&
		q.y <= glm::max(p.y, r.y) && q.y >= glm::min(p.y, r.y))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(glm::vec3 p, glm::vec3 q, glm::vec3 r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
	// for details of below formula. 
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(glm::vec3 p1, glm::vec3 q1, glm::vec3 p2, glm::vec3 q2)
{
	glm::vec3 p1Corr(p1.x, p1.z, p1.y);
	glm::vec3 q1Corr(q1.x, q1.z, q1.y);
	// Find the four orientations needed for general and 
	// special cases 
	int o1 = orientation(p1Corr, q1Corr, p2);
	int o2 = orientation(p1Corr, q1Corr, q2);
	int o3 = orientation(p2, q2, p1Corr);
	int o4 = orientation(p2, q2, q1Corr);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1Corr, p2, q1Corr)) return true;

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1Corr, q2, q1Corr)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1Corr, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1Corr, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}

bool pointWithinCircle(glm::vec3 p, glm::vec3 c, float r)
{
	float dist;
	dist = glm::distance(p, c);
	if (dist < r)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ccw(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
	return (C.y - A.z) * (B.x - A.x) > (B.z - A.z) * (C.x - A.x);

}
		// Return true if line segments AB and CD intersect
bool linesIntersect(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D) {
	return ccw(A, C, D) != ccw(B, C, D) && ccw(A, B, C) != ccw(A, B, D);
}
		


void e_EventSystem::UpdatePhysics()
{
	player->grounded = checkGrounded(player);
	player->pEffector->updateAttachedObject();

	for (int count = 0; count < actorMan->activeEnemies->size(); count++)
	{
		e_EnemyBase* e = actorMan->activeEnemies->at(count);
		if (!e->dead)
		{
			e->grounded = checkGrounded(e);
			e->physics->updateAttachedEnemy();
		}
	}
}

void e_EventSystem::UpdateEnemies()
{
	for (int count = 0; count < actorMan->activeEnemies->size(); count++)
	{
		
		e_EnemyBase* e = actorMan->activeEnemies->at(count);

		if (e->state == budgie::patrol)
		{
			if (!e->dead)
			{
				tryMovement(e, e->attachedAgent->wishDir);
				//bool playerSeen = traceEnemyHasShot(e); FUNCTION SUCKS AT THE MOMENT
			}
		}
		if (e->state == budgie::idle)
		{
			if (std::abs(player->Position->x - e->pos->x) < 20 && std::abs(player->Position->z - e->pos->z) < 20)
			{
				bool playerSeen = traceEnemyVision(e);
				if (playerSeen)
				{
					std::cout << std::endl << "PLAYER SEEN";
					e->state = budgie::patrol;
				}
			}
		}
		e->checkImageUpdate();
	}
}

void e_EventSystem::UpdateUI()
{
	player->currWeapon->checkUpdate();
	uiElements->at(1)->image = player->currWeapon->currFrame;
}

void e_EventSystem::Update()
{

	
	audio->Play();
	processKeyBuffer();
	UpdateWalls();
	UpdateUI();
	UpdateEnemies();
	UpdatePhysics();


}

void e_EventSystem::InterimUpdate()
{
	renderer->renderScene();

}

void e_EventSystem::LowPriorityUpdate()
{

}

e_EventSystem::e_EventSystem()
{

}

e_EventSystem::e_EventSystem(d_Player* player)
{
	player = player;
	lastMouseX = 0;
	lastMouseY = 0;
	mouseRotEnabled = false;
	wishDir.x = 0;
	wishDir.z = 1;
	walls = new std::vector<g_Wall*>();
	floors = new std::vector<g_floor*>();
	uiElements = new std::vector<g_UIElement*>();
	fireHeld = false;
}

e_EventSystem::e_EventSystem(d_Player* player, Camera* c)
{
	this->player = player;
	cam = c;
	lastMouseX = 0;
	lastMouseY = 0;
	mouseRotEnabled = false;
	walls = new std::vector<g_Wall*>();
	floors = new std::vector<g_floor*>();
	uiElements = new std::vector<g_UIElement*>();
	fireHeld = false;
}

e_EventSystem::~e_EventSystem()
{
}

void e_EventSystem::ProcessEvents()
{
	glfwPollEvents();
}

void e_EventSystem::registerKeyEventHandler(GLFWwindow* window)
{
	glfwSetKeyCallback(window, processKeys);
}

void e_EventSystem::registerMouseEventHandler(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, processCursor);
}

void e_EventSystem::processCursor(GLFWwindow* window, double x, double y)
{
	if (mouseRotEnabled)
	{
		if (lastMouseX == 0 && lastMouseY == 0)
		{
			lastMouseX = x;
			lastMouseY = y;
		}
		else
		{
			if (x > lastMouseX)
			{
				cam->Rotation->x += player->turnSpeed;

			}
			else if (x < lastMouseX)
			{
				cam->Rotation->x -= player->turnSpeed;

			}

		}
		lastMouseX = x;
		lastMouseY = y;
	}
}

double deg2rad(double degrees) {
	return degrees * 4.0 * atan(1.0) / 180.0;
}

glm::vec3 e_EventSystem::calculateWishDir(float r)
{
	glm::vec3 ret;

	double theta = deg2rad(r);

	double cs = cos(theta);
	double sn = sin(theta);

	double px = wishDir.x * cs - wishDir.y * sn;
	double py = wishDir.x * sn + wishDir.y * cs;

	ret.x = px;
	ret.z = py;

	return ret;
}

bool e_EventSystem::traceEnemyVision(e_EnemyBase* e)
{
	if (pointWithinCircle(*player->Position, *e->pos, 20))
	{
		return true;
	}

	return false;
}

bool e_EventSystem::traceEnemyHasShot(e_EnemyBase* en)
{
	bool hit = false;
	bool hitWall = false;
	
	glm::vec3* col = new glm::vec3();
	p_BoxCollider* temp = new p_BoxCollider();
	temp->center = new glm::vec3();
	temp->diameter = 1;
	temp->center->x = en->pos->x;
	temp->center->y = en->pos->y;
	temp->center->z = en->pos->z + 2.5;

	int cycles = 0;

	while (!hitWall && !hit)
	{
		cycles++;
		temp->center->x += en->attachedAgent->wishDir->x;
		temp->center->z += en->attachedAgent->wishDir->z;

		for (int count = 0; count < walls->size(); count++)
		{
			if (temp->center->y > walls->at(count)->getVerts1()[1] && temp->center->y < walls->at(count)->getVerts3()[1] && walls->at(count)->w_isSolid == true)
			{
				float left = (temp->center->x) - (0.1);
				float right = (temp->center->x) + (0.1);
				float top = (temp->center->z) + (0.1);
				float bottom = (temp->center->z) - (0.1);
				Point start;
				start.x = walls->at(count)->startXY[0];
				start.y = walls->at(count)->startXY[1];
				Point end;
				end.x = walls->at(count)->endXY[0];
				end.y = walls->at(count)->endXY[1];
				if (temp->Intersects(left, bottom, right, top, start.x, start.y, end.x, end.y))
				{
					hitWall = true;
				}
			}


		}
		if (!hitWall)
		{


				float left = (temp->center->x) - (2);
				float right = (temp->center->x) + (2);
				float top = (temp->center->z) + (2);
				float bottom = (temp->center->z) - (2);

				p_BoxCollider* c = player->colliders->at(0);

				float xcoords[4];
				float ycoords[4];

				xcoords[0] = temp->center->x - 2;
				ycoords[0] = temp->center->z - 2;
				xcoords[1] = temp->center->x - 2;
				ycoords[1] = temp->center->z + 2;
				xcoords[2] = temp->center->x + 2;
				ycoords[2] = temp->center->z - 2;
				xcoords[3] = temp->center->x + 2;
				ycoords[3] = temp->center->z + 2;

				if (pnpoly(4 ,xcoords , ycoords, player->Position->x, player->Position->z) && player->Position->y < temp->center->y + 5 && player->Position->y > temp->center->y - 5)
				{
					hit = true;
				}

			
		}
		if (hitWall && !hit)
		{
			//std::cout << std::endl << "HIT WALL AFTER " << cycles << " CYCLES.";
			return false;
		}
		else if (hit && !hitWall)
		{
			std::cout << std::endl << "PLAYER IN SHOT RANGE";
			en->attachedAgent->targetPos = player->Position;
			return true;

		}
		else if (cycles > 100)
		{
			//std::cout << std::endl << "NO HIT AFTER MAX CYCLES";
			return false;
		}
	}
}

e_EnemyBase* e_EventSystem::traceBullet()
{
	e_EnemyBase* ret = NULL;
	bool hitWall = false;
	bool hitEnemy = false;
	glm::vec3* col = new glm::vec3();
	p_BoxCollider* temp = new p_BoxCollider();
	temp->center = new glm::vec3();
	temp->diameter = 1;
	temp->center->x = player->Position->x;
	temp->center->y = player->Position->y;
	temp->center->z = player->Position->z + 2.5;

	int cycles = 0;

	while (!hitWall && !hitEnemy)
	{
		cycles++;
		temp->center->x -= wishDir.x;
		temp->center->z -= wishDir.z;

		for (int count = 0; count < walls->size(); count++)
		{
			if (temp->center->y > walls->at(count)->getVerts1()[1] && temp->center->y < walls->at(count)->getVerts3()[1] && walls->at(count)->w_isSolid == true)
			{
				float left = (temp->center->x) - (0.1);
				float right = (temp->center->x) + (0.1);
				float top = (temp->center->z) + (0.1);
				float bottom = (temp->center->z) - (0.1);
				Point start;
				start.x = walls->at(count)->startXY[0];
				start.y = walls->at(count)->startXY[1];
				Point end;
				end.x = walls->at(count)->endXY[0];
				end.y = walls->at(count)->endXY[1];
				if (temp->Intersects(left, bottom, right, top, start.x, start.y, end.x, end.y))
				{
					hitWall = true;
				}
			}


		}
		if (!hitWall)
		{
			for (int count = 0; count < actorMan->activeEnemies->size(); count++)
			{

					float left = (temp->center->x) - (2);
					float right = (temp->center->x) + (2);
					float top = (temp->center->z) + (2);
					float bottom = (temp->center->z) - (2);
					Point start;
					p_BoxCollider* c = actorMan->activeEnemies->at(count)->col;
					start.x = c->center->x - (c->diameter / 2);
					start.y = c->center->z - (c->diameter / 2);
					Point end;
					end.x = c->center->x + (c->diameter /2);
					end.y = c->center->z + (c->diameter /2);

					if (temp->Intersects(left, bottom, right, top, start.x, start.y, end.x, end.y) && !actorMan->activeEnemies->at(count)->dead)
					{
						hitEnemy = true;
						actorMan->activeEnemies->at(count)->currImg = actorMan->activeEnemies->at(count)->imgLib->at(budgie::ENEMYDEATHFRAME1);
						ret = actorMan->activeEnemies->at(count);
					}
				
			}
		}
		if (hitWall && !hitEnemy)
		{
			std::cout << std::endl << "HIT WALL AFTER " << cycles << " CYCLES.";
			return ret;
		}
		else if (hitEnemy && !hitWall)
		{
			std::cout << std::endl << "HIT ENEMY";
			return ret;

		}
		else if (cycles > 100)
		{
			std::cout << std::endl << "NO HIT AFTER MAX CYCLES";
			return ret;
		}
	}
	
}


bool e_EventSystem::tryMovement(d_Player* p, glm::vec3* wishDir, glm::vec3 lastPos, char key)
{
	lastPos.x = player->Position->x;
	lastPos.z = player->Position->z;

	if (key == 'W')
	{
		player->Position->z -= wishDir->z;
	}
	else if (key == 'S')
	{
		player->Position->z += wishDir->z;
	}

	player->updateColliders();

	for (int count = 0; count < p->colliders->size(); count++)
	{
		glm::vec3* col;
		for (int count = 0; count < walls->size(); count++)
		{
			g_Wall* w = walls->at(count);
			if (std::abs(w->startXY[0] - player->Position->x) < 50 && std::abs(w->startXY[1] - player->Position->z) < 50)
			{
				col = player->colliders->at(0)->center;
				if (col->y > w->getVerts1()[1] && col->y < w->getVerts3()[1])
				{
					float left = (col->x) - (p->colliders->at(0)->diameter / 4);
					float right = (col->x) + (p->colliders->at(0)->diameter / 4);
					float top = (col->z) + (p->colliders->at(0)->diameter / 4);
					float bottom = (col->z) - (p->colliders->at(0)->diameter / 4);
					Point start;
					start.x = w->startXY[0];
					start.y = w->startXY[1];
					Point end;
					end.x = w->endXY[0];
					end.y = w->endXY[1];
					if (w->w_isSolid == true)
					{
						if (p->colliders->at(0)->Intersects(left, bottom, right, top, start.x, start.y, end.x, end.y))
						{
							glm::vec3 normal;
							normal.z = (end.x - start.x);
							normal.x = -(end.y - start.y);
							normal = glm::normalize(normal);

							glm::vec3 undesiredMotion = normal * (glm::dot(*wishDir, normal));


							if (key == 'W')
							{
								player->Position->z = lastPos.z;
							}
							else if (key == 'S')
							{
								player->Position->z = lastPos.z;
							}
							player->updateColliders();
						}
					}
				}
			}
		}

		if (key == 'W')
		{
			player->Position->x -= wishDir->x;
		}
		else if (key == 'S')
		{
			player->Position->x += wishDir->x;
		}

		player->updateColliders();

		for (int count = 0; count < p->colliders->size(); count++)
		{

			glm::vec3* col;
			for (int count = 0; count < walls->size(); count++)
			{
				g_Wall* w = walls->at(count);
				if (std::abs(w->startXY[0] - player->Position->x) < 20 && std::abs(w->startXY[1] - player->Position->z) < 20)
				{
					col = player->colliders->at(0)->center;
					if (col->y > w->getVerts1()[1] && col->y < w->getVerts3()[1])
					{
						float left = (col->x) - (p->colliders->at(0)->diameter / 4);
						float right = (col->x) + (p->colliders->at(0)->diameter / 4);
						float top = (col->z) + (p->colliders->at(0)->diameter / 4);
						float bottom = (col->z) - (p->colliders->at(0)->diameter / 4);
						Point start;
						start.x = w->startXY[0];
						start.y = w->startXY[1];
						Point end;
						end.x = walls->at(count)->endXY[0];
						end.y = walls->at(count)->endXY[1];
						if (w->w_isSolid == true)
						{
							if (p->colliders->at(0)->Intersects(left, bottom, right, top, start.x, start.y, end.x, end.y))
							{
								glm::vec3 normal;
								normal.z = (end.x - start.x);
								normal.x = -(end.y - start.y);
								normal = glm::normalize(normal);

								glm::vec3 undesiredMotion = normal * (glm::dot(*wishDir, normal));

								if (key == 'W')
								{
									player->Position->x = lastPos.x;
								}
								else if (key == 'S')
								{
									player->Position->x = lastPos.x;
								}
								player->updateColliders();
							}
						}
					}
				}
			}
		}
		for (int count = 0; count < actorMan->activeEnemies->size(); count++)
		{
			e_EnemyBase* e = actorMan->activeEnemies->at(count);
			if (std::abs(e->pos->x - player->Position->x) < 3 && std::abs(e->pos->z - player->Position->z) < 3)
			{
				if (!e->dead)
				{
					col = player->colliders->at(0)->center;
					if (col->y > walls->at(count)->getVerts1()[1] && col->y < walls->at(count)->getVerts3()[1])
					{
						float left = (p->colliders->at(0)->center->x) - (p->colliders->at(0)->diameter / 4);
						float right = (p->colliders->at(0)->center->x) + (p->colliders->at(0)->diameter / 4);
						float top = (p->colliders->at(0)->center->z) + (p->colliders->at(0)->diameter / 4);
						float bottom = (p->colliders->at(0)->center->z) - (p->colliders->at(0)->diameter / 4);
						Point start;
						p_BoxCollider* c = e->col;
						start.x = c->center->x - (c->diameter / 2);
						start.y = c->center->z - (c->diameter / 2);
						Point end;
						end.x = c->center->x + (c->diameter / 2);
						end.y = c->center->z + (c->diameter / 2);

						if (p->colliders->at(0)->Intersects(left, bottom, right, top, start.x, start.y, end.x, end.y))
						{
							glm::vec3 normal;
							normal.z = (end.x - start.x);
							normal.x = -(end.y - start.y);
							normal = glm::normalize(normal);

							glm::vec3 undesiredMotion = normal * (glm::dot(*wishDir, normal));

							if (key == 'W')
							{
								player->Position->x = lastPos.x;
								player->Position->z = lastPos.z;
							}
							else if (key == 'S')
							{
								player->Position->x = lastPos.x;
								player->Position->z = lastPos.z;
							}
							player->updateColliders();
							return false;
						}

					}
				}
			}
		}
		return true;
	}
}

bool e_EventSystem::tryMovement(e_EnemyBase* e, glm::vec3* wishDir)
{
	glm::vec3 lastPos;
	lastPos.x = e->pos->x;
	lastPos.z = e->pos->z;

	e->updateColliders();

	glm::vec3 wallStart;
	glm::vec3 wallEnd;

	for (int count = 0; count < walls->size(); count++)
	{
		g_Wall* w = walls->at(count);

		wallStart.x = w->startXY[0];
		wallStart.y = w->startXY[1];
		wallEnd.x = w->endXY[0];
		wallEnd.y = w->endXY[1];

		if (doIntersect(*e->pos - *e->attachedAgent->wishDir * 24.0f, *e->pos + *e->attachedAgent->wishDir * 24.0f, wallStart, wallEnd))
		{
			e->pos->x -= e->attachedAgent->wishDir->x;
			e->pos->z -= e->attachedAgent->wishDir->z;

			e->updateColliders();
			e->updateRect();
			e->attachedAgent->changeDir();
			return false;
		}
	}
	e->pos->z += e->attachedAgent->wishDir->z;
	e->pos->x += e->attachedAgent->wishDir->x;
	
		//glm::vec3* col;
		
		e->updateColliders();
		e->updateRect();
		return true;
	
}




bool e_EventSystem::checkGrounded(d_Player* p)
{
	Point2D* playerPos = new Point2D();

	Point2D* f1 = new Point2D();
	Point2D* f2 = new Point2D();
	Point2D* f3 = new Point2D();
	Point2D* f4 = new Point2D();

	int res = 0;

	glm::vec3 x;
	glm::vec3 y;
	glm::vec3 z;

	playerPos = new Point2D();
	playerPos->x = p->Position->x;
	playerPos->y = p->Position->z;

	f1 = new Point2D();
	f2 = new Point2D();
	f3 = new Point2D();
	f4 = new Point2D();

	std::vector<g_floor*>* iFloors = new std::vector<g_floor*>();

	for (int count = 0; count < floors->size(); count++)
	{
		g_floor* f = floors->at(count);

		float xcoords[4];
		float ycoords[4];

		xcoords[0] = f->getVerts1()[0];
		ycoords[0] = f->getVerts1()[2];
		xcoords[1] = f->getVerts2()[0];
		ycoords[1] = f->getVerts2()[2];
		xcoords[2] = f->getVerts3()[0];
		ycoords[2] = f->getVerts3()[2];
		xcoords[3] = f->getVerts4()[0];
		ycoords[3] = f->getVerts4()[2];


		if (pnpoly(4, xcoords, ycoords, playerPos->x, playerPos->y))
		{
			p->Position->y = f->getVerts1()[1] + 2.5;
			return true;
		}

	}

	return false;
}


bool e_EventSystem::checkGrounded(e_EnemyBase* e)
{
	Point2D* playerPos = new Point2D();

	Point2D* f1 = new Point2D();
	Point2D* f2 = new Point2D();
	Point2D* f3 = new Point2D();
	Point2D* f4 = new Point2D();

	int res = 0;

	glm::vec3 x;
	glm::vec3 y;
	glm::vec3 z;

	playerPos = new Point2D();
	playerPos->x = e->pos->x;
	playerPos->y = e->pos->z;

	f1 = new Point2D();
	f2 = new Point2D();
	f3 = new Point2D();
	f4 = new Point2D();

	std::vector<g_floor*>* iFloors = new std::vector<g_floor*>();

	for (int count = 0; count < floors->size(); count++)
	{
		g_floor* f = floors->at(count);

		float xcoords[4];
		float ycoords[4];

		xcoords[0] = f->getVerts1()[0];
		ycoords[0] = f->getVerts1()[2];
		xcoords[1] = f->getVerts2()[0];
		ycoords[1] = f->getVerts2()[2];
		xcoords[2] = f->getVerts3()[0];
		ycoords[2] = f->getVerts3()[2];
		xcoords[3] = f->getVerts4()[0];
		ycoords[3] = f->getVerts4()[2];


		if (pnpoly(4, xcoords, ycoords, playerPos->x, playerPos->y))
		{
			e->pos->y = f->getVerts1()[1] + 2.5;
			return true;
		}

	}

	return false;
}



void e_EventSystem::tryDoorOpen(d_Player* p, glm::vec3* wishDir)
{
	for (int count = 0; count < p->colliders->size(); count++)
	{
		for (int count = 0; count < walls->size(); count++)
		{
			float left = (p->colliders->at(0)->center->x) - (p->colliders->at(0)->diameter);
			float right = (p->colliders->at(0)->center->x) + (p->colliders->at(0)->diameter);
			float top = (p->colliders->at(0)->center->z) + (p->colliders->at(0)->diameter);
			float bottom = (p->colliders->at(0)->center->z) - (p->colliders->at(0)->diameter);
			Point start;
			start.x = walls->at(count)->startXY[0];
			start.y = walls->at(count)->startXY[1];
			Point end;
			end.x = walls->at(count)->endXY[0];
			end.y = walls->at(count)->endXY[1];
			if (p->colliders->at(0)->Intersects(left, bottom, right, top, start.x, start.y, end.x, end.y))
			{
				walls->at(count)->setOpening(true);
			}
		}
	}
}

void e_EventSystem::processKeyBuffer()
{
	float fraction = player->runSpeed;
	float rotSpeed = player->turnSpeed;

	wishDir.x = 0;
	wishDir.y = 1;
	wishDir = calculateWishDir(cam->Rotation->y);

	glm::vec3* lastPos = new glm::vec3();

	bool fPressed = false;

	for (int count = 0; count < 349; count++)
	{
		if (!keys[70])
		{
			fireHeld = false;
		}
		if (!keys[count])
			continue;

		switch (count) {

		case '1':
			if (player->weapons->at(0) != NULL)
			{
				player->currWeapon = player->weapons->at(0);
			}
			break;
		case '2':
			if (player->weapons->at(1) != NULL)
			{
				player->currWeapon = player->weapons->at(1);
			}
			break;
		case 'R':
			tryDoorOpen(player, &wishDir);

			break;

		case 'A':

			cam->Rotation->y -= rotSpeed * 2;

			break;

		case 'D':

			cam->Rotation->y += rotSpeed * 2;

			break;

		case 'W':

			tryMovement(player, &wishDir, *lastPos, count);
			break;


		case 'S':

			tryMovement(player, &wishDir, *lastPos, count);
			break;

		case 'Q':

			tryMovement(player, &wishDir, *lastPos, count);
			break;

		case 'E':

			tryMovement(player, &wishDir, *lastPos, count);

			break;

		case 'F':
			fPressed = true;
			if (fireHeld == false && !player->currWeapon->repeating)
			{
				fireHeld = true;
				player->currWeapon->Fire();
			}
			else if (player->currWeapon->repeating)
			{
				fireHeld = true;
				player->currWeapon->Fire();
			}

			break;
		case 'M':
			if (!mouseRotEnabled)
			{
				mouseRotEnabled = true;
				std::cout << std::endl << "Mouse Control On";
			}
			break;
		case 'N':
			if (mouseRotEnabled)
			{
				mouseRotEnabled = false;
				std::cout << std::endl << "Mouse Control Off";
			}
			break;
		}

		player->updateColliders();

	}
}

void e_EventSystem::processKeys(GLFWwindow* window, int key, int scancode, int action, int mods ) 
{
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false; 
}
