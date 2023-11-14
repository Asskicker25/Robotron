#pragma once

#include "../BaseAI.h"

class EnemiesManager;

class BaseEnemy : public BaseAI
{

public:

	EnemiesManager* enemiesManager;

	BaseEnemy();
	virtual ~BaseEnemy() {};

	virtual void Start() = 0;
	virtual void UpdateAI(float deltaTime) = 0;
	virtual void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) = 0;
	virtual void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) = 0;

	virtual void MoveTowardsPlayerPosition(float xPos, float yPos) = 0;
	virtual void OnPlayerDead() = 0;
};

 