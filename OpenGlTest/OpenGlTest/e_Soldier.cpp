#include "e_Soldier.h"



e_Soldier::e_Soldier()
{
	e_EnemyBase();
}

e_Soldier::e_Soldier(glm::vec3 * pos, glm::vec3 * facing, int  health, float  width, float  height) : e_EnemyBase(pos, facing, health, width, height)
{

}


e_Soldier::~e_Soldier()
{
}
