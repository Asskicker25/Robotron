
#pragma once

#include "../../EntityManager/Entity.h"

class BaseElectrode : public Entity
{

public:

	Model* model;
	PhysicsObject* phyObj;

	BaseElectrode();
	virtual ~BaseElectrode() {};

	// Inherited via Entity
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) = 0;
	virtual void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) = 0;
};