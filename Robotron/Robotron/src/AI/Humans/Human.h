#pragma once

#include "../BaseAI.h"

class HumansManager;
class GameMediator;

class Human : public BaseAI
{

public:

	GameMediator* gameMediator;

	enum HumanAnimationState
	{
		NONE = -1,
		LEFT = 0,
		RIGHT = 1,
		UP = 2,
		DOWN = 3
	};
	enum HumanType
	{
		DADDY, MOMMY, MIKEY
	};

	HumanType humanType;
	HumanAnimationState currentAnimation = NONE;

	Human(HumanType humanType);

	HumansManager* humansManager;


	float speedMin = 2.0f;
	float speedMax = 5.0f;

	void RemoveFromHumanManager();
	void ChangeToProg();

private:

	void Start() override;
	void UpdateAI(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
	void MoveTowardsPlayerPosition(float xPos, float yPos) override;
	void OnPlayerDead() override;

	void ChangeAnimationState(HumanAnimationState animationState);
	void UpdateAnimationState();

};

