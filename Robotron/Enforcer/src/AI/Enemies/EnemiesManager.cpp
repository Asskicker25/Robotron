#include "EnemiesManager.h"
#include "EnemiesFactory.h"
#include "../../Utilities/Random.h"
#include "Brain/Brain.h"
#include "../Humans/HumansManager.h"

class EnemiesManager::PIMPL
{
public:
	EnemiesFactory* factory;
	GameMediator* gameMediator;

	EnemiesManager* enemiesManager;

	std::vector<BaseEnemy*> listOfEnemies;

	static const int spheroidCountMin = 2;
	static const int spheroidCountMax = 4;

	static const int gruntCountMin = 8;
	static const int gruntCountMax = 15;

	static const int hulkCountMin = 3;
	static const int hulkCountMax = 6;

	static const int brainCountMin = 3;
	static const int brainCountMax = 6;

	static const int tankCountMin = 3;
	static const int tankCountMax = 6;

	static constexpr float spawnXRange = 12.5f;
	static constexpr float spawnYRange = 5.5f;

	static constexpr float centerRadius = 5.0f;

	PIMPL();

	void SpawnEnemies();
	void SpawnEnemiesByType(const int& id, const int& count);
	void RemoveEnemy(BaseEnemy* baseEnemy);

	void SpawnEnemyForSpheroid(const glm::vec3& position);
	void AddBulletToMediator(BaseBullet* bullet);
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

	int brainCount = GetRandomIntNumber(brainCountMin, brainCountMax);

	int tankCount = GetRandomIntNumber(tankCountMin, tankCountMax);

	//SpawnEnemiesByType(0, gruntCount);
	SpawnEnemiesByType(1, 5);
	//SpawnEnemiesByType(2, hulkCount);
	//SpawnEnemiesByType(3, brainCount);
	//SpawnEnemiesByType(4, tankCount);
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

		if (id == 0 || id == 3 || id == 4)
		{
			gameMediator->AddEnemy(enemy);
		}

		if (id == 3)
		{
			((Brain*)enemy)->SetHumanManager(enemiesManager->humansManager);
		}
	}
}

void EnemiesManager::PIMPL::RemoveEnemy(BaseEnemy* baseEnemy)
{
	gameMediator->AddScore(baseEnemy->score);
	listOfEnemies.erase(std::remove(listOfEnemies.begin(), listOfEnemies.end(), baseEnemy), listOfEnemies.end());
	gameMediator->RemoveEnemy(baseEnemy);
}

void EnemiesManager::PIMPL::SpawnEnemyForSpheroid(const glm::vec3& position)
{
	BaseEnemy* enemy = factory->CreateEnforcer();

	enemy->enemiesManager = enemiesManager;

	enemy->model->transform.SetPosition(position);

	listOfEnemies.push_back(enemy);

	gameMediator->AddEnemy(enemy);
}


void EnemiesManager::PIMPL::AddBulletToMediator(BaseBullet* bullet)
{
	gameMediator->AddBullet(bullet);
}


EnemiesManager::EnemiesManager(GameMediator* gameMediator) : pimpl{new PIMPL()}
{
	entityId = "EnemiesManager";
	InitializeEntity(this);
	AssignGameMediator(gameMediator);

	pimpl->enemiesManager = this;
}

void EnemiesManager::SpawnEnemies()
{
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
	pimpl->SpawnEnemyForSpheroid(position);
}

void EnemiesManager::AddBulletToMediator(BaseBullet* bullet)
{
	pimpl->AddBulletToMediator(bullet);
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

