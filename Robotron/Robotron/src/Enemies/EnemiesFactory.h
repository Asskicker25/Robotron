#pragma once

#include "BaseEnemy.h"
#include <Graphics/Model.h>

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

