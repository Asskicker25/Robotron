#pragma once

#include "BaseElectrode.h"

class Spheroid : public BaseElectrode
{
	// Inherited via BaseElectrode
public:

	Spheroid();

	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

