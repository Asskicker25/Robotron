#include "Hulk.h"

Hulk::Hulk()
{
	tag = "Hulk";
	isMovingRandom = true;

	speed = 2.0f;
}

void Hulk::Start()
{
}

void Hulk::UpdateAI(float deltaTime)
{
	UpdateAnimationState();
	UpdateAnimation(deltaTime);
}

void Hulk::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/Enemies/Hulk/hulk2.ply");
	model->transform.SetScale(glm::vec3(0.0075f));
	model->isActive = false;
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

	AssignRendererAndShader(renderer, shader);
	SetTransformHolder(model);
	SetModelScale(0.0075f);
	SetAnimationInterval(0.1f);

	AddModelToAnimationList(LEFT, "Assets/Models/Enemies/Hulk/hulk1.ply");
	AddModelToAnimationList(LEFT, "Assets/Models/Enemies/Hulk/hulk2.ply");
	AddModelToAnimationList(LEFT, "Assets/Models/Enemies/Hulk/hulk3.ply");

	AddModelToAnimationList(RIGHT, "Assets/Models/Enemies/Hulk/hulk7.ply");
	AddModelToAnimationList(RIGHT, "Assets/Models/Enemies/Hulk/hulk8.ply");
	AddModelToAnimationList(RIGHT, "Assets/Models/Enemies/Hulk/hulk9.ply");

	AddModelToAnimationList(UP, "Assets/Models/Enemies/Hulk/hulk4.ply");
	AddModelToAnimationList(UP, "Assets/Models/Enemies/Hulk/hulk5.ply");
	AddModelToAnimationList(UP, "Assets/Models/Enemies/Hulk/hulk6.ply");

	SetAnimationState(LEFT);
}

void Hulk::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	DestroyAnimationModels();

	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);
}

void Hulk::MoveTowardsPlayerPosition(float xPos, float yPos)
{
}

void Hulk::OnPlayerDead()
{
}

void Hulk::UpdateAnimationState()
{
	if (phyObj->velocity.x > 0)
	{
		ChangeAnimationState(RIGHT);
	}
	else if (phyObj->velocity.x < 0)
	{
		ChangeAnimationState(LEFT);
	}
	else if (phyObj->velocity.y > 0 || phyObj->velocity.y<0)
	{
		ChangeAnimationState(UP);
	}

}

void Hulk::ChangeAnimationState(AnimationState animationState)
{
	if (currentAnimation == animationState) return;

	currentAnimation = animationState;

	SetAnimationState(animationState);
}

