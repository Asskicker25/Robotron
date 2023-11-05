#pragma once

#include "BaseElectrode.h"
#include "../../AnimationHelper/AnimationHelper.h"

class Spheroid : public BaseElectrode, public AnimationHelper
{
	// Inherited via BaseElectrode
public:

	Spheroid();

	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

