#pragma once

#include "../BaseEnemy.h"

class Enforcer : public BaseEnemy
{

private:

	bool isScale = false;
	float scaleSpeed = 0.005f;

	// Inherited via BaseAI
	void Start() override;
	void UpdateAI(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
	void MoveTowardsPlayerPosition(float xPos, float yPos) override;
	void OnPlayerDead() override;

	void ScaleUp(float deltaTime);

public:
	Enforcer();

};

