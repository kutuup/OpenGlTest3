#include "r_Draw.h"
#include <time.h>
#include "BudgieApp.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float r_Draw::rot = 0.0f;
d_Player* r_Draw::localPlayer;

Camera* r_Draw::camera;
e_EventSystem* r_Draw::eventSystem;
ActorManager* r_Draw::actorMan;
int* r_Draw::scrWidth;
int* r_Draw::scrHeight;
std::vector<GLuint*> *r_Draw::texLib;
std::vector<g_Wall*> *r_Draw::mapWalls = new std::vector<g_Wall*>();
std::vector<g_Roof*> *r_Draw::mapRoofs = new std::vector<g_Roof*>();
std::vector<g_floor*> *r_Draw::mapFloors = new std::vector<g_floor*>();
std::vector<g_UIElement*> *r_Draw::uiElements = new std::vector<g_UIElement*>();
GLFWwindow* r_Draw::mainWindow;

void r_Draw::initGLFW()
{
	glfwInit();
	mainWindow = glfwCreateWindow(*scrWidth, *scrHeight, "BUDGIE GLFW3 ALPHA RELEASE 1.8", NULL, NULL);

	eventSystem->player = localPlayer;
	eventSystem->registerKeyEventHandler(mainWindow);
	eventSystem->registerMouseEventHandler(mainWindow);
	glfwSwapInterval(1);
	glfwMakeContextCurrent(mainWindow);
	glewExperimental = GL_TRUE;
	glewInit();

	glfwGetFramebufferSize(mainWindow, scrWidth, scrHeight);
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	std::cout << std::endl << "INIT GRAPHICS..." << std::endl;

	std::cout << "OPENGL VERSION: " << glGetString(GL_VERSION);
	std::cout << "\nGRAPHICS HARDWARE: " << glGetString(GL_VENDOR);
	std::cout << "\nDEVICE NAME: " << glGetString(GL_RENDERER);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90 / 2.0f, 800 / 600, 0.1f, 1500);
}

g_UIElement* r_Draw::generateUIElement(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, GLuint* tex)
{
	g_UIElement* el = new g_UIElement();
	std::vector<float> tl;
	std::vector<float> tr;
	std::vector<float> bl;
	std::vector<float> br;

	for (int inner = 0; inner < 3; inner++)
	{
		tl.push_back (x1);
		tl.push_back(y1);
		tl.push_back(z1);
	}
	for (int inner = 0; inner < 3; inner++)
	{
		tr.push_back(x2);
		tr.push_back(y2);
		tr.push_back(z2);
	}
	for (int inner = 0; inner < 3; inner++)
	{
		bl.push_back(x3);
		bl.push_back(y3);
		bl.push_back(z3);
	}
	for (int inner = 0; inner < 3; inner++)
	{
		br.push_back(x4);
		br.push_back(y4);
		br.push_back(z4);
	}
	el->setRect(tl, tr, bl, br);
	el->setImage(tex);

	return el;
}

glm::vec3 floatsToVec(std::vector<float>* in)
{
	glm::vec3 res;

	res.x = in->at(0);
	res.y = in->at(1);
	res.z = in->at(2);

	return res;
}

void r_Draw::r_drawEnemy(e_EnemyBase* element)
{
	std::vector<float> ptr1 = element->rect->at(0);
	std::vector<float> ptr2 = element->rect->at(1);
	std::vector<float> ptr3 = element->rect->at(2);
	std::vector<float> ptr4 = element->rect->at(3);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *element->currImg);
	glBegin(GL_QUADS);

	glm::vec3 camRight = glm::cross(eventSystem->wishDir, glm::vec3(0, 1, 0));

	glm::vec3 quadtopleftcorner = *element->pos - ((camRight + glm::vec3(0, 1, 0)) * element->width);
	glm::vec3 quadtoprightcorner = *element->pos + ((camRight - glm::vec3(0, 1, 0)) * element->width);
	glm::vec3 quadbottomrighttcorner = *element->pos + ((camRight + glm::vec3(0, 1, 0)) * element->width);
	glm::vec3 quadbottomleftcorner = *element->pos - ((camRight - glm::vec3(0, 1, 0)) * element->width);


	glTexCoord2f(0,1);
	glVertex3f(quadtopleftcorner.x, quadtopleftcorner.y, quadtopleftcorner.z);
	glTexCoord2f(1,1);
	glVertex3f(quadtoprightcorner.x, quadtoprightcorner.y, quadtoprightcorner.z);
	glTexCoord2f(1,0);
	glVertex3f(quadbottomrighttcorner.x, quadbottomrighttcorner.y, quadbottomrighttcorner.z);
	glTexCoord2f(0,0);
	glVertex3f(quadbottomleftcorner.x, quadbottomleftcorner.y, quadbottomleftcorner.z);

	//calculate enemy facing
	//glm::vec3 enemyDir;


	glEnd();
}

