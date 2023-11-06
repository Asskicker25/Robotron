#include "EnemiesManager.h"
#include "EnemiesFactory.h"

class EnemiesManager::PIMPL
{
public:
	EnemiesFactory* factory;
	GameMediator* gameMediator;

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
	BaseEnemy* grunt = factory->CreateGrunt();

	spheroid->model->transform.SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));
	grunt->model->transform.SetPosition(glm::vec3(-4.0f, 0.0f, 0.0f));

	gameMediator->AddEnemy(grunt);
}


EnemiesManager::EnemiesManager(GameMediator* gameMediator) : pimpl{new PIMPL()}
{
	InitializeEntity(this);
	AssignGameMediator(gameMediator);
	pimpl->SpawnEnemies();
}

void EnemiesManager::AssignGameMediator(GameMediator* gameMediator)
{
	pimpl->gameMediator = gameMediator;
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

