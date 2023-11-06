#include "BaseEnemy.h"

BaseEnemy::BaseEnemy()
{
	tag = "Enemy";

	model = new Model();
	phyObj = new PhysicsObject();

	phyObj->userData = this;
}

