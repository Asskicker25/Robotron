#pragma once
#include "../BaseEnemy.h"
#include "../../Humans/HumansManager.h"

class Brain : public BaseEnemy
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

	static constexpr float minReachDist = 0.1f;

	HumansManager* humanManager = nullptr;

	Human* chasingHuman = nullptr;

	float timeStep = 2;
	float chaseUpdateInterval = 2;

};

