#pragma once

#include "BaseBullet.h"

class Bullet : public BaseBullet
{

public:
	Bullet();


	// Inherited via BaseBullet
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
	void SetPositionAndDir(glm::vec3 pos, glm::vec3 dir) override;
	void CreateBulletInstance(Model* bullet) override;

	// Inherited via BaseBullet
	void RemoveFromRendererAndPhysics(Renderer& renderer, PhysicsEngine& physicsEngine) override;
};

