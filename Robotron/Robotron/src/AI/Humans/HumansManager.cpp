#include "HumansManager.h"
#include "../../Utilities/Random.h"
#include "../../EntityManager/EntityManager.h"

HumansManager::HumansManager()
{
	entityId = "HumanManager";

	InitializeEntity(this);
}

void HumansManager::Start()
{
	SpawnHumans();
}

void HumansManager::Update(float deltaTime)
{
}

void HumansManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void HumansManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void HumansManager::SpawnHumans()
{
	humanCount = GetRandomIntNumber(humanMinCount, humanMaxCount);

	int random = 0;
	float randomX = 0;
	float randomY = 0;

	for (int i = 0; i < humanCount; i++)
	{
		random = GetRandomIntNumber(0, 2);

		Human* human = new Human((Human::HumanType)random);

		EntityManager::GetInstance().AddEntity("Human" + std::to_string(listOfHumans.size()), human);

		do {
			randomX = GetRandomFloatNumber(-spawnXRange, spawnXRange);
			randomY = GetRandomFloatNumber(-spawnYRange, spawnYRange);
		} while (std::abs(randomX) < centerRadius && std::abs(randomY) < centerRadius);

		human->model->transform.SetPosition(glm::vec3(randomX, randomY, 0.0f));
		human->humansManager = this;

		listOfHumans.push_back(human);
	}
}

void HumansManager::RemoveHuman( Human* human)
{
	listOfHumans.erase(std::remove(listOfHumans.begin(), listOfHumans.end(), human), listOfHumans.end());

	human->Destroy();
}
