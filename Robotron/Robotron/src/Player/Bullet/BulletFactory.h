#pragma once

#include <Graphics/Renderer.h>
#include "BaseBullet.h"

class BulletFactory 
{

private:
	int bulletCount = 0;

	Model* baseBulletPrefab = nullptr;

	Renderer* renderer;
	Shader* shader;
	PhysicsEngine* physicsEngine;

	EntityManager* entityManager;

public:
	BaseBullet* CreateBaseBullet();
	void AssignRenderesAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine, EntityManager* entityManager);
};

