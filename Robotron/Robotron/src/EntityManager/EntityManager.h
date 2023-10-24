#pragma once

#include <unordered_map>
#include <string>
#include "Entity.h"

class EntityManager
{
private:
	std::unordered_map<std::string, Entity*> listOfEntities;
	std::unordered_map<std::string, Entity*>::iterator it;

public:
	void AddEntity(const std::string& entityId, Entity* entity);
	void RemoveEntity(const std::string& entityId);
	void AddToRenderer(Renderer& renderer);

	void Start();
	void Update();
};

