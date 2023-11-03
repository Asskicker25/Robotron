#include "ElectroidManaager.h"
#include "ElectrodesFactory.h"

class ElectroidManaager::PIMPL
{
public:
	ElectrodesFactory* factory;

	PIMPL();
	void SpawnElectroids();

};


ElectroidManaager::PIMPL::PIMPL()
{
	factory = new ElectrodesFactory();
}

void ElectroidManaager::PIMPL::SpawnElectroids()
{
	BaseElectrode* electrode = factory->CreateCubeElectrode();

	electrode->model->transform.SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));
}


ElectroidManaager::ElectroidManaager() : pimpl{new PIMPL()}
{
	InitializeEntity(this);
	pimpl->SpawnElectroids();
}

void ElectroidManaager::Start()
{
}

void ElectroidManaager::Update(float deltaTime)
{
}

void ElectroidManaager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	pimpl->factory->AddComponents(renderer, shader, physicsEngine);
}

void ElectroidManaager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

