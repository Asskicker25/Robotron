#pragma once

#include "../EntityManager/Entity.h"

class EnemiesManager : public Entity
{

private:
	class PIMPL;

	PIMPL* pimpl;

public:

	EnemiesManager();

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

