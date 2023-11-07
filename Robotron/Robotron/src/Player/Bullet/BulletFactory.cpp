#include "BulletFactory.h"

#include "Bullet.h"

BaseBullet* BulletFactory::CreateBaseBullet()
{
	if (baseBulletPrefab == nullptr)
	{
		baseBulletPrefab = new Model("Assets/Models/DefaultCube.fbx");
		baseBulletPrefab->transform.SetScale(glm::vec3(0.05f));
		baseBulletPrefab->meshes[0]->material->SetBaseColor(glm::vec3(0.0f, 1.0f, 0.0f));
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
