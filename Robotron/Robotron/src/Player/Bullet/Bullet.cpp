#include "Bullet.h"

Bullet::Bullet ()
{
	model = new Model();
	phyObj = new PhysicsObject();

	bulletSpeed = 30.0f;
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
			Destroy();
			Debugger::Print("Bullet Hit");
		});
}

void Bullet::RemoveFromRendererAndPhysics(Renderer& renderer, PhysicsEngine& physicsEngine)
{
	model->isActive = false;
	physicsEngine.RemovePhysicsObject(phyObj);
}

void Bullet::Start()
{
}

void Bullet::Update(float deltaTime)
{
}


void Bullet::AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine)
{

}

void Bullet::RemoveFromRenderer(Renderer& renderer)
{
}

void Bullet::RemoveFromPhysics(PhysicsEngine& physicsEngine)
{
}

