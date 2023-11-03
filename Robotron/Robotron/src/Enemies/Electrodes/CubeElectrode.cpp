#include "CubeElectrode.h"

CubeElectrode::CubeElectrode() : BaseElectrode()
{
	InitializeEntity(this);
}

void CubeElectrode::Start()
{
}

void CubeElectrode::Update(float deltaTime)
{
}

void CubeElectrode::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void CubeElectrode::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
