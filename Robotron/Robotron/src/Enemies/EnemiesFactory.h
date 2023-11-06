#pragma once

#include "BaseEnemy.h"

class EnemiesFactory
{
public :

	Renderer* renderer;
	Shader* shader;
	PhysicsEngine* physicsEngine;

	void AddComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine);

	BaseEnemy* CreateSpheroid();

	BaseEnemy* CreateGrunt();
};

