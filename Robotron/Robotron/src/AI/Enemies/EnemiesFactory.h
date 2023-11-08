#pragma once

#include "BaseEnemy.h"
#include <Graphics/Model.h>

class EnemiesFactory
{
private:
	int currentCount = 0;

public :

	Renderer* renderer;
	Shader* shader;
	PhysicsEngine* physicsEngine;

	void AddComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine);

	BaseEnemy* CreateSpheroid();

	BaseEnemy* CreateGrunt();

	BaseEnemy* CreateHulk();
	 
	BaseEnemy* CreateEnforcer();

	BaseEnemy* CreateEnemyByType(const int& type = 0);

};

