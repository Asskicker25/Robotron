#include "EnemiesManager.h"
#include "EnemiesFactory.h"
#include "../../Utilities/Random.h"

class EnemiesManager::PIMPL
{
public:
	EnemiesFactory* factory;
	GameMediator* gameMediator;

	EnemiesManager* enemiesManager;

	std::vector<BaseEnemy*> listOfEnemies;

	static const int spheroidCountMin = 3;
	static const int spheroidCountMax = 5;

	static const int gruntCountMin = 8;
	static const int gruntCountMax = 15;

	static const int hulkCountMin = 3;
	static const int hulkCountMax = 6;

	static constexpr float spawnXRange = 12.5f;
	static constexpr float spawnYRange = 5.5f;

	static constexpr float centerRadius = 5.0f;

	PIMPL();

	void SpawnEnemies();
	void SpawnEnemiesByType(const int& id, const int& count);
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

	int hulkCount = GetRandomIntNumber(hulkCountMin, hulkCountMax);

	SpawnEnemiesByType(0, gruntCount);
	SpawnEnemiesByType(1, spheroidCount);
	SpawnEnemiesByType(2, hulkCount);
}

void EnemiesManager::PIMPL::SpawnEnemiesByType(const int& id, const int& count)
{
	float randomPosX = 0;
	float randomPosY = 0;

	for (int i = 0; i < count; i++)
	{
		BaseEnemy* enemy = factory->CreateEnemyByType(id);
		enemy->enemiesManager = enemiesManager;

		do {
			randomPosX = GetRandomFloatNumber(-spawnXRange, spawnXRange);
			randomPosY = GetRandomFloatNumber(-spawnYRange, spawnYRange);
		} while (std::abs(randomPosX) < centerRadius && std::abs(randomPosY) < centerRadius);

		enemy->model->transform.SetPosition(glm::vec3(randomPosX, randomPosY, 0.0f));

		listOfEnemies.push_back(enemy);

		if (id == 0)
		{
			gameMediator->AddEnemy(enemy);
		}
	}
}

void EnemiesManager::PIMPL::RemoveEnemy(BaseEnemy* baseEnemy)
{
	gameMediator->AddScore(baseEnemy->score);
	listOfEnemies.erase(std::remove(listOfEnemies.begin(), listOfEnemies.end(), baseEnemy), listOfEnemies.end());
	gameMediator->RemoveEnemy(baseEnemy);
}


EnemiesManager::EnemiesManager(GameMediator* gameMediator) : pimpl{new PIMPL()}
{
	entityId = "EnemiesManager";
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

void EnemiesManager::SpawnEnemyForSpheroid(glm::vec3 position)
{
	BaseEnemy* enemy = pimpl->factory->CreateEnforcer();

	enemy->model->transform.SetPosition(position);

	pimpl->listOfEnemies.push_back(enemy);
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
