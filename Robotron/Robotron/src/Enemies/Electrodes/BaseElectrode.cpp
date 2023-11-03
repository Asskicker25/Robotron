#include "BaseElectrode.h"

BaseElectrode::BaseElectrode()
{
	model = new Model();
	phyObj = new PhysicsObject();

}

void BaseElectrode::Start()
{
}

void BaseElectrode::Update(float deltaTime)
{
}

void BaseElectrode::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void BaseElectrode::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
