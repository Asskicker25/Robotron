#pragma once
#include "../BaseEnemy.h"
#include "../../../Bullet/BulletFactory.h"

class Tank : public BaseEnemy
{
private:
	// Inherited via BaseEnemy
	void Start() override;
	void UpdateAI(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
	void MoveTowardsPlayerPosition(float xPos, float yPos) override;
	void OnPlayerDead() override;

	void CalculateShoot(float deltaTime);
	void ShootBullet(glm::vec3 pos);

	float minDistance = 0.5f;

	float timeStep = 0;
	float bulletSpawnInterval = 5;

	BulletFactory* bulletFactory;
	Renderer* renderer;
	PhysicsEngine* physicsEngine;

public:

	Tank();


};

