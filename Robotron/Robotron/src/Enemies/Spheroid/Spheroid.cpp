#include "Spheroid.h"
#include "../EnemiesManager.h"

Spheroid::Spheroid() 
{
	phyObj->userData = this;

	score = 1000;

	isMovingRandom = true;

	speed = 10.0f;
}

void Spheroid::Start()
{
}

void Spheroid::UpdateEnemy(float deltaTime)
{
	UpdateAnimation(deltaTime);
}

void Spheroid::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/Enemies/Spheroid/sphereoid6.ply");
	model->transform.SetScale(glm::vec3(0.0075f));
	model->isActive = false;
	
	phyObj->Initialize(model, AABB, DYNAMIC, TRIGGER,true);
	phyObj->AssignCollisionCallback([this](PhysicsObject* otherObject)
		{
			OnCollision(otherObject);
		});

	AssignRendererAndShader(renderer, shader);
	SetTransformHolder(model);
	SetModelScale(0.0075f);
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

void Spheroid::ChangeDirection()
{

}

void Spheroid::OnCollision(PhysicsObject* otherObject)
{
	Entity* other = (Entity*)otherObject->userData;
	std::string tag = other->tag;

	if (tag == "Border")
	{
		ChangeRandomDirection();
	}
}

void Spheroid::MoveTowardsPlayerPosition(float xPos, float yPos)
{
}

void Spheroid::OnPlayerDead()
{
}
