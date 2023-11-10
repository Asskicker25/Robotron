#include "Tank.h"
#include "../EnemiesManager.h"
#include "../../../Utilities/Random.h"

Tank::Tank()
{
	score = 200;
}


void Tank::Start()
{
}

void Tank::UpdateAI(float deltaTime)
{
	UpdateAnimation(deltaTime);
	CalculateShoot(deltaTime);
}

void Tank::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->physicsEngine = physicsEngine;

	bulletFactory = new BulletFactory();
	bulletFactory->AssignRenderesAndPhysics(renderer, shader, physicsEngine);

	model->LoadModel("Assets/Models/Enemies/Tank/tank1.ply");
	model->transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	model->transform.SetScale(glm::vec3(0.0075f));
	model->isActive = false;

	renderer->AddModel(model, shader);
	phyObj->Initialize(model, AABB, DYNAMIC, TRIGGER, true);
	phyObj->userData = this;
	physicsEngine->AddPhysicsObject(phyObj);

	phyObj->AssignCollisionCallback([this](PhysicsObject* otherObject)
		{
			Entity* entity = (Entity*)otherObject->userData;
			std::string tag = entity->tag;

		});

	AssignRendererAndShader(renderer, shader);
	SetTransformHolder(model);
	SetModelScale(0.0075f);
	SetAnimationInterval(0.1f);

	AddModelToAnimationList(0, "Assets/Models/Enemies/Tank/tank1.ply") ;
	AddModelToAnimationList(0, "Assets/Models/Enemies/Tank/tank2.ply") ;
	AddModelToAnimationList(0, "Assets/Models/Enemies/Tank/tank3.ply") ;
	AddModelToAnimationList(0, "Assets/Models/Enemies/Tank/tank4.ply") ;

	SetAnimationState(0);
}

void Tank::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	DestroyAnimationModels();

	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);

	enemiesManager->RemoveEnemy(this);
}

void Tank::MoveTowardsPlayerPosition(float xPos, float yPos)
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

void Tank::OnPlayerDead()
{
	phyObj->velocity = glm::vec3(0);
}

void Tank::CalculateShoot(float deltaTime)
{
	timeStep += deltaTime;

	if (timeStep > bulletSpawnInterval)
	{
		timeStep = 0;

		ShootBullet(model->transform.position);
	}
}

void Tank::ShootBullet(glm::vec3 pos)
{
	BaseBullet* bullet = bulletFactory->CreateBouncingOrb();
	bullet->model->transform.SetPosition(pos);

	float randomX = GetRandomFloatNumber(-1, 1);
	float randomY = GetRandomFloatNumber(-1, 1);
	bullet->phyObj->velocity = glm::vec3(randomX, randomY, 0) * bullet->bulletSpeed;
}

