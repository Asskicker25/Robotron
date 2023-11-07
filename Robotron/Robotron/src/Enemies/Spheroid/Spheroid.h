#pragma once

#include "../BaseEnemy.h"

class Spheroid : public BaseEnemy
{
	// Inherited via BaseElectrode

private:

	glm::vec3 moveDir = glm::vec3(0.0f);

	void Start() override;
	void UpdateEnemy(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	void ChangeDirection();

	void OnCollision(PhysicsObject* otherObject);

public:

	Spheroid();

	void MoveTowardsPlayerPosition(float xPos, float yPos) override;
	void OnPlayerDead() override;


};

