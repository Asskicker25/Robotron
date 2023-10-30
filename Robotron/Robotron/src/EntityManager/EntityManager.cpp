#include "EntityManager.h"
#include <Graphics/Renderer.h>

void EntityManager::AddEntity(const std::string& entityId, Entity* entity)
{
	listOfEntities[entityId] = entity;
	entity->entityId = entityId;
	entity->entityManager = this;
}

void EntityManager::RemoveEntity(const std::string& entityId)
{

	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		if (it->first == entityId)
		{
			Destroy(listOfEntities[entityId]);
			listOfEntities.erase(it->first);
			return;
		}
	}

	//listOfEntities.erase(entityId);
}

void EntityManager::RemoveEntity(Entity* entity)
{
	/*std::unordered_map<std::string, Entity*>::iterator it;

	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		if (it->second == entity)
		{
			Destroy(it->first);
			listOfEntities.erase(it->first);
			return;
		}
	}*/
}

void EntityManager::AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine)
{
	this->renderer = renderer;
	this->physicsEngine = physicsEngine;

	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->AddToRendererAndPhysics(renderer, shader, physicsEngine);
	}
}

void EntityManager::Start()
{
	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->Start();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->Update(deltaTime);
	}
}

void EntityManager::Destroy(Entity* entity)
{
	entity->RemoveFromRendererAndPhysics(renderer, physicsEngine);
}

