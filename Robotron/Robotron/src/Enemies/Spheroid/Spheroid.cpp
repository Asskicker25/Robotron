#include "Spheroid.h"
#include "../EnemiesManager.h"

Spheroid::Spheroid() 
{

	InitializeEntity(this);

	phyObj->userData = this;

}

void Spheroid::Start()
{
}

void Spheroid::Update(float deltaTime)
{
	UpdateAnimation(deltaTime);
}

void Spheroid::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/Enemies/Spheroid/sphereoid6.ply");
	model->transform.SetScale(glm::vec3(0.01f));
	model->isActive = false;
	phyObj->Initialize(model, AABB, STATIC, TRIGGER);

	AssignRendererAndShader(renderer, shader);
	SetTransformHolder(model);
	SetModelScale(0.01f);
	SetAnimationInterval(0.1f);

	AddModelToAnimationList(0, "Assets/Models/Enemies/Spheroid/sphereoid1.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Spheroid/sphereoid2.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Spheroid/sphereoid3.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Spheroid/sphereoid4.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Spheroid/sphereoid5.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Spheroid/sphereoid6.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Spheroid/sphereoid7.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Spheroid/sphereoid8.ply");

	SetAnimationState(0);
}

void Spheroid::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	DestroyAnimationModels();
	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);

	enemiesManager->RemoveEnemy(this);
}

void Spheroid::MoveTowardsPlayerPosition(float xPos, float yPos)
{
}

void Spheroid::OnPlayerDead()
{
}
