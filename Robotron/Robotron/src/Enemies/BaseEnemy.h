#pragma once

#include "../EntityManager/Entity.h"
#include "../AnimationHelper/AnimationHelper.h"

class BaseEnemy : public Entity, public AnimationHelper
{

public:
	bool isDestroyed = false;

	Model* model;
	PhysicsObject* phyObj;

	BaseEnemy();
	virtual ~BaseEnemy() {};

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) = 0;
	virtual void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) = 0;

	virtual void MoveTowardsPlayerPosition(float xPos, float yPos) = 0;
};

 