glm::vec3 r_Draw::findQuadNormal(glm::vec3* verts)
{
	glm::vec3 res;
	res = glm::cross((verts[0] - verts[1]), (verts[0] - verts[2]));
	return res;
}

void r_Draw::r_drawUIElement(g_UIElement* element)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1, 1, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *element->image);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(element->rect->at(0).at(0), element->rect->at(0).at(1), element->rect->at(0).at(2));
	glTexCoord2f(1, 0);
	glVertex3f(element->rect->at(1).at(0), element->rect->at(1).at(1), element->rect->at(1).at(2));
	glTexCoord2f(1, 1);
	glVertex3f(element->rect->at(2).at(0), element->rect->at(2).at(1), element->rect->at(2).at(2));
	glTexCoord2f(0, 1);
	glVertex3f(element->rect->at(3).at(0), element->rect->at(3).at(1), element->rect->at(3).at(2));

	glEnd();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void r_Draw::r_drawWall(g_Wall* wall)
{
	std::vector<float> ptr1 = wall->getVerts1();
	std::vector<float> ptr2 = wall->getVerts2();
	std::vector<float> ptr3 = wall->getVerts3();
	std::vector<float> ptr4 = wall->getVerts4();
	
	if (!wall->w_isDoor)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *texLib->at(0));
		

		glBegin(GL_QUADS);

		int distancex = (wall->endXY[0] - wall->startXY[0]) * (wall->endXY[0] - wall->startXY[0]);
		int distancey = (wall->endXY[1] - wall->startXY[1]) * (wall->endXY[1] - wall->startXY[1]);

		double distance = sqrt(distancex + distancey);

		glTexCoord2f(0, 1);
		glVertex3f(ptr3[0], ptr3[1], ptr3[2]);
		glTexCoord2f(0, 0);
		glVertex3f(ptr1[0], ptr1[1], ptr1[2]);
		glTexCoord2f(distance /4 , 0);
		glVertex3f(ptr2[0], ptr2[1], ptr2[2]);
		glTexCoord2f(distance /4, 1);
		glVertex3f(ptr4[0], ptr4[1], ptr4[2]);
		glEnd();
	}
	else
	{

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *texLib->at(2));
		glBegin(GL_QUADS);

		glTexCoord2f(1, 0);
		glVertex3f(ptr3[0], ptr3[1], ptr3[2]);
		glTexCoord2f(1, 1);
		glVertex3f(ptr1[0], ptr1[1], ptr1[2]);
		glTexCoord2f(0, 1);
		glVertex3f(ptr2[0], ptr2[1], ptr2[2]);
		glTexCoord2f(0, 0);
		glVertex3f(ptr4[0], ptr4[1], ptr4[2]);
		glEnd();
	}
}

void r_Draw::r_drawFloor(g_floor* wall)
{
	std::vector<float> ptr1 = wall->getVerts1();
	std::vector<float> ptr2 = wall->getVerts2();
	std::vector<float> ptr3 = wall->getVerts3();
	std::vector<float> ptr4 = wall->getVerts4();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texLib->at(1));
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(ptr1[0], ptr1[1], ptr1[2]);
	glTexCoord2f(0, 10);
	glVertex3f(ptr2[0], ptr2[1], ptr2[2]);
	glTexCoord2f(10, 0);
	glVertex3f(ptr3[0], ptr3[1], ptr3[2]);
	glTexCoord2f(10, 10);
	glVertex3f(ptr4[0], ptr4[1], ptr4[2]);
	glEnd();

}

void r_Draw::r_drawRoof(g_Roof* wall)
{
	std::vector<float> ptr1 = wall->getVerts1();
	std::vector<float> ptr2 = wall->getVerts2();
	std::vector<float> ptr3 = wall->getVerts3();
	std::vector<float> ptr4 = wall->getVerts4();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texLib->at(1));
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(ptr1[0], ptr1[1], ptr1[2]);
	glTexCoord2f(0, 10);
	glVertex3f(ptr2[0], ptr2[1], ptr2[2]);
	glTexCoord2f(10, 0);
	glVertex3f(ptr3[0], ptr3[1], ptr3[2]);
	glTexCoord2f(10, 10);
	glVertex3f(ptr4[0], ptr4[1], ptr4[2]);
	glEnd();

}

