#include "EnemiesManager.h"
#include "EnemiesFactory.h"

class EnemiesManager::PIMPL
{
public:
	EnemiesFactory* factory;

	PIMPL();
	void SpawnEnemies();

};


EnemiesManager::PIMPL::PIMPL()
{
	factory = new EnemiesFactory();
}

void EnemiesManager::PIMPL::SpawnEnemies()
{
	BaseEnemy* spheroid = factory->CreateSpheroid();

	spheroid->model->transform.SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));
}


EnemiesManager::EnemiesManager() : pimpl{new PIMPL()}
{
	InitializeEntity(this);
	pimpl->SpawnEnemies();
}

void EnemiesManager::Start()
{
}

void EnemiesManager::Update(float deltaTime)
{
}

void EnemiesManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	pimpl->factory->AddComponents(renderer, shader, physicsEngine);
}

void EnemiesManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

