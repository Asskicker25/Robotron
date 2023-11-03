#include "CubeElectrode.h"

CubeElectrode::CubeElectrode() : BaseElectrode()
{
	InitializeEntity(this);

	tag = "Electroid";

	phyObj->userData = this;
}

void CubeElectrode::Start()
{
}

void CubeElectrode::Update(float deltaTime)
{
}

void CubeElectrode::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/DefaultCube.fbx");

	phyObj->Initialize(model, AABB, STATIC, TRIGGER);
}

void CubeElectrode::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	model->isActive = false;
	physicsEngine->RemovePhysicsObject(phyObj);
}
