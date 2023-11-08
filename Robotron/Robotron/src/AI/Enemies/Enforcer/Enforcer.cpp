#include "Enforcer.h"
#include "../EnemiesManager.h"
#include "../../../Bullet/EnforcerBullet.h"

Enforcer::Enforcer()
{
	score = 150;
	speed = 5.0f;

}

void Enforcer::Start()
{
}

void Enforcer::UpdateAI(float deltaTime)
{
	ScaleUp(deltaTime);
	UpdateEnforcer(deltaTime);

}

void Enforcer::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	bulletFactory = new BulletFactory();
	bulletFactory->AssignRenderesAndPhysics(renderer, shader, physicsEngine);

	model->LoadModel("Assets/Models/Enemies/Enforcer/enforcer1.ply");
	model->transform.SetScale(glm::vec3(0));
	phyObj->Initialize(model, AABB, DYNAMIC, TRIGGER,true);

	phyObj->AssignCollisionCallback([this](PhysicsObject* otherObject)
		{
			Entity* entity = (Entity*)otherObject->userData;

			std::string tag = entity->tag;

			if (tag == "Border")
			{
				ChangeRandomDirection();
			}
		});
}

void Enforcer::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);

	enemiesManager->RemoveEnemy(this);
}

void Enforcer::MoveTowardsPlayerPosition(float xPos, float yPos)
{
	playerPos = glm::vec3(xPos, yPos, 0);
}

void Enforcer::OnPlayerDead()
{
	isPlayerDead = true;
	SwitchState(RANDOM);
}

void Enforcer::ScaleUp(float deltaTime)
{
	if (isScale) return;

	model->transform.SetScale(glm::vec3(model->transform.scale.x + (deltaTime * scaleSpeed)));

	if (model->transform.scale.x > 0.0075f)
	{
		isScale = true;
		isMovingRandom = true;
		SwitchState(RANDOM);
 	}
}

void Enforcer::SwitchState(EnforcerState state)
{
	this->currentState = state;
}

void Enforcer::UpdateEnforcer(float deltaTime)
{
	switch (currentState)
	{
	case NONE:
		break;
	case RANDOM:
		UpdateRandom(deltaTime);
		break;
	case CHASING:
		UpdateChasing(deltaTime);
		break;
	}
}

void Enforcer::UpdateChasing(float deltaTime)
{
	glm::vec3 diff = playerPos - model->transform.position;
	glm::vec3 dir = glm::normalize(diff);

	float sqDist = glm::dot(diff, diff);

	if (sqDist < chaseStopDistance * chaseStopDistance)
	{
		phyObj->velocity = glm::vec3(0);
	}
	else
	{
		phyObj->velocity = dir * speed;
	}

	shootingTimeStep += deltaTime;

	if (shootingTimeStep > shootingTimeInterval)
	{
		shootingTimeStep = 0;

		ShootBullet(dir);
	}

}

void Enforcer::UpdateRandom(float deltaTime)
{
	if (isPlayerDead) return;
	
	glm::vec3 diff = playerPos - model->transform.position;

	float sqDist = glm::dot(diff, diff);

	if (sqDist < chaseRadius * chaseRadius)
	{
		SwitchState(CHASING);
	}
}

void Enforcer::ShootBullet(glm::vec3 direction)
{
	if (isPlayerDead) return;

	BaseBullet* bullet = bulletFactory->CreateEnforcerBullet();

	bullet->model->transform.SetPosition(model->transform.position);

	bullet->phyObj->velocity = direction * bullet->bulletSpeed;

	//((EnforcerBullet*)bullet)->SetAnimationState(0);
}
