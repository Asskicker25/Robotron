#include "Spheroid.h"

Spheroid::Spheroid() : BaseElectrode()
{
	InitializeEntity(this);

	tag = "Spheroid";

	phyObj->userData = this;
}

void Spheroid::Start()
{
}

void Spheroid::Update(float deltaTime)
{
}

void Spheroid::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/Enemies/Spheroid/sphereoid6.ply");
	model->transform.SetScale(glm::vec3(0.01f));
	//model->LoadModel("Assets/Models/DefaultSphere.fbx");

	phyObj->Initialize(model, AABB, STATIC, TRIGGER);
}

void Spheroid::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	model->isActive = false;
	physicsEngine->RemovePhysicsObject(phyObj);
}
