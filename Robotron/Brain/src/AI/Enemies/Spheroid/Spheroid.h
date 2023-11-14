#pragma once

#include "../BaseEnemy.h"

class Spheroid : public BaseEnemy
{
	// Inherited via BaseElectrode

private:

	static constexpr float spawnTimeMin = 2.0f;
	static constexpr float spawnTimeMax = 5.0f;

	static  const int spawnCount = 1;

	int currentSpawnCount = 0;

	glm::vec3 moveDir = glm::vec3(0.0f);

	float timeStep = 0;
	float timeInterval = 0;

	void Start() override;
	void UpdateAI(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	void ChangeDirection();

	void OnCollision(PhysicsObject* otherObject);

	void CalculateSpawning(float deltaTime);


public:

	Spheroid();

	void MoveTowardsPlayerPosition(float xPos, float yPos) override;
	void OnPlayerDead() override;


};

