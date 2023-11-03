#include "ElectrodesFactory.h"

#include "CubeElectrode.h"

BaseElectrode* ElectrodesFactory::CreateCubeElectrode()
{
	BaseElectrode* baseElectrode = new CubeElectrode();
	
	renderer->AddModel(baseElectrode->model, shader);
	physicsEngine->AddPhysicsObject(baseElectrode->phyObj);

	return baseElectrode;
}

void ElectrodesFactory::AddComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
	this->physicsEngine = physicsEngine;
}
