#pragma once
#include "../BaseEnemy.h"

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

	float minDistance = 0.5f;

public:

	Tank();


};