void r_Draw::renderScene(void) {

	// Clear Color and Depth Buffers

	glClearColor(0, 0, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();
	glLoadIdentity();
	gluPerspective(90 / 2.0f, 800 / 600, 0.1f, 1500);
	// Reset transformations
	camera->Position->x = localPlayer->Position->x;
	camera->Position->y = localPlayer->Position->y;
	camera->Position->z = localPlayer->Position->z;

	glRotatef(camera->Rotation->y, 0, 1, 0);

	glTranslatef(-camera->Position->x, -camera->Position->y, -camera->Position->z);
	for each (g_floor* floor in *r_Draw::mapFloors)
	{
		r_drawFloor(floor);
	}
	for each (g_Roof* roof in *r_Draw::mapRoofs)
	{
		r_drawRoof(roof);
	}
	for each (g_Wall* wall in *r_Draw::mapWalls)
	{
		r_drawWall(wall);
	}

	for each(e_EnemyBase* e in *r_Draw::actorMan->activeEnemies)
	{
		r_drawEnemy(e);
	}

	glPopMatrix();
	for each (g_UIElement* el in *r_Draw::uiElements)
	{
		r_drawUIElement(el);
	}




	glfwSwapBuffers(mainWindow);
}

r_Draw::r_Draw()
{
	this->texLib = new std::vector<GLuint*>();
	this->scrWidth = new int();
	this->scrHeight = new int();
}

r_Draw::~r_Draw()
{
}

void r_Draw::LoadTextures()
{
	std::string* paths = new std::string[24]();
	paths[0] = ".\\TEX\\WOLFWALL1.bmp";
	paths[1] = ".\\TEX\\WOLFWOOD.bmp";
	paths[2] = ".\\TEX\\WOLFDOOR.bmp";
	paths[3] = ".\\TEX\\WOLFHUD.bmp";
	paths[4] = ".\\TEX\\PISTOL1.png";
	paths[5] = ".\\TEX\\PISTOL2.png";
	paths[6] = ".\\TEX\\PISTOL3.png";
	paths[7] = ".\\TEX\\PISTOL4.png";
	paths[8] = ".\\TEX\\PISTOL5.png";
	paths[9] = ".\\TEX\\MACHINE1.png";
	paths[10] = ".\\TEX\\MACHINE2.png";
	paths[11] = ".\\TEX\\MACHINE3.png";
	paths[12] = ".\\TEX\\MACHINE4.png";
	paths[13] = ".\\TEX\\MACHINE5.png";
	paths[14] = ".\\TEX\\E\\SOLDIER1.png";
	paths[15] = ".\\TEX\\E\\SOLDIER2.png";
	paths[16] = ".\\TEX\\E\\SOLDIER3.png";
	paths[17] = ".\\TEX\\E\\SOLDIER4.png";
	paths[18] = ".\\TEX\\E\\SOLDIER5.png";
	paths[19] = ".\\TEX\\E\\SOLDIER6.png";
	paths[20] = ".\\TEX\\E\\SOLDIER7.png";
	paths[21] = ".\\TEX\\E\\SOLDIER8.png";
	paths[22] = ".\\TEX\\E\\SOLDIER9.png";
	paths[23] = ".\\TEX\\E\\SOLDIER10.png";
	LoadTexture(paths);
	//uiElements->push_back(generateTestUIElement());
}

void r_Draw::LoadUIElements()
{
	uiElements->push_back(generateUIElement(0, 0.8, 0, 1, 0.8, 0, 0, 1, 0, 1, 1, 0, texLib->at(3)));
	uiElements->push_back(generateUIElement(0.25, 0.4, 0, 0.75, 0.4, 0, 0.25, 0.85, 0, 0.75, 0.85, 0, texLib->at(4)));
}

void r_Draw::LoadTexture(std::string* path)
{
	unsigned char** dataArr = new unsigned char*[24];
	GLuint* textures = new GLuint[24];
	glGenTextures(24, textures);
	unsigned char* data;
	for (int c = 0; c < 24; c++)
	{

		int width, height, nrChannels;
		const char* p = path[c].c_str();
		data = stbi_load(p, &width, &height, &nrChannels, 4);
		dataArr[c] = data;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[c]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		std::cout << std::endl << "Texture at: " << textures[c] << " success.";

		if (!data)
		{
			std::cout << std::endl << "FAILED TO LOAD TEXTURE";
		}

		texLib->push_back(&textures[c]);
		stbi_image_free(data);
	}
}
