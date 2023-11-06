#include "EnemiesFactory.h"

#include "Spheroid/Spheroid.h"
#include "Grunts/Grunt.h"

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

	return spheroid;
}

BaseEnemy* EnemiesFactory::CreateGrunt()
{
	BaseEnemy* grunt = new Grunt();

	renderer->AddModel(grunt->model, shader);
	physicsEngine->AddPhysicsObject(grunt->phyObj);

	return grunt;
}
