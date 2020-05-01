
#include "BudgieApp.h"
#include "ActorManager.h"
#include "d_Player.h"
#include "Camera.h"
#include "d_WAD.h"
#include "r_Draw.h"
#include "a_Audio.h"

d_WAD* wadStream;
r_Draw* renderer;
d_Player* player;
Camera* camera;
e_EventSystem* eventSystem;

int main(int argc, char **argv)
{
	std::cout << "(c) 2018 Winwood Laboratories - All Rights Reserved" << std::endl << "BUDGIE ENGINE v1.8" << std::endl;

	BudgieEngine* _BE = new BudgieEngine();

	srand(static_cast <unsigned> (time(NULL)));

	renderer = new r_Draw();
	_BE->be_r_Draw = renderer;
	*_BE->be_r_Draw->scrWidth = 800;
	*_BE->be_r_Draw->scrHeight = 600;
	_BE->be_r_Draw->initGLFW();
	_BE->be_r_Draw->LoadTextures();
	_BE->be_r_Draw->LoadUIElements();

	ActorManager* actorMan = new ActorManager();
	_BE->be_ActorManager = actorMan;
	_BE->be_ActorManager->activeActors->push_back(player);

	d_WAD* wadStream = new d_WAD();
	_BE->be_d_WAD = wadStream;
	wadStream->renderer = renderer;
	renderer->actorMan = actorMan;
	_BE->be_d_WAD->ReadWAD(".\\WAD\\WAD.wad");

	player = new d_Player(wadStream->playerStart);
	player->runSpeed = 2.5;
	player->turnSpeed = 2.2;
	player->addCollider(new p_BoxCollider(player->Position, 5.0, true));

	player->pEffector = new PhysicsEffector();
	player->pEffector->attachedObject = player;
	player->pEffector->gravityScale = 0.3;

	camera = new Camera();

	a_Audio* audio = new a_Audio();

	_BE->be_d_WAD->renderer = renderer;

	eventSystem = new e_EventSystem(player, camera);
	_BE->be_e_EventSystem = eventSystem;
	_BE->be_e_EventSystem->walls = wadStream->walls;
	_BE->be_e_EventSystem->floors = wadStream->floors;
	_BE->be_e_EventSystem->uiElements = renderer->uiElements;
	_BE->be_e_EventSystem->renderer = renderer;
	_BE->be_e_EventSystem->audio = audio;


	_BE->be_r_Draw->eventSystem = eventSystem;
	_BE->be_r_Draw->localPlayer = player;
	_BE->be_r_Draw->camera = camera;
	_BE->be_r_Draw->mapWalls = wadStream->walls;
	_BE->be_r_Draw->mapFloors = wadStream->floors;
	_BE->be_r_Draw->mapRoofs = wadStream->roofs;




	d_Weapon* pistol = new d_Weapon();
	pistol->frames->push_back(_BE->be_r_Draw->texLib->at(4));
	pistol->frames->push_back(_BE->be_r_Draw->texLib->at(5));
	pistol->frames->push_back(_BE->be_r_Draw->texLib->at(6));
	pistol->frames->push_back(_BE->be_r_Draw->texLib->at(7));
	pistol->frames->push_back(_BE->be_r_Draw->texLib->at(8));
	pistol->repeating = false;
	pistol->currFrame = pistol->frames->at(0);
	pistol->fireFrame = 2;
	pistol->damage = 80;
	pistol->eventSystem = eventSystem;
	pistol->frameUpdateRate = 60;
	player->weapons->push_back(pistol);

	d_Weapon* machine = new d_Weapon();
	machine->frames->push_back(_BE->be_r_Draw->texLib->at(9));
	machine->frames->push_back(_BE->be_r_Draw->texLib->at(10));
	machine->frames->push_back(_BE->be_r_Draw->texLib->at(11));
	machine->frames->push_back(_BE->be_r_Draw->texLib->at(12));
	machine->frames->push_back(_BE->be_r_Draw->texLib->at(13));
	machine->repeating = true;
	machine->currFrame = machine->frames->at(0);
	machine->fireFrame = 3;
	machine->damage = 80;
	machine->eventSystem = eventSystem;
	machine->frameUpdateRate = 30;
	player->weapons->push_back(machine);
	player->currWeapon = player->weapons->at(0);


	_BE->be_ActorManager->wadStream = wadStream;

	_BE->be_r_Draw->actorMan = actorMan;
	_BE->be_e_EventSystem->actorMan = actorMan;


	//actorMan->GenerateEnemy("soldier");
	//actorMan->GenerateEnemy("soldier");


	std::cout << std::endl << std::endl << "Active Actors: " << actorMan->activeActors->size();

	while (true)
	{
		//_BE->be_r_Draw->renderScene();
		_BE->checkUpdate();
		_BE->be_e_EventSystem->ProcessEvents();
	}
	return 0;
}



