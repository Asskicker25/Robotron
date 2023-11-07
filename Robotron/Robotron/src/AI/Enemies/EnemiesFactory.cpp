#include "EnemiesFactory.h"

#include "Spheroid/Spheroid.h"
#include "Grunts/Grunt.h"
#include "../../EntityManager/EntityManager.h"

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
