#include "Brain.h"

Brain::Brain()
{
	score = 500;
}

void Brain::Start()
{
}

void Brain::UpdateAI(float deltaTime)
{
	UpdateAnimation(deltaTime);
	UpdateAnimationState();
	HandleUpdate(deltaTime);
}

void Brain::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/Enemies/Brain/brain2.ply");
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

			if (tag == "Border")
			{
				ChangeRandomDirection();
			}

			if (tag == "Human")
			{
				humanManager->RemoveHuman(chasingHuman);
			}
		});

	AssignRendererAndShader(renderer, shader);
	SetTransformHolder(model);
	SetModelScale(0.0075f);
	SetAnimationInterval(0.1f);

	AddModelToAnimationList(LEFT, "Assets/Models/Enemies/Brain/brain1.ply");
	AddModelToAnimationList(LEFT, "Assets/Models/Enemies/Brain/brain2.ply");
	AddModelToAnimationList(LEFT, "Assets/Models/Enemies/Brain/brain3.ply");


	AddModelToAnimationList(RIGHT, "Assets/Models/Enemies/Brain/brain4.ply");
	AddModelToAnimationList(RIGHT, "Assets/Models/Enemies/Brain/brain5.ply");
	AddModelToAnimationList(RIGHT, "Assets/Models/Enemies/Brain/brain6.ply");

	AddModelToAnimationList(DOWN, "Assets/Models/Enemies/Brain/brain7.ply");
	AddModelToAnimationList(DOWN, "Assets/Models/Enemies/Brain/brain8.ply");
	AddModelToAnimationList(DOWN, "Assets/Models/Enemies/Brain/brain9.ply");

	AddModelToAnimationList(UP, "Assets/Models/Enemies/Brain/brain10.ply");
	AddModelToAnimationList(UP, "Assets/Models/Enemies/Brain/brain11.ply");
	AddModelToAnimationList(UP, "Assets/Models/Enemies/Brain/brain12.ply");

	SetAnimationState(LEFT);
}

void Brain::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	DestroyAnimationModels();

	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);
}

void Brain::MoveTowardsPlayerPosition(float xPos, float yPos)
{
}

void Brain::OnPlayerDead()
{
}

void Brain::SwitchState(BrainState state)
{
	this->brainState = state;
}

void Brain::HandleUpdate(float deltaTime)
{
	switch (brainState)
	{
	case NONE:
		break;
	case CHASEHUMAN:

		ChaseHumanMoveUpdate(deltaTime);

		timeStep += deltaTime;

		if (timeStep > chaseUpdateInterval)
		{
			timeStep = 0;
			ChaseHumanUpdate(deltaTime);
		}

		break;
	case CHASEPLAYER:
		ChasePlayerUpdate(deltaTime);
		break;
	}
}

void Brain::ChaseHumanUpdate(float deltaTime)
{
	if (humanManager->listOfHumans.size() <= 0)
	{
		SwitchState(CHASEPLAYER);
		return;
	}

	float shortDistance = DistanceFromHuman(humanManager->listOfHumans[0]);
	int index = 0;

	for (int i = 1; i < humanManager->listOfHumans.size(); i++)
	{
		float distance = DistanceFromHuman(humanManager->listOfHumans[i]);

		if (distance < shortDistance)
		{
			index = i;
			shortDistance = distance;
		}
	}


	chasingHuman = humanManager->listOfHumans[index];
}

void Brain::ChaseHumanMoveUpdate(float deltaTime)
{
	if (chasingHuman == nullptr) return;

	glm::vec3 diff = chasingHuman->model->transform.position - model->transform.position;

	glm::vec3 dir = glm::normalize(diff);

	float sqDist = glm::dot(diff, diff);

	phyObj->velocity = dir * speed;

	if (sqDist < minReachDist * minReachDist)
	{
		phyObj->velocity = glm::vec3(0);
	}
}

void Brain::ChasePlayerUpdate(float deltaTime)
{
}

float Brain::DistanceFromHuman(Human* human)
{
	glm::vec3 diff = human->model->transform.position - model->transform.position;
	return glm::dot(diff, diff);
}



void Brain::ChangeAnimationState(AnimationState animationState)
{
	if (currentAnimation == animationState) return;

	currentAnimation = animationState;

	SetAnimationState(animationState);
}

void Brain::UpdateAnimationState()
{
	if (phyObj->velocity.x > 0)
	{
		ChangeAnimationState(RIGHT);
	}
	else if (phyObj->velocity.x < 0)
	{
		ChangeAnimationState(LEFT);
	}
	else if (phyObj->velocity.y > 0)
	{
		ChangeAnimationState(UP);
	}
	else if (phyObj->velocity.y < 0)
	{
		ChangeAnimationState(DOWN);
	}
}

void Brain::SetHumanManager(HumansManager* humanManager)
{
	this->humanManager = humanManager;

	SwitchState(CHASEHUMAN);
}
