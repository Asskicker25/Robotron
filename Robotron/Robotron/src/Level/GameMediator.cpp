#include "GameMediator.h"

void GameMediator::AddEnemy(BaseEnemy* enemy)
{
	listOfEnemies.push_back(enemy);
}

void GameMediator::RemoveEnemy(BaseEnemy* enemy)
{
	listOfEnemies.erase(std::remove(listOfEnemies.begin(), listOfEnemies.end(), enemy), listOfEnemies.end());
}

void GameMediator::UpdatePlayerPosition(float posX, float posY)
{
	for (BaseEnemy* enemy : listOfEnemies)
	{
		enemy->MoveTowardsPlayerPosition(posX, posY);
	}
}

void GameMediator::OnPlayerDead()
{
	for (BaseEnemy* enemy : listOfEnemies)
	{
		enemy->OnPlayerDead();
	}
}
