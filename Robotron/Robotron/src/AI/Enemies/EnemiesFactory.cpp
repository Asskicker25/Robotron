#include "EnemiesFactory.h"

#include "Spheroid/Spheroid.h"
#include "Grunts/Grunt.h"
#include "Hulk/Hulk.h"
#include "Enforcer/Enforcer.h"
#include "../../EntityManager/EntityManager.h"
#include "Brain/Brain.h"

void EnemiesFactory::AddComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
	this->physicsEngine = physicsEngine;
}


BaseEnemy* EnemiesFactory::CreateSpheroid()
{

	BaseEnemy* spheroid = new Spheroid();
	
	renderer->AddModel(spheroid->model, shader);
	physicsEngine->AddPhysicsObject(spheroid->phyObj);

	EntityManager::GetInstance().AddEntity("Spheroid" + std::to_string(currentCount), spheroid);

	currentCount++;

	return spheroid;
}

BaseEnemy* EnemiesFactory::CreateGrunt()
{
	BaseEnemy* grunt = new Grunt();

	renderer->AddModel(grunt->model, shader);
	physicsEngine->AddPhysicsObject(grunt->phyObj);

	EntityManager::GetInstance().AddEntity("Grunt" + std::to_string(currentCount), grunt);

	currentCount++;

	return grunt;
}

BaseEnemy* EnemiesFactory::CreateHulk()
{
	BaseEnemy* hulk = new Hulk();

	renderer->AddModel(hulk->model, shader);
	physicsEngine->AddPhysicsObject(hulk->phyObj);

	EntityManager::GetInstance().AddEntity("Hulk" + std::to_string(currentCount), hulk);

	currentCount++;

	return hulk;
}

BaseEnemy* EnemiesFactory::CreateEnforcer()
{
	BaseEnemy* enforcer = new Enforcer();

	renderer->AddModel(enforcer->model, shader);
	physicsEngine->AddPhysicsObject(enforcer->phyObj);

	EntityManager::GetInstance().AddEntity("Enforcer" + std::to_string(currentCount), enforcer);

	currentCount++;

	return enforcer;
}

BaseEnemy* EnemiesFactory::CreateBrain()
{
	BaseEnemy* brain = new Brain();

	renderer->AddModel(brain->model, shader);
	physicsEngine->AddPhysicsObject(brain->phyObj);

	EntityManager::GetInstance().AddEntity("Brain" + std::to_string(currentCount), brain);

	currentCount++;

	return brain;
}


BaseEnemy* EnemiesFactory::CreateEnemyByType(const int& type)
{
	if (type == 0)
	{
		return CreateGrunt();
	}
	else if (type == 1)
	{
		return CreateSpheroid();
	}
	else if (type == 2)
	{
		return CreateHulk();
	}
	else if (type == 3)
	{
		return CreateBrain();
	}

	return CreateGrunt();
}


