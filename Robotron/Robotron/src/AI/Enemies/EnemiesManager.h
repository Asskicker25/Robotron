#pragma once

#include "../../EntityManager/Entity.h"
#include "../../Level/GameMediator.h"
#include "../../Bullet/BaseBullet.h"

class HumansManager;

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

	void SpawnEnemies();
	
	void AssignGameMediator(GameMediator* gameMediator);
	void RemoveEnemy(BaseEnemy* enemy);

	void SpawnEnemyForSpheroid(glm::vec3 position);

	void AddBulletToMediator(BaseBullet* bullet);


	HumansManager* humansManager;

};

