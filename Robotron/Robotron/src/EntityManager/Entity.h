#pragma once

#include <Graphics/Renderer.h>
#include <Physics/PhysicsEngine.h>

class Entity
{
public:
	virtual ~Entity() {};

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void AddToRenderer(Renderer& renderer, Shader* shader) = 0;
	virtual void AddToPhysics(PhysicsEngine& physicsEngine) = 0;
};

