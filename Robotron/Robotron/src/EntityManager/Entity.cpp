#include "Entity.h"
#include "EntityManager.h"


void Entity::Destroy()
{
	Debugger::Print("Destroy Triggered");
	((EntityManager*)entityManager)->RemoveEntity(entityId);
}
