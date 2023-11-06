#include "EnemiesFactory.h"

#include "Electrodes/Spheroid.h"

void EnemiesFactory::AddComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
	this->physicsEngine = physicsEngine;
}

BaseEnemy* EnemiesFactory::CreateSpheroid()
{
	Spheroid* spheroid = new Spheroid();
	
	renderer->AddModel(spheroid->model, shader);
	physicsEngine->AddPhysicsObject(spheroid->phyObj);

	return spheroid;
}

