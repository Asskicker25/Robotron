#pragma once

#include <Graphics/Renderer.h>
#include <Physics/PhysicsEngine.h>
//#include "EntityManager.h"

class EntityManager;

class Entity
{

public:
	void* entityManager;
	std::string entityId;

	virtual ~Entity() {};

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) = 0;
	virtual void RemoveFromRendererAndPhysics(Renderer& renderer, PhysicsEngine& physicsEngine) = 0;
	virtual void Destroy();
	
};

