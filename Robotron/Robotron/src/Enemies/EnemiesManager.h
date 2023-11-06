#pragma once

#include "../EntityManager/Entity.h"
#include "../Level/GameMediator.h"

class EnemiesManager : public Entity
{

private:
	class PIMPL;

	PIMPL* pimpl;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

public:

	EnemiesManager(GameMediator* gameMediator);
	
	void AssignGameMediator(GameMediator* gameMediator);
	void RemoveEnemy(BaseEnemy* enemy);

};

