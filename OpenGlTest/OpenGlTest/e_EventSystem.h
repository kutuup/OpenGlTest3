#pragma once

//#include "GLFW\glfw3.h"

#include "d_Player.h" 
#include "g_UIElement.h"
#include "g_Wall.h"
#include "g_floor.h"
#include "g_Door.h"
#include "Camera.h"
#include "a_Audio.h"

#include "BudgieApp.h"
#include "ActorManager.h"



static class e_EventSystem
{
public:
	e_EventSystem();
	e_EventSystem(d_Player*);
	e_EventSystem(d_Player*, Camera*);
	~e_EventSystem();

	static void e_EventSystem::ProcessEvents();
	static void e_EventSystem::processKeyBuffer();
	static void e_EventSystem::registerKeyEventHandler(GLFWwindow* window);
	static void e_EventSystem::registerMouseEventHandler(GLFWwindow* window);
	static void e_EventSystem::processKeys(GLFWwindow*, int, int, int, int);
	static void e_EventSystem::processCursor(GLFWwindow*, double, double);
	static bool e_EventSystem::checkGrounded(d_Player*);
	static bool e_EventSystem::checkGrounded(e_EnemyBase *);
	static bool e_EventSystem::tryMovement(d_Player*, glm::vec3*, glm::vec3, char key);
	static bool e_EventSystem::tryMovement(e_EnemyBase * e, glm::vec3 * wishDir);
	static void e_EventSystem::tryDoorOpen(d_Player*, glm::vec3*);
	static void e_EventSystem::Update();
	static void e_EventSystem::InterimUpdate();
	static void LowPriorityUpdate();
	static void e_EventSystem::UpdateWalls();
	static void e_EventSystem::UpdateUI();
	static void e_EventSystem::UpdatePhysics();
	static void e_EventSystem::UpdateEnemies();
	static glm::vec3 e_EventSystem::calculateWishDir(float r);
	static bool traceEnemyVision(e_EnemyBase*);
	static e_EnemyBase* traceBullet();
	static bool e_EventSystem::traceEnemyHasShot(e_EnemyBase* en);
	static std::vector<g_floor*>*e_EventSystem::floors;
	static std::vector<g_Wall*>*e_EventSystem::walls;
	static std::vector<g_UIElement*>*e_EventSystem::uiElements;
	static bool e_EventSystem::keys[];
	static d_Player* player;
	static ActorManager* actorMan;
	static r_Draw* renderer;
	static a_Audio* audio;
	static Camera* cam;
	static double lastMouseX;
	static double lastMouseY;
	static bool mouseRotEnabled;
	static glm::vec3 wishDir;
	static bool e_EventSystem::fireHeld;

};

