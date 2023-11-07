#pragma once

#include "../EntityManager/Entity.h"
#include "../AnimationHelper/AnimationHelper.h"

class EnemiesManager;

class BaseEnemy : public Entity, public AnimationHelper
{

public:
	Model* model;
	PhysicsObject* phyObj;

	EnemiesManager* enemiesManager;

	float speed = 3.0f;
	float score = 0;

	BaseEnemy();
	virtual ~BaseEnemy() {};

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) = 0;
	virtual void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) = 0;

	virtual void MoveTowardsPlayerPosition(float xPos, float yPos) = 0;
	virtual void OnPlayerDead() = 0;
};

 