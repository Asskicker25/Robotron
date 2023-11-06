#pragma once

#include "../BaseEnemy.h"

class Grunt : public BaseEnemy
{

public:
	Grunt();

private:
	// Inherited via BaseEnemy
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	// Inherited via BaseEnemy
	void MoveTowardsPlayerPosition(float xPos, float yPos) override;
};

