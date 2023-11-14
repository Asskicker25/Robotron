#pragma once
#include "BaseBullet.h"

class BouncingOrb : public BaseBullet
{
	// Inherited via BaseBullet
	void Start() override;
	void Update(float deltaTime) override;
	void SetPositionAndDir(glm::vec3 pos, glm::vec3 dir) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
	void UpdatePlayerPos(float xPos, float yPos) override;

public:

	BouncingOrb();
	void CreateBulletInstance(Model* bullet) override;
};

