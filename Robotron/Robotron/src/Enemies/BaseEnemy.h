#pragma once

#include "../EntityManager/Entity.h"

class BaseEnemy : public Entity
{

public:

	Model* model;
	PhysicsObject* phyObj;

	BaseEnemy();
	virtual ~BaseEnemy() {};

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) = 0;
	virtual void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) = 0;
};

