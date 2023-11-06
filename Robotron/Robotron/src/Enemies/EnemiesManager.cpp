#include "EnemiesManager.h"
#include "EnemiesFactory.h"
#include "../Utilities/Random.h"

class EnemiesManager::PIMPL
{
public:
	EnemiesFactory* factory;
	GameMediator* gameMediator;

	EnemiesManager* enemiesManager;

	std::vector<BaseEnemy*> listOfEnemies;

	static const int spheroidCountMin = 3;
	static const int spheroidCountMax = 8;

	static const int gruntCountMin = 8;
	static const int gruntCountMax = 15;

	static constexpr float spawnXRange = 13.5f;
	static constexpr float spawnYRange = 7.0f;

	PIMPL();

	void SpawnEnemies();
	void RemoveEnemy(BaseEnemy* baseEnemy);

};


EnemiesManager::PIMPL::PIMPL()
{
	factory = new EnemiesFactory();
}

void EnemiesManager::PIMPL::SpawnEnemies()
{

	int spheroidCount = GetRandomIntNumber(spheroidCountMin, spheroidCountMax);
	int gruntCount = GetRandomIntNumber(gruntCountMin, gruntCountMax);

	float randomPosX = 0;
	float randomPosY = 0;

	for (int i = 0; i < 1; i++)
	{
		BaseEnemy* spheroid = factory->CreateSpheroid();
		spheroid->enemiesManager = enemiesManager;

		randomPosX = GetRandomFloatNumber(-spawnXRange, spawnXRange);
		randomPosY = GetRandomFloatNumber(-spawnYRange, spawnYRange);
		spheroid->model->transform.SetPosition(glm::vec3(randomPosX, randomPosY, 0.0f));

		listOfEnemies.push_back(spheroid);
	}

	for (int i = 0; i < 1; i++)
	{
		BaseEnemy* grunt = factory->CreateGrunt();
		grunt->enemiesManager = enemiesManager;

		randomPosX = GetRandomFloatNumber(-spawnXRange, spawnXRange);
		randomPosY = GetRandomFloatNumber(-spawnYRange, spawnYRange);
		grunt->model->transform.SetPosition(glm::vec3(randomPosX, randomPosY, 0.0f));

		gameMediator->AddEnemy(grunt);
		listOfEnemies.push_back(grunt);
	}

}

void EnemiesManager::PIMPL::RemoveEnemy(BaseEnemy* baseEnemy)
{
	listOfEnemies.erase(std::remove(listOfEnemies.begin(), listOfEnemies.end(), baseEnemy), listOfEnemies.end());
	gameMediator->RemoveEnemy(baseEnemy);
}


EnemiesManager::EnemiesManager(GameMediator* gameMediator) : pimpl{new PIMPL()}
{
	InitializeEntity(this);
	AssignGameMediator(gameMediator);

	pimpl->enemiesManager = this;
	pimpl->SpawnEnemies();
}

void EnemiesManager::AssignGameMediator(GameMediator* gameMediator)
{
	pimpl->gameMediator = gameMediator;
}

void EnemiesManager::RemoveEnemy(BaseEnemy* enemy)
{
	pimpl->RemoveEnemy(enemy);
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

