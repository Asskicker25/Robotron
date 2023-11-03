#pragma once

#include "../../EntityManager/EntityManager.h"

class BaseBullet : public Entity
{
public:

	Model* model;
	PhysicsObject* phyObj;

	float bulletSpeed;

	virtual ~BaseBullet() {};

	// Inherited via Entity

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void SetPositionAndDir(glm::vec3 pos, glm::vec3 dir) = 0;
	virtual void CreateBulletInstance(Model* bullet) = 0;
	virtual void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) = 0;
	virtual void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) = 0;

};