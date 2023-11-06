#pragma once

#include "../BaseEnemy.h"

class Spheroid : public BaseEnemy
{
	// Inherited via BaseElectrode
public:

	Spheroid();

	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	// Inherited via BaseEnemy
	void MoveTowardsPlayerPosition(float xPos, float yPos) override;
};

