#include "Grunt.h"
#include "../EnemiesManager.h"

Grunt::Grunt()
{
	score = 100;
}

void Grunt::Start()
{
}

void Grunt::UpdateAI(float deltaTime)
{
	UpdateAnimation(deltaTime);
}

void Grunt::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/Enemies/Grunt/grunt1.ply");
	model->transform.SetScale(glm::vec3(0.0075f));
	model->isActive = false;
	phyObj->Initialize(model, AABB, DYNAMIC, TRIGGER);

	AssignRendererAndShader(renderer, shader);
	SetTransformHolder(model);
	SetModelScale(0.0075f);
	SetAnimationInterval(0.1f);

	AddModelToAnimationList(0, "Assets/Models/Enemies/Grunt/grunt1.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Grunt/grunt2.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Grunt/grunt3.ply");

	SetAnimationState(0);
}

void Grunt::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	DestroyAnimationModels();

	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);

	enemiesManager->RemoveEnemy(this);
}

void Grunt::MoveTowardsPlayerPosition(float xPos, float yPos)
{
	glm::vec3 diff = glm::vec3(xPos, yPos, model->transform.position.z) - model->transform.position;

	glm::vec3 dir = glm::normalize(diff);

	float sqDist = glm::dot(diff, diff);

	if (sqDist < minDistance * minDistance)
	{
		phyObj->velocity = glm::vec3(0);
	}
	else
	{
		phyObj->velocity = dir * speed;
	}
}

void Grunt::OnPlayerDead()
{
	phyObj->velocity = glm::vec3(0);
}
