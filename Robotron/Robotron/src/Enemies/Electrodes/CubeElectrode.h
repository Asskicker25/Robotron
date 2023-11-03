#pragma once

#include "BaseElectrode.h"

class CubeElectrode : public BaseElectrode
{
	// Inherited via BaseElectrode
public:

	CubeElectrode();

	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

