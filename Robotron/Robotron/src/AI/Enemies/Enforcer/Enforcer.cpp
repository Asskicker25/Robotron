#include "Enforcer.h"

Enforcer::Enforcer()
{

}

void Enforcer::Start()
{
}

void Enforcer::UpdateAI(float deltaTime)
{
	ScaleUp(deltaTime);
}

void Enforcer::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
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
}

void Enforcer::MoveTowardsPlayerPosition(float xPos, float yPos)
{
}

void Enforcer::OnPlayerDead()
{
}

void Enforcer::ScaleUp(float deltaTime)
{
	if (isScale) return;

	model->transform.SetScale(glm::vec3(model->transform.scale.x + (deltaTime * scaleSpeed)));

	if (model->transform.scale.x > 0.0075f)
	{
		isScale = true;
		isMovingRandom = true;
 	}
}
