#pragma once
#include "../BaseEnemy.h"
#include "../../Humans/HumansManager.h"
#include "../../../Bullet/BulletFactory.h"

class TrackingMissile;

class Brain  : public BaseEnemy
{

public:
	enum AnimationState
	{
		NONE = -1,
		LEFT = 0,
		RIGHT = 1,
		UP = 2,
		DOWN = 3
	};

	enum BrainState
	{
		IDLE = -1,
		CHASEHUMAN = 0,
		CHASEPLAYER
	};

	Brain();

	AnimationState currentAnimation = NONE;
	BrainState brainState = IDLE;

	void ChangeAnimationState(AnimationState animationState);
	void UpdateAnimationState();

	void SetHumanManager(HumansManager* humanManager);

	void RemoveFromRenderer();


private:
	// Inherited via BaseEnemy
	void Start() override;
	void UpdateAI(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
	void MoveTowardsPlayerPosition(float xPos, float yPos) override;
	void OnPlayerDead() override;

	void SwitchState(BrainState state);
	void HandleUpdate(float deltaTime);

	void ChaseHumanUpdate(float deltaTime);
	void ChaseHumanMoveUpdate(float deltaTime);
	void ChasePlayerUpdate(float deltaTime);

	float DistanceFromHuman(Human* human);

	void ShootBullet(glm::vec3 dir);


	static constexpr float minReachDist = 0.1f;


	BulletFactory* bulletFactory;

	HumansManager* humanManager = nullptr;

	Human* chasingHuman = nullptr;

	float timeStep = 2;
	float chaseUpdateInterval = 2;
	float shootingInterval = 4;

	bool isPlayerDead = false;

	glm::vec3 playerPos;


	Renderer* render;
	PhysicsEngine* physicsEngine;

};

