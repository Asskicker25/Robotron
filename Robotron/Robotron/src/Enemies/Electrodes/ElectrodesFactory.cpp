#include "ElectrodesFactory.h"

#include "Spheroid.h"

BaseElectrode* ElectrodesFactory::CreateSpheroid()
{
	BaseElectrode* baseElectrode = new Spheroid();
	
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
