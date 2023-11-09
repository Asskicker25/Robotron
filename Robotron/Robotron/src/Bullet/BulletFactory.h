#pragma once

#include <Graphics/Renderer.h>
#include "BaseBullet.h"

class BulletFactory 
{

private:
	int bulletCount = 0;

	Model* baseBulletPrefab = nullptr;

	Model* enforcerBulletPrefab = nullptr;

	Model* trackingMissilePrefab = nullptr;

	std::vector<Model*> enforcerAnimationModels;

	Renderer* renderer;
	Shader* shader;
	PhysicsEngine* physicsEngine;

public:
	BaseBullet* CreateBaseBullet();
	BaseBullet* CreateEnforcerBullet();
	BaseBullet* CreateTrackingMissile();

	void AssignRenderesAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine);
};

