#pragma once

#include "BaseBullet.h"

class Bullet : public BaseBullet
{

public:

	Bullet();
	~Bullet();

	// Inherited via BaseBullet
	void Start() override;
	void Update(float deltaTime) override;
	void SetPositionAndDir(glm::vec3 pos, glm::vec3 dir) override;
	void CreateBulletInstance(Model* bullet) override;


	// Inherited via BaseBullet
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;

	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;


	// Inherited via BaseBullet
	void UpdatePlayerPos(float xPos, float yPos) override;

};

