#include "Bullet.h"

Bullet::Bullet () 
{
	phyObj->userData = this;

	bulletSpeed = 30.0f;
	
	tag = "Bullet";
}

Bullet::~Bullet()
{
}

void Bullet::SetPositionAndDir(glm::vec3 pos, glm::vec3 dir)
{
	model->transform.SetPosition(pos);
	phyObj->velocity = dir * bulletSpeed;
}

void Bullet::CreateBulletInstance(Model* bullet)
{
	model->CopyFromModel(*bullet);
	phyObj->Initialize(model, SPHERE, DYNAMIC, TRIGGER, true);

	phyObj->AssignCollisionCallback([this](PhysicsObject* otherObject)
		{
			Entity* other = (Entity*)otherObject->userData;
			std::string tag = other->tag;

			if (tag == "Enemy" || tag == "EnforcerBullet")
			{
				other->Destroy();
				Destroy();
			}

			if (tag == "Hulk")
			{
				Destroy();
			}

			if (tag == "Border")
			{
				Destroy();
			}
		});
}

void Bullet::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{

}

void Bullet::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);
}

void Bullet::Start()
{
}

void Bullet::Update(float deltaTime)
{
}


