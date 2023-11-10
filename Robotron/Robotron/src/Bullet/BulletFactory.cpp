#include "BulletFactory.h"

#include "Bullet.h"
#include "EnforcerBullet.h"
#include "TrackingMissile.h"
#include "BouncingOrb.h"

int BulletFactory::count = 0;

BulletFactory::BulletFactory()
{
	index = ++count;
}

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

	EntityManager::GetInstance().AddEntity("Factory" + std::to_string(index) + "Bullet" + std::to_string(bulletCount), bullet);

	bulletCount++;

	return bullet;
}

BaseBullet* BulletFactory::CreateEnforcerBullet()
{
	if (enforcerBulletPrefab == nullptr)
	{
		enforcerBulletPrefab = new Model("Assets/Models/Enemies/Enforcer/enforcerbullet1.ply");
		enforcerBulletPrefab->transform.SetScale(glm::vec3(0.0075f));
	}

	EnforcerBullet* bullet = new EnforcerBullet();

	bullet->CreateBulletInstance(enforcerBulletPrefab);

	renderer->AddModel(bullet->model, shader);
	physicsEngine->AddPhysicsObject(bullet->phyObj);

	EntityManager::GetInstance().AddEntity("Factory" + std::to_string(index)+  "EnforcerBullet" + std::to_string(bulletCount), bullet);

	bulletCount++;

	return bullet;
}

BaseBullet* BulletFactory::CreateTrackingMissile()
{
	if (trackingMissilePrefab == nullptr)
	{
		trackingMissilePrefab = new Model("Assets/Models/DefaultCube.fbx");
		trackingMissilePrefab->transform.SetScale(glm::vec3(0.3f));
		trackingMissilePrefab->meshes[0]->material->SetBaseColor(glm::vec3(0.0f, 0.0f, 1.0f));
	}

	TrackingMissile* bullet = new TrackingMissile();

	bullet->CreateBulletInstance(trackingMissilePrefab);

	renderer->AddModel(bullet->model, shader);
	physicsEngine->AddPhysicsObject(bullet->phyObj);

	EntityManager::GetInstance().AddEntity("Factory" + std::to_string(index) + "TrackingMissile" + std::to_string(bulletCount), bullet);


	bulletCount++;

	return bullet;
}

BaseBullet* BulletFactory::CreateBouncingOrb()
{
	if (bouncingOrbPrefab == nullptr)
	{
		bouncingOrbPrefab = new Model("Assets/Models/DefaultSphere.fbx");
		bouncingOrbPrefab->transform.SetScale(glm::vec3(0.3f));
		bouncingOrbPrefab->meshes[0]->material->SetBaseColor(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	BouncingOrb* bullet = new BouncingOrb();

	bullet->CreateBulletInstance(bouncingOrbPrefab);

	renderer->AddModel(bullet->model, shader);
	physicsEngine->AddPhysicsObject(bullet->phyObj);

	EntityManager::GetInstance().AddEntity("Factory" + std::to_string(index) + "BouncingOrb" + std::to_string(bulletCount), bullet);

	bulletCount++;

	return bullet;
}

//BaseBullet* BulletFactory::CreateEnforcerBullet()
//{
//	if (enforcerBulletPrefab == nullptr)
//	{
//		enforcerBulletPrefab = new Model("Assets/Models/Enemies/Enforcer/enforcerbullet1.ply");
//		enforcerBulletPrefab->transform.SetScale(glm::vec3(0.0075f));
//		enforcerBulletPrefab->isActive = false;
//
//		Model* model2 = new Model("Assets/Models/Enemies/Enforcer/enforcerbullet2.ply");
//		model2->transform.SetScale(glm::vec3(0.0075f));
//		model2->isActive = false;
//
//		Model* model3 = new Model("Assets/Models/Enemies/Enforcer/enforcerbullet3.ply");
//		model3->transform.SetScale(glm::vec3(0.0075f));
//		model3->isActive = false;
//
//		enforcerAnimationModels.push_back(enforcerBulletPrefab);
//		enforcerAnimationModels.push_back(model2);
//		enforcerAnimationModels.push_back(model3);
//
//	}
//
//	EnforcerBullet* bullet = new EnforcerBullet();
//
//	bullet->CreateBulletInstance(enforcerBulletPrefab, enforcerAnimationModels, renderer, shader, physicsEngine);
//
//
//	renderer->AddModel(bullet->model, shader);
//	physicsEngine->AddPhysicsObject(bullet->phyObj);
//
//	EntityManager::GetInstance().AddEntity("EnforcerBullet" + std::to_string(bulletCount), bullet);
//
//	bulletCount++;
//
//	return bullet;
//}

void BulletFactory::AssignRenderesAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
	this->physicsEngine = physicsEngine;
}
