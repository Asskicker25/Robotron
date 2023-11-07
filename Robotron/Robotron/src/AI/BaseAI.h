#pragma once

#include "../EntityManager/Entity.h"
#include "../AnimationHelper/AnimationHelper.h"

class BaseAI : public Entity, public AnimationHelper
{

private:
	int currentDirection = -1;

	float timeStep = 2.0f;
	float dirChangeIntervalMin = 1.0f;
	float dirChangeIntervalMax = 5.0f;
	float dirChangeInterval = 0.0f;

	glm::vec2 GetRandomDirection();
	void UpdateRandomMoveDirection(float deltaTime);

public:
	Model* model;
	PhysicsObject* phyObj;

	float speed = 3.0f;
	float score = 0;

	bool isMovingRandom = false;


	BaseAI();
	virtual ~BaseAI() {};

	virtual void Start() = 0;
	virtual void UpdateAI(float deltaTime) = 0;
	virtual void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) = 0;
	virtual void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) = 0;

	virtual void MoveTowardsPlayerPosition(float xPos, float yPos) = 0;
	virtual void OnPlayerDead() = 0;

	// Inherited via Entity
	void Update(float deltaTime) override;

	void ChangeRandomDirection();
};

