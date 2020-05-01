#pragma once

#include "g_Wall.h"

#include "d_Player.h"
#include "e_EventSystem.h"
#include "g_UIElement.h"
#include "BudgieApp.h"
#include "d_WAD.h"
#include "Camera.h"
#include "ActorManager.h"
#include <string.h>


#include <vector>

class g_Wall;
class d_Player;
class Camera;

#include "BudgieApp.h"

class r_Draw
{
public:
	static std::vector<g_Wall*>* mapWalls;
	static std::vector<g_floor*>* mapFloors;
	static std::vector<g_Roof*>* mapRoofs;
	static std::vector<g_UIElement*>* uiElements;
	static std::vector<GLuint*>* texLib;
	static d_Player* localPlayer;
	static Camera* camera;
	static void r_drawWall(g_Wall*);
	static void r_drawFloor(g_floor*);
	static void r_drawRoof(g_Roof*);
	static void r_drawUIElement(g_UIElement*);
	static void r_drawEnemy(e_EnemyBase*);
	static glm::vec3 findQuadNormal(glm::vec3*);
	static g_UIElement* generateUIElement(float, float, float, float, float, float, float, float, float, float, float, float, GLuint*);
	static GLFWwindow* mainWindow;
	static e_EventSystem* eventSystem;
	static ActorManager* actorMan;

	static int* scrWidth;
	static int* scrHeight;

	static float rot;
	r_Draw();
	~r_Draw();

	static void renderScene();
	static void initGLFW();
	static void LoadTextures();
	static void LoadTexture(std::string* path);
	static void LoadUIElements();

private:
	
};

