#include "TrackingMissile.h"
#include "../AI/Enemies/Brain/Brain.h"

TrackingMissile::TrackingMissile()
{
	tag = "TrackingMissile";
	bulletSpeed = 5.0f;
	phyObj->userData = this;
}

void TrackingMissile::Start()
{
	

}

void TrackingMissile::Update(float deltaTime)
{
	
}

void TrackingMissile::SetPositionAndDir(glm::vec3 pos, glm::vec3 dir)
{
}


void TrackingMissile::CreateBulletInstance(Model* bullet)
{
	model->CopyFromModel(*bullet);
	phyObj->Initialize(model,AABB,DYNAMIC,TRIGGER,true);

	phyObj->AssignCollisionCallback([this](PhysicsObject* otherObject)
		{
			Entity* other = (Entity*)otherObject->userData;
			std::string tag = other->tag;

			if (tag == "Border")
			{
				Destroy();
			}
		});

}

void TrackingMissile::UpdatePlayerPos(float xPos, float yPos)
{
	glm::vec3 diff = glm::vec3(xPos,yPos,0.0f) - model->transform.position;

	glm::vec3 dir = glm::normalize(diff);

	float sqDist = glm::dot(diff, diff);

	phyObj->velocity = dir * bulletSpeed;

	if (sqDist < minReachDist * minReachDist)
	{
		phyObj->velocity = glm::vec3(0);
	}
}

void TrackingMissile::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void TrackingMissile::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	renderer->RemoveModel(model);

	physicsEngine->RemovePhysicsObject(phyObj);
}
