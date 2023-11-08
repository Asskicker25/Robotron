#pragma once

#include "../BaseEnemy.h"
#include "../../../Bullet/BulletFactory.h"

class Enforcer : public BaseEnemy
{

private:

	enum EnforcerState
	{
		IDLE,
		RANDOM,
		CHASING
	};

	bool isScale = false;
	bool isPlayerDead = false;
	float scaleSpeed = 0.005f;

	static constexpr float chaseRadius = 8.0f;
	static constexpr float chaseStopDistance = 0.5f;

	float shootingTimeStep = 0;
	float shootingTimeInterval = 1;

	glm::vec3 playerPos = glm::vec3(0);

	BulletFactory* bulletFactory;

	// Inherited via BaseAI
	void Start() override;
	void UpdateAI(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
	void MoveTowardsPlayerPosition(float xPos, float yPos) override;
	void OnPlayerDead() override;

	void ScaleUp(float deltaTime);

	void SwitchState(EnforcerState state);

	void UpdateEnforcer(float deltaTime);

	void UpdateChasing(float deltaTime);
	void UpdateRandom(float deltaTime);

	void ShootBullet(glm::vec3 direction);

public:
	
	EnforcerState currentState = IDLE;

	Enforcer();

};

