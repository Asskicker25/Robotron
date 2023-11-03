#pragma once

#include "../EntityManager/Entity.h"

class BasePlayer : public Entity
{
public:

	Model* model;
	PhysicsObject* phyObj;

	float speed;
	float maxHealth;

	virtual ~BasePlayer() {};

	//BasePlayer
	virtual void Shoot() = 0;
	virtual void UpdateVelocity(glm::vec3 velocity) = 0;
	virtual void SetMaxHealth(const float& maxHealth) = 0;
	virtual void SetSpeed(const float& speed) = 0;

	// Inherited via Entity
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) = 0;
	virtual void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) = 0;
};

