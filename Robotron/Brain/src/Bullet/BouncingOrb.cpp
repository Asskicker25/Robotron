#include "BouncingOrb.h"


BouncingOrb::BouncingOrb()
{
	tag = "BouncingOrb";
	bulletSpeed = 10.0f;
	phyObj->userData = this;
}


void BouncingOrb::Start()
{
}

void BouncingOrb::Update(float deltaTime)
{
}

void BouncingOrb::SetPositionAndDir(glm::vec3 pos, glm::vec3 dir)
{
}


void BouncingOrb::CreateBulletInstance(Model* bullet)
{
	model->CopyFromModel(*bullet);
	phyObj->Initialize(model, AABB, DYNAMIC, TRIGGER, true);

	phyObj->AssignCollisionCallback([this](PhysicsObject* otherObject)
		{
			Entity* other = (Entity*)otherObject->userData;
			std::string tag = other->tag;

			if (tag == "Border")
			{
				phyObj->velocity = -phyObj->GetCollisionNormals()[0] * bulletSpeed;
			}
		});
}

void BouncingOrb::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{

}

void BouncingOrb::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	renderer->RemoveModel(model);

	physicsEngine->RemovePhysicsObject(phyObj);
}

void BouncingOrb::UpdatePlayerPos(float xPos, float yPos)
{
}
