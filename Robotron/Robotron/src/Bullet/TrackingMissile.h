#pragma once

#include "BaseBullet.h"

class Brain;

class TrackingMissile : public BaseBullet
{
private:
	// Inherited via BaseBullet
	void Start() override;
	void Update(float deltaTime) override;
	void SetPositionAndDir(glm::vec3 pos, glm::vec3 dir) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;


	static constexpr float minReachDist = 0.1f;

public:

	TrackingMissile();
	void CreateBulletInstance(Model* bullet) override;

	// Inherited via BaseBullet
	void UpdatePlayerPos(float xPos, float yPos) override;
};

