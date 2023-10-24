#include "EntityManager.h"
#include <Graphics/Renderer.h>

void EntityManager::AddEntity(const std::string& entityId, Entity* entity)
{
	listOfEntities[entityId] = entity;
}

void EntityManager::RemoveEntity(const std::string& entityId)
{
	listOfEntities.erase(entityId);
}

void EntityManager::Start()
{
	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->Start();
	}
}

void EntityManager::Update()
{
	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->Update();
	}
}

void EntityManager::AddToRenderer(Renderer& renderer)
{
	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->AddToRenderer(renderer);
	}
}
