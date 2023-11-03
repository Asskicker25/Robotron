#include "BulletFactory.h"

#include "Bullet.h"

BaseBullet* BulletFactory::CreateBaseBullet()
{
	if (baseBulletPrefab == nullptr)
	{
		baseBulletPrefab = new Model("Assets/Models/DefaultSphere.fbx");
		baseBulletPrefab->transform.SetScale(glm::vec3(0.1f));
	}

	Bullet* bullet = new Bullet();

	bullet->CreateBulletInstance(baseBulletPrefab);

	renderer->AddModel(bullet->model, shader);
	physicsEngine->AddPhysicsObject(bullet->phyObj);


	EntityManager::GetInstance().AddEntity("Bullet" + std::to_string(bulletCount), bullet);

	bulletCount++;

	return bullet;
}

void BulletFactory::AssignRenderesAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
	this->physicsEngine = physicsEngine;
}
