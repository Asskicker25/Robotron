#pragma once

#include "BaseElectrode.h"

class ElectrodesFactory
{
public :

	Renderer* renderer;
	Shader* shader;
	PhysicsEngine* physicsEngine;

	BaseElectrode* CreateCubeElectrode();
	void AddComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine);

};

