#pragma once

#include "../BaseEnemy.h"

class Hulk : public BaseEnemy
{


public:
	enum AnimationState
	{
		NONE = -1,
		LEFT = 0,
		RIGHT = 1,
		UP = 2,
	};

	AnimationState currentAnimation = NONE;

	Hulk();

private:

	void Start() override;
	void UpdateAI(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
	void MoveTowardsPlayerPosition(float xPos, float yPos) override;
	void OnPlayerDead() override;

	void UpdateAnimationState();
	void ChangeAnimationState(AnimationState animationState);
};

